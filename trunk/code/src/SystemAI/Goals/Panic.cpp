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
#include "Panic.h"
#include "..\AIs\Bot.h"
#include "..\AIs\Animal.h"

///////////////////////////////////////////////////////////////////////////////
// Panic - Default constructor
Panic::Panic( Bot* pBot ) : Goal( pBot )
{
}


///////////////////////////////////////////////////////////////////////////////
// ~Panic - Destructor
Panic::~Panic( void )
{
}


///////////////////////////////////////////////////////////////////////////////
// PreUpdate - PreUpdate processing
void Panic::PreUpdate( f32 DeltaTime )
{
	UNREFERENCED_PARAM( DeltaTime );
}


///////////////////////////////////////////////////////////////////////////////
// Update - Main update
void Panic::Update( f32 DeltaTime )
{
	ASSERT( m_Bot->m_Type == BotType::e_None || m_Bot->m_Type == BotType::e_Chicken || m_Bot->m_Type == BotType::e_Horse || m_Bot->m_Type == BotType::e_Swallow );
	Animal* p_Animal = (Animal*)m_Bot;

    // Adjust desired veleocity
    m_Bot->m_DesiredVelocity = m_Bot->m_DesiredVelocity + p_Animal->m_FearVector;
    m_Bot->m_DesiredVelocity.Normalize();

    // Adjust bot speed (go as fast as we can)
    m_Bot->m_Speed = MIN( m_Bot->m_MaxSpeed, m_Bot->m_Speed + (m_Bot->m_Accel * DeltaTime) );
}


///////////////////////////////////////////////////////////////////////////////
// PostUpdate - PostUpdate processing
void Panic::PostUpdate( f32 DeltaTime )
{
	UNREFERENCED_PARAM( DeltaTime );
}


