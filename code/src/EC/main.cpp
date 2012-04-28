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

#include <windows.h>
#include <tchar.h>

#include "..\BaseTypes\BaseTypes.h"
#include "..\Interfaces\Interface.h"
#include "..\Framework\FrameworkAPI.h"
#include "..\Framework\EnvironmentManager.cpp"

#include <atlbase.h>

extern "C" int APIENTRY
_tWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR pszCmdLine,
    int CmdShow
    )
{
	USES_CONVERSION;
	
	WCHAR**				argv;
	int					argc, iArg;
	std::string			sGdfPath = "EC.gdf";
	bool				bLogging;
	
    UNREFERENCED_PARAM( hInstance );
    UNREFERENCED_PARAM( hPrevInstance );
    UNREFERENCED_PARAM( pszCmdLine );
    UNREFERENCED_PARAM( CmdShow );

	// 
	// Parse command line 
	// 
	bLogging = false;
	
	argv = CommandLineToArgvW( GetCommandLineW(), &argc);
	for(iArg=1; iArg<argc; iArg++)
	{
		switch (*argv[iArg])
		{
			case '-':
			case '/':
			{
				if (0==_wcsicmp(argv[iArg]+1, L"logging" ))		bLogging 		= true;
				// [moved to SystemGraphicsOGRE] if (0==_wcsicmp(argv[iArg]+1, L"windowed" ))	Options.bForceWindowed	= true;
			}	break;
			
			default:
			{
				sGdfPath = W2A( argv[iArg] );
			}
		}
	}
	LocalFree(argv);

	//
    // Start up debug functionality.
    //
	// NOTE: checking the environment will never work, because the Environment hasn't been read yet
    //Bool bLogging = Singletons::EnvironmentManager.Variables().GetAsBool( "Debug::Logging", False );
	Debug::Startup( bLogging );

    //
    // Call the engine to start execution.
    //
	EngineExecuteGDF(sGdfPath.c_str());

	//
    // Shutdown debug functionality.
    //
	Debug::Shutdown();

    return 0;
}
