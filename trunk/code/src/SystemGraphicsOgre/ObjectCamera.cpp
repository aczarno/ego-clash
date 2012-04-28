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
// extern includes
//
#pragma warning( push, 0 )
#pragma warning( disable : 6326 6385 )
#include "Ogre.h"
//Include PagedGeometry headers that will be needed
#include "PagedGeometry.h"
#include "GrassLoader.h"
#pragma warning( pop )

#ifdef SAFE_DELETE
#undef SAFE_DELETE
#endif
#ifdef SAFE_DELETE_ARRAY
#undef SAFE_DELETE_ARRAY
#endif

//
// core includes
//
#include "..\BaseTypes\BaseTypes.h"
#include "..\Interfaces\Interface.h"

//
// core includes
//
#include "..\SystemInput\Object.h"

//
// Ogre system includes
//
#include "System.h"
#include "Scene.h"
#include "Object.h"
#include "ObjectCamera.h"


#define PSCENE          (reinterpret_cast<OGREGraphicsScene*>(m_pSystemScene))
#define PSYSTEM         (reinterpret_cast<OGREGraphicsSystem*>(m_pSystemScene->GetSystem()))
#define POGRESCENEMGR   (PSCENE->GetOGRESceneManager())


const pcstr OGREGraphicsObjectCamera::sm_kapszPolygonModeEnumOptions[] =
{
    "Points", "WireFrame", "Solid",
    NULL
};

const pcstr OGREGraphicsObjectCamera::sm_kapszPropertyNames[] =
{
    "FOVy", "ClipDistances", "Position", "LookAt", "PolygonMode", "LockCamera", "PagedGeometry"
};

const Properties::Property OGREGraphicsObjectCamera::sm_kaDefaultProperties[] =
{
    Properties::Property( sm_kapszPropertyNames[ Property_FOVy ],
                          VALUE1( Properties::Values::Float32 ),
                          Properties::Flags::Valid,
                          NULL, NULL, NULL, NULL,
                          0.0f ),
    Properties::Property( sm_kapszPropertyNames[ Property_ClipDistances ],
                          VALUE1x2( Properties::Values::Float32 ),
                          Properties::Flags::Valid,
                          NULL, NULL, NULL, NULL,
                          0.0f, 0.0f ),
    Properties::Property( sm_kapszPropertyNames[ Property_Position ],
                          Properties::Values::Vector3,
                          Properties::Flags::Valid,
                          NULL, NULL, NULL, NULL,
                          Math::Vector3::Zero ),
    Properties::Property( sm_kapszPropertyNames[ Property_LookAt ],
                          Properties::Values::Vector3,
                          Properties::Flags::Valid | Properties::Flags::WriteOnly,
                          NULL, NULL, NULL, NULL,
                          Math::Vector3::Zero ),
    Properties::Property( sm_kapszPropertyNames[ Property_PolygonMode ],
                          Properties::Values::Enum,
                          Properties::Flags::Valid | Properties::Flags::WriteOnly,
                          NULL, NULL, NULL, NULL,
                          PolygonMode_Solid ),
    Properties::Property( sm_kapszPropertyNames[ Property_LockCamera ],
                          Properties::Values::Boolean,
                          Properties::Flags::Valid | Properties::Flags::WriteOnly,
                          NULL, NULL, NULL, NULL,
                          0 ),
    Properties::Property( sm_kapszPropertyNames[ Property_PagedGeometry ],
                          NULL,
                          Properties::Flags::Valid,
                          NULL, NULL, NULL, NULL,
                          0, 0),
};


OGREGraphicsObjectCamera::OGREGraphicsObjectCamera(
    ISystemScene* pSystemScene,
    pcstr pszName
    )
    : OGREGraphicsObject( pSystemScene, pszName )
    , m_pCamera( NULL )
    , m_pViewport( NULL )
    , m_bLocked( false )
    , m_vLookAt( Math::Vector3::Zero )
{
    ASSERT( Property_Count == sizeof sm_kapszPropertyNames / sizeof sm_kapszPropertyNames[ 0 ] );
    ASSERT( Property_Count == sizeof sm_kaDefaultProperties / sizeof sm_kaDefaultProperties[ 0 ] );

    m_Type = OGREGraphicsObject::Type_Camera;
}


OGREGraphicsObjectCamera::~OGREGraphicsObjectCamera(
    void
    )
{
    ASSERT( m_pCamera != NULL );
    ASSERT( m_pViewport != NULL );

    if ( m_pViewport != NULL )
    {
        Ogre::RenderWindow* pRenderWindow = PSYSTEM->GetOGRERenderWindow();

        pRenderWindow->removeViewport( m_pViewport->getZOrder() );
    }

    if ( m_pCamera != NULL )
    {
		m_pNode->detachObject( m_pCamera );
        POGRESCENEMGR->destroyCamera( m_pCamera );
    }
}


