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
//
// AI system includes
//
#include "GotoPosition.h"
#include "..\AIs\Bot.h"

///////////////////////////////////////////////////////////////////////////////
// GotoPosition - Constructor with target position
GotoPosition::GotoPosition( Bot* pBot ) : Goal( pBot )
{
	// Init instance data
	m_TargetPosition = Math::Vector3::Zero;
	m_Finished = False;
}


///////////////////////////////////////////////////////////////////////////////
// GotoPosition - Constructor with target position
GotoPosition::GotoPosition( Bot* pBot, Math::Vector3 TargetPosition ) : Goal( pBot )
{
	// Init instance data
	SetPosition( TargetPosition );
	m_Finished = False;
}


///////////////////////////////////////////////////////////////////////////////
// ~GotoPosition - Destructor
GotoPosition::~GotoPosition( void )
{
}


///////////////////////////////////////////////////////////////////////////////
// SetPosition - Set target position
void GotoPosition::SetPosition( Math::Vector3 TargetPosition )
{
	m_TargetPosition = TargetPosition;
}


///////////////////////////////////////////////////////////////////////////////
// PreUpdate - PreUpdate processing
void GotoPosition::PreUpdate( f32 DeltaTime )
{
	UNREFERENCED_PARAM( DeltaTime );
}


///////////////////////////////////////////////////////////////////////////////
// Update - Main update
void GotoPosition::Update( f32 DeltaTime )
{
	if( !m_Finished )
	{
		Math::Vector3 Disp = m_TargetPosition - m_Bot->m_Position;
		f32 DistToTravel = Disp.Magnitude();

		f32 TimeToStop = m_Bot->m_Speed / m_Bot->m_Accel;
		f32 DistToStop = m_Bot->m_Speed * TimeToStop;

		// Adjust bot speed
		if( DistToStop < DistToTravel )
		{
			// Accelerate
			m_Bot->m_Speed = MIN( m_Bot->m_MaxSpeed, m_Bot->m_Speed + (m_Bot->m_Accel * DeltaTime) );
		}
		else
		{
			// Decelerate
			m_Bot->m_Speed = MAX( 0.0f, m_Bot->m_Speed - (m_Bot->m_Accel * DeltaTime) );
		}

		// Normalize the displacement
		Disp.x = Disp.x / DistToTravel;
		Disp.y = Disp.y / DistToTravel;
		Disp.z = Disp.z / DistToTravel;

        // Adjust desired veleocity
        m_Bot->m_DesiredVelocity = m_Bot->m_DesiredVelocity + Disp;
	}
}


///////////////////////////////////////////////////////////////////////////////
// PostUpdate - PostUpdate processing
void GotoPosition::PostUpdate( f32 DeltaTime )
{
	UNREFERENCED_PARAM( DeltaTime );

	// Check if we've reached the target position
	Math::Vector3 Disp = m_TargetPosition - m_Bot->m_Position;

    #define MIN_DISTANCE_FROM_TARGET 1.0f
	if( Disp.Magnitude() < MIN_DISTANCE_FROM_TARGET )
	{
		m_Finished = True;
		m_Bot->m_Speed = 0.0f;
		m_Bot->m_Velocity = Math::Vector3::Zero;
	}
}

