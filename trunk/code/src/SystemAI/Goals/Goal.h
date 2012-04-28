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
#include "..\..\BaseTypes\BaseTypes.h"
#include "..\..\Interfaces\Interface.h"

//
// forward declarations
//
class Bot;

///////////////////////////////////////////////////////////////////////////////
/// <summary>
///   <c>Goal</c> Implementation of the base AI goal.
/// </summary>
///////////////////////////////////////////////////////////////////////////////

class Goal
{
public:
	Goal( Bot* pBot );
    virtual ~Goal( void );

    /// <summary cref="Goal::GetName">
    ///   Gets the name for this goal.
    /// </summary>
    /// <returns>pcstr - Name of this goal.</returns>
	virtual pcstr GetName( void ) { return "Base Goal"; }

    /// <summary cref="Goal::PreUpdate">
    /// This method is called before each <c>Update</c> call to perform pre-processing.
    /// </summary>
    /// <param name="DeltaTime">Elapsed time since the last frame.</param>
	virtual void PreUpdate( f32 DeltaTime );

    /// <summary cref="Goal::Update">
    /// This method is called each frame to update this goal.
    /// </summary>
    /// <param name="DeltaTime">Elapsed time since the last frame.</param>
	virtual void Update( f32 DeltaTime );

    /// <summary cref="Goal::PostUpdate">
    /// This method is called after each <c>Update</c> call to perform post-processing.
    /// </summary>
    /// <param name="DeltaTime">Elapsed time since the last frame.</param>
	virtual void PostUpdate( f32 DeltaTime );

protected:
	Bot* m_Bot;  // Pointer to the bot that owns this goal
};

