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
// AI system includes
//
#include "Goal.h"

///////////////////////////////////////////////////////////////////////////////
/// <summary>
///   <c>Idle</c> Implementation of a simple idle goal.
/// </summary>
///////////////////////////////////////////////////////////////////////////////

class Idle : public Goal
{
public:
	Idle( Bot* pBot );
    virtual ~Idle( void );

    /// <summary cref="Idle::GetName">
    ///   Gets the name for this goal ("Idle").
    /// </summary>
    /// <returns>pcstr - Name of this goal.</returns>
    /// <seealso cref="Goal::GetName"/>
	virtual pcstr GetName( void ) { return "Idle"; }

    /// <summary cref="Idle::PreUpdate">
    /// This method is called before each <c>Update</c> call to perform pre-processing.  
    /// Does nothing for this goal.
    /// </summary>
    /// <param name="DeltaTime">Elapsed time since the last frame.</param>
    /// <seealso cref="Goal::PreUpdate"/>
	virtual void PreUpdate( f32 DeltaTime );

    /// <summary cref="Idle::Update">
    /// This method is called each frame to update this goal.  
    /// Slows down the AI to bring them to a stop (if they are moving).
    /// </summary>
    /// <param name="DeltaTime">Elapsed time since the last frame.</param>
    /// <seealso cref="Goal::Update"/>
	virtual void Update( f32 DeltaTime );

    /// <summary cref="Idle::PostUpdate">
    /// This method is called after each <c>Update</c> call to perform post-processing.  
    /// Does nothing for this goal.
    /// </summary>
    /// <param name="DeltaTime">Elapsed time since the last frame.</param>
    /// <seealso cref="Goal::PostUpdate"/>
	virtual void PostUpdate( f32 DeltaTime );

protected:
	Math::Vector3 m_TargetPosition;
	Coll::Handle  m_CollHandle;
	Bool          m_Finished;  // Goal has completed
};

