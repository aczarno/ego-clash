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
// AI system includes
//
#include "Idle.h"
#include "..\AIs\Bot.h"
#include "..\AIs\Animal.h"

///////////////////////////////////////////////////////////////////////////////
// Idle - Default constructor
Idle::Idle( Bot* pBot ) : Goal( pBot )
{
}


///////////////////////////////////////////////////////////////////////////////
// ~Idle - Destructor
Idle::~Idle( void )
{
}


///////////////////////////////////////////////////////////////////////////////
// PreUpdate - PreUpdate processing
void Idle::PreUpdate( f32 DeltaTime )
{
	UNREFERENCED_PARAM( DeltaTime );
}


///////////////////////////////////////////////////////////////////////////////
// Update - Main update
void Idle::Update( f32 DeltaTime )
{
	// Come to a stop
	m_Bot->m_Speed = Math::Max( 0.0f, m_Bot->m_Speed - (m_Bot->m_Accel * DeltaTime) );
}


///////////////////////////////////////////////////////////////////////////////
// PostUpdate - PostUpdate processing
void Idle::PostUpdate( f32 DeltaTime )
{
	UNREFERENCED_PARAM( DeltaTime );
}

