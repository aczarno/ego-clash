// Copyright © 2008-2009 Intel Corporation
// All Rights Reserved
//
// Permission is granted to use, copy, distribute and prepare derivative works of this
// software for any purpose and without fee, provided, that the above copyright notice
// and this statement appear in all copies.  Intel makes no representations about the
// suitability of this software for any purpose.  THIS SOFTWARE IS PROVIDED "AS IS."
// INTEL SPECIFICALLY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, AND ALL LIABILITY,
// INCLUDING CONSEQUENTIAL AND OTHER INDIRECT DAMAGES, FOR THE USE OF THIS SOFTWARE,
// INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PROPRIETARY RIGHTS, AND INCLUDING THE
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  Intel does not
// assume any responsibility for any errors which may appear in this software nor any
// responsibility to update it.

// Prevent other headers from including any platform specific ones
#define __PLATFORM_MANAGER

#include "..\BaseTypes\BaseTypes.h"
#include "..\Interfaces\Interface.h"

#include "PlatformManager.h"
#include "SystemManager.h"
#include "EnvironmentManager.h"
#include "ServiceManager.h"
#include "TaskManager.h"

extern TaskManager*     g_pTaskManager;

PlatformManager::PlatformManager(
    void
    )
{
}


PlatformManager::~PlatformManager(
    void
    )
{
}


#if defined ( WIN32 ) || defined ( WIN64 )
namespace Windows
{
    #define _WIN32_WINNT	0x0400 
    #include <windows.h>
}


PlatformManager::FileSystem::FileSystem(
    void
    )
{
}


PlatformManager::FileSystem::~FileSystem(
    void
    )
{
    //
    // Iterate through all the loaded libraries.
    //
    std::vector<SystemLib>::const_iterator it;
    for ( it=m_SystemLibs.begin(); it!=m_SystemLibs.end(); it++ )
    {
        Windows::HMODULE hLib = reinterpret_cast<Windows::HMODULE>(it->hLib);

        //
        // Get the system destruction function.
        //
        DestroySystemFunction fnDestroySystem =
            reinterpret_cast<DestroySystemFunction>(
                Windows::GetProcAddress( hLib, "DestroySystem" )
                );

        if ( fnDestroySystem != NULL )
        {
            fnDestroySystem( it->pSystem );
        }

        Windows::FreeLibrary( hLib );
    }

    m_SystemLibs.clear();
}


Error
PlatformManager::FileSystem::LoadSystemLibrary(
    const char* pszSysLib,
    ISystem** ppSystem
    )
{
    Error   Err = Errors::Failure;

    //
    // Load the dll.
    //
    Windows::HMODULE hLib = Windows::LoadLibraryA( pszSysLib );

    if ( hLib != NULL )
    {
        //
        // Get the system initialization function.
        //
        InitializeSystemLibFunction fnInitSystemLib =
            reinterpret_cast<InitializeSystemLibFunction>(
                Windows::GetProcAddress( hLib, "InitializeSystemLib" )
                );

        if ( fnInitSystemLib != NULL )
        {
            ManagerInterfaces Managers;
            Managers.pEnvironment = &Singletons::EnvironmentManager;
            Managers.pService     = &Singletons::ServiceManager;
            Managers.pTask        = g_pTaskManager;

            fnInitSystemLib( &Managers );
        }

        //
        // Get the system creation function.
        //
        CreateSystemFunction fnCreateSystem =
            reinterpret_cast<CreateSystemFunction>(
                Windows::GetProcAddress( hLib, "CreateSystem" )
                );

        if ( fnCreateSystem != NULL )
        {
            //
            // Create the system.
            //
			ISystem* pSystem = fnCreateSystem( Debug::GetDebugger() );

            if ( pSystem != NULL )
            {
                //
                // Verify that there's no duplicate system type.
                //
                System::Type SystemType = pSystem->GetSystemType();

                ISystem* pCurrSystem =
                    Singletons::SystemManager.Get( SystemType );

                if ( pCurrSystem == NULL )
                {
                    //
                    // Add the system to the collection.
                    //
                    Singletons::SystemManager.Add( pSystem );

                    SystemLib sl = { reinterpret_cast<Handle>(hLib), pSystem };
                    m_SystemLibs.push_back( sl );

                    *ppSystem = pSystem;
                }
            }
        }
    }

    return Err;
}


