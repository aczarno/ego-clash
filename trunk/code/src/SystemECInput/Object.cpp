//
// core includes
//
#include "..\BaseTypes\BaseTypes.h"
#include "..\Interfaces\Interface.h"

//
// Input system includes
//
#include "Object.h"

static const int s_MoveMax = 8;

pcstr InputObject::sm_kapszTypeNames[] =
{
    "Controlled", "Overlay",
    NULL
};

pcstr InputObject::sm_kapszPropertyNames[] =
{
    "FKey", "Orientation", "PUNCHA", "PUNCHB", "PUNCHC", "KICKA",
		"KICKB", "KICKC", "UP", "DOWN", "BACK", "FORWARD"
};

InputObject::InputObject( ISystemScene* pSystemScene ) : ISystemObject( pSystemScene, NULL )
{
	m_Type = Type_Controlled;
}

const Properties::Property InputObject::sm_kaDefaultProperties[] =
{
	Properties::Property( sm_kapszPropertyNames[ Property_FKey ], VALUE1( Properties::Values::Int32 ), Properties::Flags::Valid, NULL, NULL, NULL, NULL, 0),
	Properties::Property( sm_kapszPropertyNames[ Property_Orientation ], VALUE1x3( Properties::Values::Float32 ), Properties::Flags::Valid, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f),
	Properties::Property( sm_kapszPropertyNames[ Property_PunchA ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_PunchB ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_PunchC ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_KickA ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_KickB ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_KickC ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_Up ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_Down ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_Back ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_Forward ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, "")
};

InputObject::InputObject( ISystemScene* pSystemScene, pcstr pszType, pcstr pszName) : ISystemObject( pSystemScene, NULL )
{
	ASSERT( Property_Count == sizeof sm_kapszPropertyNames / sizeof sm_kapszPropertyNames[ 0 ] );
  ASSERT( Property_Count == sizeof sm_kaDefaultProperties / sizeof sm_kaDefaultProperties[ 0 ] );

	if(strcmp(pszType, sm_kapszTypeNames[Type_Controlled]) == 0) 
		m_Type = Type_Controlled;
  else if(strcmp(pszType, sm_kapszTypeNames[Type_GUI]) == 0)
		m_Type = Type_GUI;

	m_sName = pszName;
}

InputObject::~InputObject( void )
{
}

System::Type InputObject::GetSystemType( void )
{
	return System::Types::Input;
}

Error InputObject::Initialize( std::vector<Properties::Property> Properties )
{
	m_bInitialized = True;

	m_Input = new CECInputManager();

	// fill out pitch and yaw 
	m_Pitch = 0.0f;
	m_Yaw = 0.0f;
	m_nFunctionKey = 0;

	m_nOldLeft = 0;
  m_nOldRight = 0;
	m_nMoveLeftRight = 0;
	m_Behavior = Interface::e_Behavior_Idle;

	memset(&m_LayoutData, 0, sizeof(m_LayoutData));

	SetProperties(Properties);
	SetKeys();

  return Errors::Success;
}

void InputObject::GetProperties( Properties::Array& Properties )
{
  // Get the index of our first item.
  i32 iProperty = static_cast<i32>(Properties.size());

  // Add all the properties.
  Properties.reserve( Properties.size() + Property_Count );

  for ( i32 i=0; i < Property_Count; i++ )
  {
    Properties.push_back( sm_kaDefaultProperties[ i ] );
  }

  // Modify the default values.
	Properties[iProperty + Property_FKey].SetValue(0, m_nFunctionKey);
}

void InputObject::SetProperties( Properties::Array Properties )
{
	ASSERT( m_bInitialized );

	Error Err;
	Err = Errors::Failure;

  // Read in the properties.
  for ( Properties::Iterator it=Properties.begin(); it != Properties.end(); it++ )
  {
    if ( it->GetFlags() & Properties::Flags::Valid )
    {
			std::string sName = it->GetName();

			if ( sName == sm_kapszPropertyNames[Property_FKey] )
			{
				m_nFunctionKey = it->GetInt32(0);
			}
			else if ( sName == sm_kapszPropertyNames[Property_Orientation] )
			{
				m_Yaw   = it->GetFloat32(0);
				m_Pitch = it->GetFloat32(1);
				m_Roll  = it->GetFloat32(2);

				m_Orientation.x = m_Yaw;
				m_Orientation.y = m_Pitch;
				m_Orientation.z = 0;
				m_Orientation.w = 0;

				PostChanges(System::Changes::Geometry::Orientation);
			}
			else
			{
				m_HotKeys[sName.c_str()] = it->GetString(0);
				//ASSERT(False);
			}
      // Set this property to invalid since it's already been read.
      it->ClearFlag(Properties::Flags::Valid);
    }
  }
}

System::Types::BitMask InputObject::GetDesiredSystemChanges( void )
{
	return System::Changes::None;
}

Error InputObject::ChangeOccurred( ISubject* pSubject, System::Changes::BitMask ChangeType )
{
	ASSERT( m_bInitialized );

	if ( ChangeType & System::Changes::Geometry::Position )
		m_Position = *dynamic_cast<IGeometryObject*>(pSubject)->GetPosition();

	if ( ChangeType & System::Changes::Geometry::Orientation )
		m_Orientation = *dynamic_cast<IGeometryObject*>(pSubject)->GetOrientation();

	return Errors::Success;
}

System::Changes::BitMask InputObject::GetPotentialSystemChanges( void )
{
	return System::Changes::Geometry::Position |
					System::Changes::Geometry::Orientation |
					System::Changes::Graphics::GUI |
					System::Changes::Graphics::Animation;
}

const Math::Vector3* InputObject::GetPosition( void )
{
	return &m_Position;
}

const Math::Quaternion* InputObject::GetOrientation( void )
{
	return &m_Orientation;
}

///////////////////////////////////////////////////////////////////////////////
// GetBehavior - Returns the current behavior of this Object
const Behavior InputObject::GetBehavior( void )
{
  return m_Behavior;
}

const Math::Vector3* InputObject::GetScale( void )
{
	ASSERT(False);
	return NULL;
}

const WindowData* InputObject::GetWindowData( void )
{
	m_LayoutData.nFlags |= WINDOW_SHOW;
	m_LayoutData.bShow = !m_LayoutData.bShow;

	return &m_LayoutData; 
}

///////////////////////////////////////////////////////////////////////////////
// SetBehavior - Set the current behavior of this AI
void InputObject::SetBehavior( Interface::Behavior Behavior )
{
  if( m_Behavior != Behavior )
  {
    m_Behavior = Behavior;
    //PostChanges( System::Changes::AI::Behavior );
  }
}

void InputObject::Update(f32 DeltaTime)
{
	bool bPositionModified = false;
	const float        fMovementSpeed = 5.0f;
	u32                mModified = 0;
	Math::Vector3 Direction( 0.0f, 0.0f, 0.0f );
	float changePos = 0.0f;

	m_RunTime += DeltaTime;
	m_Input->Update(DeltaTime);

	// Check if we have activated any moves
	// Note: Any moves that have been activated will be found in m_Moves
	CMove ActivatedMove;
	if(m_Input->CheckMoves(&ActivatedMove, m_AvailableMoves) == true)
	{
		if(m_Moves.size() == s_MoveMax)
			m_Moves.pop_back();

		MoveDetails NewMoveDetails = {ActivatedMove, m_RunTime};
		m_Moves.push_front(NewMoveDetails);
	}
	if(m_Input->CheckCommand(COMMAND_BACK))
	{
		changePos        = -fMovementSpeed;
		bPositionModified = true;
		m_nMoveLeftRight += changePos * DeltaTime;
	}
	if(m_Input->CheckCommand(COMMAND_FORWARD))
	{
		changePos       = fMovementSpeed;
		bPositionModified = true;
		m_nMoveLeftRight += changePos * DeltaTime;
	}

	// Fire off events for any new moves
	// TODO: DO IT HERE
	/*if (m_nMoveLeftRight) 
	{
			// When paused DeltaTime is 0 which prevents camera movement on paused scene.  
			// If paused, set DeltaTime to some constant to allow camera movement around the scene.
			if( bScenePaused )
			{
					DeltaTime = 0.02f;
			}
			Direction.x += m_nMoveLeftRight + (changePos * DeltaTime);

			//Direction.z += m_nMoveForwardBack * DeltaTime;
			//Direction.y += m_nMoveUpDown * DeltaTime;
			bPositionModified = true;
	}*/

	//
  // Cycle through all of our objects and apply the changes. Also post our change notifications to the CCM.
  //
  if( bPositionModified )
  {
		Direction.x += m_nMoveLeftRight;

		if(m_Behavior != Interface::e_Behavior_Running)
		{
			SetBehavior(Interface::e_Behavior_Running);
			mModified |= System::Changes::AI::Behavior;
		}
    //--------------------------------------------------------------------------
    // GUI Objects do not need to be modified.
    //
    if( m_Type == Type_GUI ) 
    {
			return;
    }
    if( bPositionModified ) 
    {
      m_Position = Direction;

      mModified |= System::Changes::Geometry::Position;
    }

    PostChanges( mModified );
  }
	else if(m_Behavior != Interface::e_Behavior_Idle)
	{
		SetBehavior(Interface::e_Behavior_Idle);
		PostChanges(System::Changes::AI::Behavior);
	}
}

void InputObject::SetKeys()
{
	m_Input->ClearCommandInputs();

	// PUNCH A
	if(m_HotKeys.find(sm_kapszPropertyNames[ Property_PunchA ]) != m_HotKeys.end())
		m_Input->SetCommandInput(COMMAND_PUNCHA, (int)m_HotKeys[sm_kapszPropertyNames[ Property_PunchA ]].c_str());
	else
		m_Input->SetCommandInput(COMMAND_PUNCHA, 'A');
	// PUNCH B
	if(m_HotKeys.find(sm_kapszPropertyNames[ Property_PunchB ]) != m_HotKeys.end())
		m_Input->SetCommandInput(COMMAND_PUNCHB, (int)m_HotKeys[sm_kapszPropertyNames[ Property_PunchB ]].c_str());
	else
		m_Input->SetCommandInput(COMMAND_PUNCHB, 'S');
	// PUNCH C
	if(m_HotKeys.find(sm_kapszPropertyNames[ Property_PunchC ]) != m_HotKeys.end())
		m_Input->SetCommandInput(COMMAND_PUNCHC, (int)m_HotKeys[sm_kapszPropertyNames[ Property_PunchC ]].c_str());
	else
		m_Input->SetCommandInput(COMMAND_PUNCHC, 'D');
	// KICK A
	if(m_HotKeys.find(sm_kapszPropertyNames[ Property_KickA ]) != m_HotKeys.end())
		m_Input->SetCommandInput(COMMAND_KICKA, (int)m_HotKeys[sm_kapszPropertyNames[ Property_KickA ]].c_str());
	else
		m_Input->SetCommandInput(COMMAND_KICKA, 'Z');
	// KICK B
	if(m_HotKeys.find(sm_kapszPropertyNames[ Property_KickB ]) != m_HotKeys.end())
		m_Input->SetCommandInput(COMMAND_KICKB, (int)m_HotKeys[sm_kapszPropertyNames[ Property_KickB ]].c_str());
	else
		m_Input->SetCommandInput(COMMAND_KICKB, 'X');
	// KICK C
	if(m_HotKeys.find(sm_kapszPropertyNames[ Property_KickC ]) != m_HotKeys.end())
		m_Input->SetCommandInput(COMMAND_KICKC, (int)m_HotKeys[sm_kapszPropertyNames[ Property_KickC ]].c_str());
	else
		m_Input->SetCommandInput(COMMAND_KICKC, 'C');
	// UP
	if(m_HotKeys.find(sm_kapszPropertyNames[ Property_Up ]) != m_HotKeys.end())
		m_Input->SetCommandInput(COMMAND_UP, (int)m_HotKeys[sm_kapszPropertyNames[ Property_Up ]].c_str());
	else
		m_Input->SetCommandInput(COMMAND_UP, VK_UP);
	// DOWN
	if(m_HotKeys.find(sm_kapszPropertyNames[ Property_Down ]) != m_HotKeys.end())
		m_Input->SetCommandInput(COMMAND_DOWN, (int)m_HotKeys[sm_kapszPropertyNames[ Property_Down ]].c_str());
	else
		m_Input->SetCommandInput(COMMAND_DOWN, VK_DOWN);
	// BACK
	if(m_HotKeys.find(sm_kapszPropertyNames[ Property_Back ]) != m_HotKeys.end())
		m_Input->SetCommandInput(COMMAND_BACK, (int)m_HotKeys[sm_kapszPropertyNames[ Property_Back ]].c_str());
	else
		m_Input->SetCommandInput(COMMAND_BACK, VK_LEFT);
	// FORWARD
	if(m_HotKeys.find(sm_kapszPropertyNames[ Property_Forward ]) != m_HotKeys.end())
		m_Input->SetCommandInput(COMMAND_FORWARD, (int)m_HotKeys[sm_kapszPropertyNames[ Property_Forward ]].c_str());
	else
		m_Input->SetCommandInput(COMMAND_FORWARD, VK_RIGHT);

	// Need to fix all this for gamepad input
	if(CInput::GetInstance()->GetXboxGamepad(0)->IsConnected() == false)
	{
		m_Input->SetGamepad(false, 0);
	}
	else
	{
		m_Input->SetCommandInput(COMMAND_PUNCHA,		XBOX_GAMEPAD_BUTTON_X);
		m_Input->SetCommandInput(COMMAND_PUNCHB,		XBOX_GAMEPAD_BUTTON_Y);
		m_Input->SetCommandInput(COMMAND_PUNCHC,		XBOX_GAMEPAD_BUTTON_RB);
		m_Input->SetCommandInput(COMMAND_KICKA,		XBOX_GAMEPAD_BUTTON_A);
		m_Input->SetCommandInput(COMMAND_KICKB,		XBOX_GAMEPAD_BUTTON_B);
		m_Input->SetCommandInput(COMMAND_KICKC,		XBOX_GAMEPAD_BUTTON_RT);
		m_Input->SetCommandInput(COMMAND_UP,			XBOX_GAMEPAD_BUTTON_DPAD_UP);
		m_Input->AddCommandInput(COMMAND_UP,			XBOX_GAMEPAD_BUTTON_LS_UP);
		m_Input->SetCommandInput(COMMAND_DOWN,		XBOX_GAMEPAD_BUTTON_DPAD_DOWN);
		m_Input->AddCommandInput(COMMAND_DOWN,		XBOX_GAMEPAD_BUTTON_LS_DOWN);
		m_Input->SetCommandInput(COMMAND_BACK,		XBOX_GAMEPAD_BUTTON_DPAD_LEFT);
		m_Input->AddCommandInput(COMMAND_BACK,		XBOX_GAMEPAD_BUTTON_LS_LEFT);
		m_Input->SetCommandInput(COMMAND_FORWARD,		XBOX_GAMEPAD_BUTTON_DPAD_RIGHT);
		m_Input->AddCommandInput(COMMAND_FORWARD,		XBOX_GAMEPAD_BUTTON_LS_RIGHT);
		m_Input->SetGamepad(true, 0);
	}
}