// Copyright � 2008-2009 Intel Corporation
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
// core includes
//
#include "..\BaseTypes\BaseTypes.h"
#include "..\Interfaces\Interface.h"

//
// AI system includes
//
#include "System.h"
#include "Scene.h"
#include "Object.h"


///////////////////////////////////////////////////////////////////////////////
// AISystem - Constructor
AISystem::AISystem( void ) : ISystem()
{
}


///////////////////////////////////////////////////////////////////////////////
// ~AISystem - Destructor
AISystem::~AISystem( void )
{
}


///////////////////////////////////////////////////////////////////////////////
// GetName - Returns the name of this System
pcstr AISystem::GetName( void )
{
    return System::Names::AI;
}


///////////////////////////////////////////////////////////////////////////////
// GetSystemType - Returns System type for this System
System::Type AISystem::GetSystemType( void )
{
    return System::Types::AI;
}


///////////////////////////////////////////////////////////////////////////////
// Initialize - Initializes this System with the given properties
Error AISystem::Initialize( Properties::Array Properties )
{
    ASSERT( !m_bInitialized );

	m_bInitialized = True;

    return Errors::Success;
}


///////////////////////////////////////////////////////////////////////////////
// GetProperties - Properties for this System are returned in Properties
void AISystem::GetProperties( Properties::Array& Properties )
{
    UNREFERENCED_PARAM( Properties );
}


///////////////////////////////////////////////////////////////////////////////
// SetProperties - Set properties for this System
void AISystem::SetProperties( Properties::Array Properties )
{
    ASSERT( m_bInitialized );
}


///////////////////////////////////////////////////////////////////////////////
// CreateScene - Creates and returns a new Scene
ISystemScene* AISystem::CreateScene( void )
{
    return new AIScene( this );
}


///////////////////////////////////////////////////////////////////////////////
// DestroyScene - Destorys the given Scene, free all associated resources
Error AISystem::DestroyScene( ISystemScene* pSystemScene )
{
    ASSERT( pSystemScene != NULL );

    AIScene* pScene = reinterpret_cast<AIScene*>(pSystemScene);
    SAFE_DELETE( pScene );

    return Errors::Success;
}

