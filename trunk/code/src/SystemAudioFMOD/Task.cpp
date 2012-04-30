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

//
// extern includes
//
#include "fmod.hpp"

//
// core includes
//
#include "..\BaseTypes\BaseTypes.h"
#include "..\Interfaces\Interface.h"

//
// system includes
//
#include "Scene.h"
#include "Task.h"
#include "Object.h"
#include "System.h"

extern ManagerInterfaces g_Managers;

FMODTask::FMODTask(FMODScene* pScene)
: ISystemTask( pScene )
, m_pScene( pScene )
{
	ASSERT( m_pScene != NULL );
	m_pSystem = (FMODSystem*)m_pScene->GetSystem();
	m_Pause = False;
}


FMODTask::~FMODTask(void)
{
}


System::Type FMODTask::GetSystemType(void)
{
	return System::Types::Audio;
}


void FMODTask::Update(f32 DeltaTime)
{
	if ( m_pSystem->AudioInitialized() )
	{
		// Update - process sound changes (random sounds)
		m_pScene->Update( DeltaTime );
		m_Result = m_pSystem->m_pFMOD->update();
		if (m_Result != FMOD_OK)
		{
			m_pSystem->FMODErrorCode( m_Result, __FUNCTION__ );
		}

		// Check if environment is paused
		Bool Pause = g_Managers.pEnvironment->Runtime().GetStatus() == IEnvironment::IRuntime::Status::Paused;

		if( Pause && !m_Pause )
		{
			// Pause the audio
			m_Pause = True;
			FMODSystem::PauseAll();
		}
		else if( !Pause && m_Pause )
		{
			// Unpause the audio
			m_Pause = False;
			FMODSystem::ResumeAll();
		}

		// Capture CPU Utilization information
		// It was learned that cpu = stream + dsp + main, but on multi-core systems,
		// cpu should not top at 100f.  The FMOD documentation states that cpu has
		// a [0f, 100f] range.  We will disregard cpu and only have it here in case 
		// the FMOD creators address this
		f32 stream, dsp, geometry, update, total;
		m_Result = m_pSystem->m_pFMOD->getCPUUsage( &dsp, &stream, &geometry, &update, &total );
		UNREFERENCED_PARAM(total);
		if (m_Result != FMOD_OK)
		{
			m_pSystem->FMODErrorCode( m_Result, __FUNCTION__ );
		}
		//Debug::Print("s = %1.2f, d = %1.2f, m = %1.2f, c = %1.2f\n", stream, dsp, main, cpu);

		m_pSystem->SetCPUUsage( stream + dsp + geometry + update );
	}
}

