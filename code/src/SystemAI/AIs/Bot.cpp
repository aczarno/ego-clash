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
#include "..\..\BaseTypes\BaseTypes.h"
#include "..\..\Interfaces\Interface.h"
#include "..\..\Interfaces\Services\CollisionAPI.h"
#include "..\..\Framework\ServiceManager.h"

//
// AI system includes
//
#include "../System.h"
#include "Bot.h"

// Local constants
#define MIN_UPDATE_MAGNITUDE 0.00000001f


///////////////////////////////////////////////////////////////////////////////
// Bot - Constructor
Bot::Bot( ISystemScene* pSystemScene, pcstr pszName ) : AIObject( pSystemScene, pszName )
{
	m_Goal = NULL;

	// Set default values
	m_Type = BotType::e_None;

    m_Accel      = 20.0f;
	m_MaxSpeed   = 600.0f;
	m_Perception = 1.0f;
	m_Radius     = 50.0f;
	m_Speed      = 0.0f;
	m_SpeedRot   = 0.5f;
    m_Agility    = 1.0f;
	m_YOffset    = 200.0f;

	m_Velocity        = Math::Vector3::Zero;
    m_DesiredVelocity = Math::Vector3::Zero;

	m_Ground      = Math::Vector3::Zero;
	m_GroundTest  = Coll::InvalidHandle;
	m_GroundValid = False;
    m_PhysicsMove = True;

    m_MoveTest = Coll::InvalidHandle;

	m_OriginalFacing.x = 0.0f;
	m_OriginalFacing.y = 0.0f;
	m_OriginalFacing.z = 1.0f;
	m_OriginalFacing.Normalize();

	m_Facing = m_OriginalFacing;
	m_Orientation = Math::Quaternion::Zero;
	m_Orientation.Rotate( m_Facing );
	m_Facing.Normalize();
    
	m_Position = Math::Vector3::Zero;
    m_TargetPosition = m_Position;
}


///////////////////////////////////////////////////////////////////////////////
// ~Bot - Destructor
Bot::~Bot( void )
{
	SAFE_DELETE( m_Goal );
}


///////////////////////////////////////////////////////////////////////////////
// ChangeOccurred - Notify this Object a change occureed (change handler)
Error Bot::ChangeOccurred( ISubject* pSubject, System::Changes::BitMask ChangeType )
{
	// Call parent handler
	Error Result = AIObject::ChangeOccurred( pSubject, ChangeType );

	if( ChangeType & System::Changes::Geometry::Orientation )
    {
		// Set a new facing vector
		m_Facing = m_OriginalFacing;
		m_Orientation.Rotate( m_Facing );
		m_Facing.Normalize();
	}

    return Result;
}


///////////////////////////////////////////////////////////////////////////////
// PreUpdate - PreUpdate processing
void Bot::PreUpdate( f32 DeltaTime )
{
	// Call base PreUpdate
	AIObject::PreUpdate( DeltaTime );

    // Clear out desired velocity
    m_DesiredVelocity = Math::Vector3::Zero;

	// Update the current goal
	if( m_Goal )
	{
		m_Goal->PreUpdate( DeltaTime );
	}
}


///////////////////////////////////////////////////////////////////////////////
// Update - Main update
void Bot::Update( f32 DeltaTime )
{
	// Call base Update
	AIObject::Update( DeltaTime );

	// Update the current goal
	if( m_Goal )
	{
		m_Goal->Update( DeltaTime );
	}

    // Determine the squared magnitude of m_Velocity
    f32 Magnitude = m_Velocity.x * m_Velocity.x + m_Velocity.y * m_Velocity.y + m_Velocity.z * m_Velocity.z;

    // Update with velocity
    if( Magnitude > MIN_UPDATE_MAGNITUDE )
    {
        // If we are not using physics, directly change the position
        if( !m_PhysicsMove )
        {
            m_Position += ( m_Velocity * DeltaTime );
            PostChanges( System::Changes::Geometry::Position );
        }

	    // Rotation towards our current velocity
	    Math::Vector3 NormalizedVelocity = m_Velocity;
	    NormalizedVelocity.Normalize();

	    f32 AngularSpeed = m_SpeedRot * DeltaTime;
	    f32 DiffAngle = Math::Angle::ACos( m_Facing.Dot( NormalizedVelocity ) );

        // Rotate if the difference in m_Facing and m_Velocity is significant
        if( DiffAngle > 0.0001f || !m_PhysicsMove )
	    {
		    f32 Angle = Math::Min( DiffAngle, AngularSpeed );
            
            // Rotate m_Facing toward m_Velocity by Angle
		    Math::Quaternion Rotation;
		    Rotation.Set( (m_Facing.Cross( NormalizedVelocity )).Normalize(), Angle );

            // Update our orientation
		    m_Orientation = m_Orientation * Rotation;
		    m_Facing = m_OriginalFacing;
		    m_Orientation.Rotate( m_Facing );
		    m_Facing.Normalize();

            // Force the to face the direction they are heading if not using physics
            if( !m_PhysicsMove )
            {
                m_Orientation.Set( (m_OriginalFacing.Cross( NormalizedVelocity )).Normalize(), Math::Angle::ACos( m_OriginalFacing.Dot( NormalizedVelocity ) ) );
            }

            // Tell the other system our new orientation
            PostChanges( System::Changes::Geometry::Orientation );
	    }
    }
}


///////////////////////////////////////////////////////////////////////////////
// PostUpdate - PostUpdate processing
void Bot::PostUpdate( f32 DeltaTime )
{
	// Call base PostUpdate
	AIObject::PostUpdate( DeltaTime );

	// Update the current goal
	if( m_Goal )
	{
		m_Goal->PostUpdate( DeltaTime );
	}
    
    // Update velocity
    m_Velocity.Normalize();

    Math::Vector3 DeltaVelocity = m_DesiredVelocity - m_Velocity;
    DeltaVelocity.Normalize();
    DeltaVelocity *= DeltaTime * m_Agility;

    m_Velocity = m_Velocity + DeltaVelocity;
    m_Velocity.Normalize();
    m_Velocity *= m_Speed;

    // Tell other systems about our new velocity
    PostChanges( System::Changes::AI::Velocity );
}


///////////////////////////////////////////////////////////////////////////////
// GetPotentialSystemChanges - Returns systems changes possible for this Bot
System::Changes::BitMask Bot::GetPotentialSystemChanges( void )
{
    return ( System::Changes::Geometry::Position
           | System::Changes::Geometry::Orientation
           | System::Changes::AI::Behavior
           | System::Changes::AI::Velocity );
}

