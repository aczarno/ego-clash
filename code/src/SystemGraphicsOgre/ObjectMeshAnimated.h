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

#include "ObjectMesh.h"

struct Animation
{
  Interface::Behavior   m_Behavior;    // Behavior associated with this animation
  Ogre::AnimationState* m_State;       // Pointer to OGRE animation state

  f32                   m_Transition;  // Run transition while there is time left
  bool                  m_Disable;     // Animation should be disabled?
};


///////////////////////////////////////////////////////////////////////////////
/// <summary>
///   A class that extends OGREGraphicsObjectMesh for meshes that animate.
/// </summary>
///////////////////////////////////////////////////////////////////////////////

class OGREGraphicsObjectMeshAnimated : public OGREGraphicsObjectMesh
{
public:
	OGREGraphicsObjectMeshAnimated( ISystemScene* pSystemScene, pcstr pszName );
  ~OGREGraphicsObjectMeshAnimated( void );

  /// <summary cref="OGREGraphicsObjectMeshAnimated::ChangeOccurred">
  /// Implementation of the <c>ISystemTask::Update</c> method.
  /// </summary>
  /// <param name="DeltaTime">Elapsed time since the last frame.</param>
  /// <seealso cref="OGREGraphicsObject::Update"/>
	virtual void Update( f32 DeltaTime );

protected:

  /// <summary cref="OGREGraphicsObjectMeshAnimated::Initialize">
  ///   Implementation of the <c>ISystem::Initialize</c> function.
  /// </summary>
  /// <param name="Properties">Initializes the object with the properties specified by <paramref name="Properties"/>.</param>
  /// <returns>Error.</returns>
  /// <seealso cref="OGREGraphicsObjectMesh::Initialize"/>
  virtual Error Initialize( std::vector<Properties::Property> Properties );

  /// <summary cref="OGREGraphicsObjectMeshAnimated::GetProperties">
  ///   Implementation of the <c>ISystem::GetProperties</c> function.
  /// </summary>
  /// <param name="Properties">Gets the properties of the object</param>
  /// <seealso cref="OGREGraphicsObjectMesh::GetProperties"/>
  virtual void GetProperties( Properties::Array& Properties );

  /// <summary cref="OGREGraphicsObjectMeshAnimated::SetProperties">
  ///   Implementation of the <c>ISystem::SetProperties</c> function.
  /// </summary>
  /// <param name="Properties">Sets the properties of the object</param>
  /// <seealso cref="OGREGraphicsObjectMesh::SetProperties"/>
  virtual void SetProperties( Properties::Array Properties );

  /// <summary cref="OGREGraphicsObjectMeshAnimated::GetDesiredSystemChanges">
  ///   Implementation of the <c>IGeometryObject::GetDesiredSystemChanges</c> function.
  /// </summary>
  /// <returns>System::Types::BitMask - System changes desired by the object.</returns>
  /// <seealso cref="OGREGraphicsObjectMesh::GetSystemType"/>
  virtual System::Types::BitMask GetDesiredSystemChanges( void );

  /// <summary cref="OGREGraphicsObjectMeshAnimated::ChangeOccurred">
  ///   Implementation of the <c>IObserver::ChangeOccurred</c> function.
  /// </summary>
  /// <param name="pSubject">Subject of this notification.</param>
  /// <param name="ChangeType">Type of notification for this object.</param>
  /// <returns>Error.</returns>
  /// <seealso cref="OGREGraphicsObjectMesh::ChangeOccurred"/>
	virtual Error ChangeOccurred( ISubject* pSubject, System::Changes::BitMask ChangeType );

  /// <summary cref="OGREGraphicsObjectMeshAnimated::GetPotentialSystemChanges">
  ///   Implementation of the <c>ISubject::GetPotentialSystemChanges</c> function.
  /// </summary>
  /// <returns>System::Changes::BitMask - Returns systems changes possible for this object.</returns>
  /// <seealso cref="OGREGraphicsObjectMesh::GetPotentialSystemChanges"/>
  virtual System::Changes::BitMask GetPotentialSystemChanges( void );


protected:
	enum BlendType
	{
		BlendSwitch,					// Stop source anim and start dest anim
		BlendWhileAnimating,	// Cross fade, blend source anim out while blending dest anim in
		BlendThenAnimate,			// Blend source to first frame of dest, when done, start dest anim
		BlendCount
	};

	void blend(Animation* animation, BlendType transition, float duration, bool looping);
	void addTime(const float deltaTime);

	// Blending variables _*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_
	float m_TimeLeft, m_Duration;
	bool m_Complete, m_Loop;
	Animation*						m_CurAnim;			// Current animation
	Animation*						m_TargetAnim;		// Animation to transition to
	BlendType							m_Transition;		// Current way to blend
	//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_

	// Properties
  enum PropertyTypes
  {
		Property_Skeleton,
    Property_Animation, 
    Property_Count
  };

  static pcstr                        sm_kapszAnimatedPropertyNames[];
  static const Properties::Property   sm_kaAnimatedDefaultProperties[];

	// Member variables
  std::list<Animation*> m_Animations;   // Collection of animations
  Math::Vector3         m_Velocity;     // Current velocity
  f32                   m_MaxVelocity;  // Max velocity
};