Error
OGREGraphicsObjectCamera::Initialize(
    std::vector<Properties::Property> Properties
    )
{
    Error Err = Errors::Failure;

    ASSERT( !m_bInitialized );

    //
    // Call the base class.
    //
    OGREGraphicsObject::Initialize( Properties );

    //
    // Create the camera.
    //
    m_pCamera = POGRESCENEMGR->createCamera( m_pszName );
    ASSERT( m_pCamera != NULL );

    if ( m_pCamera != NULL )
    {
        //
        // Create the viewport.
        //
        Ogre::RenderWindow* pRenderWindow = PSYSTEM->GetOGRERenderWindow();
        m_pViewport = pRenderWindow->addViewport( m_pCamera );
        ASSERT( m_pViewport != NULL );

        if ( m_pViewport != NULL )
        {
            m_pViewport->setBackgroundColour( Ogre::ColourValue( 0, 0, 0 ) );
            m_PolygonMode = PolygonMode_Solid;

            //
            // Set the camera's aspect ratio to the dimensions of the viewport.
            //
            m_pCamera->setAspectRatio( Ogre::Real( m_pViewport->getActualWidth() ) /
                                       Ogre::Real( m_pViewport->getActualHeight() ));

            //
            // Attach the camera to the Ogre scene node. 
            //
            m_pNode->attachObject( m_pCamera );
            m_pNode->hideBoundingBox( true );

            //
            // Set this set as initialized.
            //
	        m_bInitialized = True;

            //
            // Set the properties for this object.
            //
            SetProperties( Properties );

            Err = Errors::Success;
        }
    }
    
    m_Modified = System::Changes::None;

    return Err;
}


void
OGREGraphicsObjectCamera::GetProperties(
    Properties::Array& Properties
    )
{
    //
    // Get the index of our first item.
    //
    i32 iProperty = static_cast<i32>(Properties.size());

    //
    // Add all the properties.
    //
    Properties.reserve( Properties.size() + Property_Count );

    for ( i32 i=0; i < Property_Count; i++ )
    {
        Properties.push_back( sm_kaDefaultProperties[ i ] );
    }

    //
    // Set the enum options string array.
    //
    Properties[ iProperty+Property_PolygonMode ].SetEnumOptions( sm_kapszPolygonModeEnumOptions );

    //
    // Modify the default values.
    //
    if ( m_pCamera != NULL )
    {
        Properties[ iProperty+Property_FOVy ].SetValue( 0, m_pCamera->getFOVy().valueRadians() );

        Properties[ iProperty+Property_ClipDistances ].SetValue(
            0, m_pCamera->getNearClipDistance()
            );
        Properties[ iProperty+Property_ClipDistances ].SetValue(
            1, m_pCamera->getFarClipDistance()
            );

        Ogre::Vector3 Position = m_pCamera->getPosition();
        Properties[ iProperty+Property_Position ].SetValue( 0, Position.x );
        Properties[ iProperty+Property_Position ].SetValue( 1, Position.y );
        Properties[ iProperty+Property_Position ].SetValue( 2, Position.z );

        Properties[ iProperty+Property_PolygonMode ].SetValue( 0, m_PolygonMode );
    }
}


void
OGREGraphicsObjectCamera::SetProperties(
    Properties::Array Properties
    )
{
    //
    // Read in the properties.
    //
    for ( Properties::Iterator it=Properties.begin(); it != Properties.end(); it++ )
    {
        if ( it->GetFlags() & Properties::Flags::Valid )
        {
            std::string sName = it->GetName();

            if ( sName == sm_kapszPropertyNames[ Property_FOVy ] )
            {
                //
                // Set the camera's field of view.
                //
                m_pCamera->setFOVy( Ogre::Radian( it->GetFloat32( 0 ) ) );
            }
            else if ( sName == sm_kapszPropertyNames[ Property_ClipDistances ] )
            {
                //
                // Set near and far clipping distances.
                //
                m_pCamera->setNearClipDistance( it->GetFloat32( 0 ) );
                m_pCamera->setFarClipDistance( it->GetFloat32( 1 ) );
            }
            else if ( sName == sm_kapszPropertyNames[ Property_Position ] )
            {
                //
                // Set the camera's position.
                //
                const Math::Vector3& Position = it->GetVector3();
                m_pCamera->setPosition( Ogre::Vector3( Position.x, Position.y, Position.z ) );
            }
            else if ( sName == sm_kapszPropertyNames[ Property_LookAt ] )
            {
                //
                // Set the point the camera is looking at.
                //
                m_vLookAt = it->GetVector3();
                m_pCamera->lookAt( TOOGREVEC( m_vLookAt ) );
            }
            else if ( sName == sm_kapszPropertyNames[ Property_PolygonMode ] )
            {
                //
                // Get the polygon mode.
                //
                m_PolygonMode = static_cast<PolygonModes>(it->GetInt32( 0 ));
                UpdatePolygonMode();
            }
            else if ( sName == sm_kapszPropertyNames[ Property_LockCamera ] )
            {
                m_bLocked = (0 != it->GetBool( 0 ));
            }
            //
            // Here we associate the camera with the PagedGeometry module. SetDetailLevel can
            // only be called after the camera has been set.
            //
            else if ( sName == sm_kapszPropertyNames[ Property_PagedGeometry ] )
            {
                PSCENE->SetCamera(m_pCamera);
                PSCENE->SetDetailLevel();
            }
            else
            {
                ASSERT( False );
            }

            //
            // Set this property to invalid since it's already been read.
            //
            it->ClearFlag( Properties::Flags::Valid );
        }
    }
}

