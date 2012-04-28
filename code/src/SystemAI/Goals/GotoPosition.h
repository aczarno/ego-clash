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

#pragma once

//
// core includes
//
#include "..\..\Interfaces\Services\CollisionAPI.h"

//
// AI system includes
//
#include "Goal.h"


///////////////////////////////////////////////////////////////////////////////
/// <summary>
///   <c>GotoPosition</c> Implementation of a simple go to position goal.
/// </summary>
///////////////////////////////////////////////////////////////////////////////

class GotoPosition : public Goal
{
public:
	GotoPosition( Bot* pBot );
    virtual ~GotoPosition( void );

    /// <summary cref="GotoPosition::GotoPosition">
    ///   Constructor with an initial TargetPosition.
    /// </summary>
    /// <param name="pBot">Pointer to the bot that owns this goal.</param>
    /// <param name="TargetPosition">Desired position.</param>
	GotoPosition( Bot* pBot, Math::Vector3 TargetPosition );
   
    /// <summary cref="GotoPosition::GetName">
    ///   Gets the name for this goal ("GotoPosition").
    /// </summary>
    /// <returns>pcstr - Name of this goal.</returns>
    /// <seealso cref="Goal::GetName"/>
	virtual pcstr GetName( void ) { return "GotoPosition"; }

    /// <summary cref="GotoPosition::SetPosition">
    /// This method sets the desired position.  This is the position that
    /// the goal will try to move the AI towards.
    /// </summary>
    /// <param name="TargetPosition">Desired position.</param>
    void SetPosition( Math::Vector3 TargetPosition );

    /// <summary cref="GotoPosition::PreUpdate">
    /// This method is called before each <c>Update</c> call to perform pre-processing.
    /// </summary>
    /// <param name="DeltaTime">Elapsed time since the last frame.</param>
    /// <seealso cref="Goal::PreUpdate"/>
	virtual void PreUpdate( f32 DeltaTime );

    /// <summary cref="GotoPosition::Update">
    /// This method is called each frame to update this goal.
    /// </summary>
    /// <param name="DeltaTime">Elapsed time since the last frame.</param>
    /// <seealso cref="Goal::Update"/>
	virtual void Update( f32 DeltaTime );

    /// <summary cref="GotoPosition::PostUpdate">
    /// This method is called after each <c>Update</c> call to perform post-processing.
    /// </summary>
    /// <param name="DeltaTime">Elapsed time since the last frame.</param>
    /// <seealso cref="Goal::PostUpdate"/>
	virtual void PostUpdate( f32 DeltaTime );

protected:
	Math::Vector3 m_TargetPosition;
	Bool          m_Finished;  // Goal has completed
};