Bool
PlatformManager::FileSystem::FileExists(
    In pcstr pszFileName
    )
{
    Bool bFound = False;

    //
    // Open the file for read access.
    //
    Windows::HANDLE hFile = Windows::CreateFileA( pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
                                                  OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

    {
        using namespace Windows;

        if ( hFile != INVALID_HANDLE_VALUE )
        {
            //
            // Close it since we're just checking if it exists.
            //
            Windows::CloseHandle( hFile );

            bFound = True;
        }
    }

    return bFound;
}


Bool
PlatformManager::FileSystem::SetCurrentDirToFileLocation(
    In pcstr pszFileName,
    In pcstr apszLocations[],
    Out pstr pszCurrentDir,
    u32 BufferSize
    )
{
    Bool bDirectorySet = False;

    //
    // Check the current directory.
    //
    if ( !FileExists( pszFileName ) )
    {
        //
        // Save the original current directory.
        //
        char szCurrentDir[ _MAX_PATH ];
        Windows::GetCurrentDirectoryA( _MAX_PATH, szCurrentDir );

        for ( int i=0; apszLocations[ i ] != NULL; i++ )
        {
            //
            // Switch to the directory.
            //
            if ( Windows::SetCurrentDirectoryA( apszLocations[ i ] ) )
            {
                //
                // If it worked checked for file existence.
                //
                if ( FileExists( pszFileName ) )
                {
                    //
                    // We found it.  The break will keep the original directory from being reset.
                    //
                    bDirectorySet = True;
                    break;
                }
            }

            //
            // Restore the original directory for the next loop iteration.
            //
            Windows::SetCurrentDirectoryA( szCurrentDir );
        }
    }
    else
    {
        bDirectorySet = True;
    }

    //
    // Return the just set current directory if the user requested it.
    //
    if ( bDirectorySet && pszCurrentDir != NULL && BufferSize > 0 )
    {
        Windows::GetCurrentDirectoryA( BufferSize, pszCurrentDir );
    }

    return bDirectorySet;
}


PlatformManager::WindowSystem::WindowSystem(
    void
    )
{
}


void
PlatformManager::WindowSystem::ProcessMessages(
    void
    )
{
    //
    // Process all messages in the queue.
    //
    Windows::MSG    Msg;

    while ( Windows::PeekMessage( &Msg, NULL, 0, 0, PM_REMOVE ) )
    {
        Windows::TranslateMessage( &Msg );
        Windows::DispatchMessage( &Msg );
    }
}


struct WindowsTimerData
{
    Windows::HANDLE			hTimer;
    Windows::LARGE_INTEGER	Interval;
    Windows::LARGE_INTEGER  PreviousTick;
};

static f32                  sm_PerfCounterFrequency;

PlatformManager::Timers::Timers(
    void
    )
{
    Windows::LARGE_INTEGER Frequency;
	Windows::QueryPerformanceFrequency( &Frequency );

    sm_PerfCounterFrequency = static_cast<f32>(Frequency.QuadPart);
}


f32
PlatformManager::Timers::GetGranularity(
    void
    )
{
    // Use Windows::GetSystemTimeAdjustment
    return static_cast<f32>(1000.0f) / 1000000.0f;		// Set to 1 ms
}


Handle
PlatformManager::Timers::Create(
    f32 Interval
    )
{
    WindowsTimerData* pTimerData = new WindowsTimerData;
    ASSERT( pTimerData != NULL );

    //
    // Create the timer, granularity is in 100ns steps (but timer accuracy is system dependent).
    //
    pTimerData->hTimer = Windows::CreateWaitableTimer( NULL, TRUE, NULL );
    pTimerData->Interval.QuadPart = static_cast<Windows::ULONGLONG>(static_cast<double>(Interval) * -10000000.0);
    Windows::QueryPerformanceCounter( &pTimerData->PreviousTick );

    //
    // Start the timer.
    //
    Windows::SetWaitableTimer( pTimerData->hTimer, &pTimerData->Interval, 0, NULL, NULL, 0 );

    return reinterpret_cast<Handle>(pTimerData);
}


void
PlatformManager::Timers::Destroy(
    Handle hTimer
    )
{
    WindowsTimerData* pTimerData = reinterpret_cast<WindowsTimerData*>(hTimer);

    Windows::CloseHandle( pTimerData->hTimer );

    SAFE_DELETE( pTimerData );
}


f32
PlatformManager::Timers::Wait(
    Handle hTimer,
	Bool bWait
    )
{
    WindowsTimerData* pTimerData = reinterpret_cast<WindowsTimerData*>(hTimer);

    //
    // Wait for the timer to expire, then start it up again.
    //
	if ( bWait )
	{
		Windows::WaitForSingleObject( pTimerData->hTimer, INFINITE );
		Windows::SetWaitableTimer( pTimerData->hTimer, &pTimerData->Interval, 0, NULL, NULL, 0 );
	}

	//
	// Calculate the time delta in seconds. We are using the performance counter which varies by system.
	// The performance frequency is the number of performance counts per second.
	//
	Windows::LARGE_INTEGER CurrentTick;
	Windows::QueryPerformanceCounter(&CurrentTick);

	f32 DeltaTime = (f32)(CurrentTick.QuadPart - pTimerData->PreviousTick.QuadPart) /
                    sm_PerfCounterFrequency;

	ASSERT( DeltaTime >= static_cast<f32>(pTimerData->Interval.QuadPart) );

	pTimerData->PreviousTick = CurrentTick;

    return DeltaTime;
}


PlatformManager::Debugging::Debugging(
    void
    )
{
}
    
void
PlatformManager::Debugging::OutputMessage(
    pcstr pszMessage
    )
{
    Windows::OutputDebugStringA( pszMessage );
}


PlatformManager::Processor::Processor(
    void
    )
{
    //
    // Get the processor affinities for this process.
    //
    Windows::DWORD_PTR ProcessAffinityMask;
    Windows::DWORD_PTR SystemAffinityMask;

    Windows::GetProcessAffinityMask(
        Windows::GetCurrentProcess(), &ProcessAffinityMask, &SystemAffinityMask
        );

    //
    // Create a mask index for the processors.
    //
    Windows::SYSTEM_INFO si;
    Windows::GetSystemInfo( &si );

    m_ProcessorMasks.reserve( si.dwNumberOfProcessors );

	// Make sure we can use all processors.
	if ( SystemAffinityMask != ProcessAffinityMask ) {
		Windows::MessageBox( NULL,
			TEXT ( "The Smoke process has been restricted, so it cannot use all processors in the system." ),
			TEXT ( "Smoke startup warning" ),
			MB_OK );
	}

    for ( u32 i=0; ProcessAffinityMask > 0; i++, ProcessAffinityMask >>= 1 )
    {
        if ( ProcessAffinityMask & 1 )
        {
            m_ProcessorMasks.push_back( i );
        }
    }
    ASSERT( m_ProcessorMasks.size() <= si.dwNumberOfProcessors );
}


u32
PlatformManager::Processor::GetNumProcessors(
    void
    )
{
    return static_cast<u32>(m_ProcessorMasks.size());
}


void
PlatformManager::Processor::AffinitizeThreadToProcessor(
    u32 ProcessorNumber
    )
{
    ASSERT( ProcessorNumber < m_ProcessorMasks.size() );

    //
    // Set the preferred processor for this thread.
    //
    Windows::SetThreadIdealProcessor( Windows::GetCurrentThread(),
                                      m_ProcessorMasks[ ProcessorNumber ] );
}
#endif