System::Types::BitMask OGREGraphicsObjectCamera::GetDesiredSystemChanges( void )
{
    return System::Changes::POI::Target | OGREGraphicsObject::GetDesiredSystemChanges();
}

Error OGREGraphicsObjectCamera::ChangeOccurred( ISubject* pSubject, System::Changes::BitMask ChangeType )
{
    ASSERT( m_bInitialized );

	if ( ChangeType & System::Changes::POI::Target )
	{
        const Math::Vector3 poi = dynamic_cast<ITargetObject*>(pSubject)->GetTarget();
		m_pCamera->lookAt(poi.x,poi.y,poi.z);
	}
    if (ChangeType & System::Changes::Geometry::Orientation)
    {
        const Math::Quaternion& Orientation =
            *dynamic_cast<IGeometryObject*>(pSubject)->GetOrientation();

		Ogre::Radian rad;

		rad = Orientation.x;
		m_pCamera->yaw(rad);

        rad = Orientation.y;
		m_pCamera->pitch(rad);
		
        // Store the camera lookat direction
        const Ogre::Vector3 ogreVec = m_pCamera->getDirection();
        m_vLookAt.x = ogreVec.x;
        m_vLookAt.y = ogreVec.y;
        m_vLookAt.x = ogreVec.z;

		m_Modified |= System::Changes::Geometry::Orientation;
    }

	if (ChangeType & System::Changes::Geometry::Position)
    {
        const Math::Vector3 Position =
			    *dynamic_cast<IGeometryObject*>(pSubject)->GetPosition();

		Ogre::Vector3 pos(Position.x, Position.y, Position.z);
			
        //---------------------------------------------------------------------
        // The Input System makes relative changes. The other systems (cambot)
        // change the position of the camera in absolute terms.
        //
		if ( dynamic_cast<InputObject*>(pSubject) )
		{
			m_pCamera->moveRelative(pos);
        } else {
            m_pCamera->setPosition(pos);
        }
        
		m_Modified |= System::Changes::Geometry::Position;
    }

    return Errors::Success;
}

void 
OGREGraphicsObjectCamera::UpdatePolygonMode( void )
{
    ASSERT( m_PolygonMode > PolygonMode_Invalid );
    ASSERT( m_PolygonMode < PolygonMode_Count );

    switch(m_PolygonMode)
    {
        case PolygonMode_Points:
            m_pCamera->setPolygonMode( Ogre::PM_POINTS );
            break;

        case PolygonMode_WireFrame:
            m_pCamera->setPolygonMode( Ogre::PM_WIREFRAME );
            break;

        case PolygonMode_Solid:
            m_pCamera->setPolygonMode( Ogre::PM_SOLID );
            break;

        default:
            ASSERT( False );
    }
}

void 
OGREGraphicsObjectCamera::Update( f32 DeltaTime )
{
    UNREFERENCED_PARAM( DeltaTime );

    if( m_bLocked )
    {
        m_pCamera->lookAt( TOOGREVEC( m_vLookAt ) );
    }
    
    if (m_Modified) {
        PostChanges(m_Modified);
        m_Modified = System::Changes::None;
    }
}

///////////////////////////////////////////////////////////////////////////////
// GetPosition - Returns the position of this Object
const Math::Vector3* OGREGraphicsObjectCamera::GetPosition( void )
{
    Ogre::Vector3 v3;

    v3 = m_pCamera->getDerivedPosition();
    m_Position.x = v3.x;
    m_Position.y = v3.y;
    m_Position.z = v3.z;
    
	return &m_Position;
}


///////////////////////////////////////////////////////////////////////////////
// GetOrientation - Returns the orientation of this Object
const Math::Quaternion* OGREGraphicsObjectCamera::GetOrientation( void )
{
    Ogre::Quaternion q;
    
    q = m_pCamera->getDerivedOrientation();
    
    m_Orientation.x = q.x;
    m_Orientation.y = q.y;
    m_Orientation.z = q.z;
    m_Orientation.w = q.w;
    
	return &m_Orientation;
}


///////////////////////////////////////////////////////////////////////////////
// GetScale - Returns the scale of this Object
const Math::Vector3* OGREGraphicsObjectCamera::GetScale( void )
{
	return &m_Scale;
}

System::Changes::BitMask
OGREGraphicsObjectCamera::GetPotentialSystemChanges(
    void
    )
{
    return System::Changes::Geometry::Orientation | System::Changes::Geometry::Position;
}
