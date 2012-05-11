#include "..\BaseTypes\BaseTypes.h"
#include "..\Interfaces\Interface.h"

// Input system includes
#include "System.h"
#include "Scene.h"
#include "Object.h"
#include "Task.h"

#include <tchar.h>
#include "..\ECInputLib\ECInputManager.h"
#include "dinput.h"

#include "MyGUI.h"

extern ManagerInterfaces   g_Managers;

// These are the generic names for all of the possible actions in the demo.
enum ACTIONS 
{
	// Discrete input. This is for state events such as button or key presses.
	// Used by the keyboard, mouse buttons, and digital buttons on a gamepad.
	INPUT_ACTION_1,
	INPUT_ACTION_2,

	// Absolute axis input. This is for the joystick-like devices which report absolute measurments.
	INPUT_ABS_MOVE_FORWARDBACK_AXIS,    // Move along Z axis
	INPUT_ABS_MOVE_LEFTRIGHT_AXIS,      // Move along X axis
	INPUT_ABS_ROTATE_UPDOWN_AXIS,       // Rotate around X axis
	INPUT_ABS_ROTATE_LEFTRIGHT_AXIS,    // Rotate around Y axis
	INPUT_ABS_MOVE_UPDOWN,              // Move along Y axis

	INPUT_LEFT_CTRL,                    // Left Ctrl
	INPUT_RIGHT_CTRL,                   // Right Ctrl
	INPUT_MOVE_FORWARD,
	INPUT_MOVE_BACK,
	INPUT_MOVE_LEFT,
	INPUT_MOVE_RIGHT,
	INPUT_MOVE_UP,
	INPUT_MOVE_DOWN,
	INPUT_ACTION_TIMESTOP,
	INPUT_ACTION_TOGGLE_OVERLAY_1,
	INPUT_ACTION_TOGGLE_OVERLAY_2,
	INPUT_ACTION_TOGGLE_OVERLAY_3,
	INPUT_ACTION_TOGGLE_OVERLAY_4,
	INPUT_ACTION_TOGGLE_OVERLAY_5,
	INPUT_QUIT,
	INPUT_SHOW_POLYGONS,                // Ctrl + P
	INPUT_TOGGLE_NORMALS,               // Ctrl + N
	INPUT_TOGGLE_TANGENTS,              // Ctrl + T
	INPUT_TOGGLE_BOUNDING_BOX,          // Ctrl + B
	INPUT_TOGGLE_CAPTIONS,              // Ctrl + O
	INPUT_SET_THREAD_COUNT_1,           // Ctrl + 1
	INPUT_SET_THREAD_COUNT_2,           // Ctrl + 2
	INPUT_SET_THREAD_COUNT_4,           // Ctrl + 4
	INPUT_SET_THREAD_COUNT_MAX,         // Ctrl + X

	// Relative axis input. This is for the mouse-like devices which report changes since the last measurement
	INPUT_REL_ROTATE_LEFTRIGHT_AXIS,  // Rotate around Y axis
	INPUT_REL_ROTATE_UPDOWN_AXIS,     // Rotate around X axis

	INPUT_NUM_ACTIONS,
	INPUT_INVALID_ACTION
};

DIACTION g_rgGameAction[] =
{
	// Device input pre-defined by DirectInput, according to genre
	// joystick
	{INPUT_ACTION_1,                  DIBUTTON_MECHA_FIRE,    0,            _T("Reset view"),           },
	{INPUT_ACTION_2,                  DIBUTTON_MECHA_WEAPONS, 0,            _T("Enable movement"),      },
	{INPUT_ABS_MOVE_FORWARDBACK_AXIS, DIAXIS_ANY_1,           0,            _T("Move forward/back"),    },
	{INPUT_ABS_MOVE_LEFTRIGHT_AXIS,   DIAXIS_ANY_2,           0,            _T("Move left/right"),      },
	{INPUT_ABS_ROTATE_UPDOWN_AXIS,    DIAXIS_ANY_3,           0,            _T("Rotate up/down"),       },
	{INPUT_ABS_ROTATE_LEFTRIGHT_AXIS, DIAXIS_ANY_4,           0,            _T("Rotate left/right"),    },
	{INPUT_ABS_MOVE_UPDOWN,           DIAXIS_ANY_Z_1,         0,            _T("Move up/down"),         },

	// Keyboard input mappings
	{INPUT_LEFT_CTRL,                 DIKEYBOARD_LCONTROL,    0,            _T("Left control key"),     },
	{INPUT_RIGHT_CTRL,                DIKEYBOARD_RCONTROL,    0,            _T("Right control key"),    },
	{INPUT_MOVE_FORWARD,              DIKEYBOARD_W,           0,            _T("MoveForward"),          },
	{INPUT_MOVE_BACK,                 DIKEYBOARD_S,           0,            _T("MoveBack"),             },
	{INPUT_MOVE_LEFT,                 DIKEYBOARD_A,           0,            _T("MoveLeft"),             },
	{INPUT_MOVE_RIGHT,                DIKEYBOARD_D,           0,            _T("MoveRight"),            },
	{INPUT_MOVE_UP,                   DIKEYBOARD_R,           0,            _T("MoveUp"),               },
	{INPUT_MOVE_DOWN,                 DIKEYBOARD_F,           0,            _T("MoveDown"),             },
	{INPUT_ACTION_1,                  DIKEYBOARD_C,           0,            _T("ResetView"),            },
	{INPUT_ACTION_TIMESTOP,           DIKEYBOARD_PAUSE,       0,            _T("Pause"),                },
	{INPUT_ACTION_TOGGLE_OVERLAY_1,   DIKEYBOARD_F1,          0,            _T("ToggleOverlay1"),       },
	{INPUT_ACTION_TOGGLE_OVERLAY_2,   DIKEYBOARD_F2,          0,            _T("ToggleOverlay2"),       },
	{INPUT_ACTION_TOGGLE_OVERLAY_3,   DIKEYBOARD_F3,          0,            _T("ToggleOverlay3"),       },
	{INPUT_ACTION_TOGGLE_OVERLAY_4,   DIKEYBOARD_F4,          0,            _T("ToggleOverlay4"),       },
	{INPUT_ACTION_TOGGLE_OVERLAY_5,   DIKEYBOARD_F5,          0,            _T("ToggleOverlay5"),       },
	{INPUT_QUIT,                      DIKEYBOARD_ESCAPE,      DIA_APPFIXED, _T("Quit"),                 },
	{INPUT_SHOW_POLYGONS,             DIKEYBOARD_P,           0,            _T("PolygonMode"),          },

	{INPUT_TOGGLE_NORMALS,            DIKEYBOARD_N,           0,            _T("ShowNormals"),          },
	{INPUT_TOGGLE_TANGENTS,           DIKEYBOARD_T,           0,            _T("ShowTangents"),         },
	{INPUT_TOGGLE_BOUNDING_BOX,       DIKEYBOARD_B,           0,            _T("ShowBoundingBox"),      },
	{INPUT_TOGGLE_CAPTIONS,           DIKEYBOARD_O,           0,            _T("ShowCaptions"),         },
	{INPUT_SET_THREAD_COUNT_1,        DIKEYBOARD_1,           0,            _T("SetThreadCountTo1"),    },
	{INPUT_SET_THREAD_COUNT_2,        DIKEYBOARD_2,           0,            _T("SetThreadCountTo2"),    },
	{INPUT_SET_THREAD_COUNT_4,        DIKEYBOARD_4,           0,            _T("SetThreadCountTo4"),    },
	{INPUT_SET_THREAD_COUNT_MAX,      DIKEYBOARD_X,           0,            _T("SetThreadCountToMax"),  },

	// Mouse input mappings
	{INPUT_REL_ROTATE_LEFTRIGHT_AXIS, DIMOUSE_XAXIS,          0,            _T("Look left/right"),      },
	{INPUT_REL_ROTATE_UPDOWN_AXIS,    DIMOUSE_YAXIS,          0,            _T("Look up/down"),         },
	{INPUT_ACTION_2,                  DIMOUSE_BUTTON1,        0,            _T("Enable movement"),      },
};

pcstr InputScene::sm_kapszPropertyNames[] =
{
  "INPUT_ACTION_CONFIRM", "INPUT_ACTION_CANCEL", "INPUT_MOVE_LEFT", "INPUT_MOVE_RIGHT", "INPUT_MOVE_UP", "INPUT_MOVE_DOWN",
	"INPUT_ACTION_TIMESTOP", "INPUT_ACTION_TOGGLE_OVERLAY_1", "INPUT_ACTION_TOGGLE_OVERLAY_2", "INPUT_ACTION_TOGGLE_OVERLAY_3",
	"INPUT_ACTION_TOGGLE_OVERLAY_4", "INPUT_ACTION_TOGGLE_OVERLAY_5", "INPUT_QUIT", "INPUT_SHOW_POLYGONS", "INPUT_TOGGLE_NORMALS",
	"INPUT_TOGGLE_TANGENTS", "INPUT_TOGGLE_BOUNDING_BOX", "INPUT_TOGGLE_CAPTIONS", "INPUT_SET_THREAD_COUNT_1", "INPUT_SET_THREAD_COUNT_2",
	"INPUT_SET_THREAD_COUNT_4", "INPUT_SET_THREAD_COUNT_MAX"
};

const Properties::Property InputScene::sm_kaDefaultProperties[] =
{
	Properties::Property( sm_kapszPropertyNames[ Property_InputActionConfirm ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_InputActionCancel ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_InputMoveLeft ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_InputMoveRight ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_InputMoveUp ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_InputMoveDown ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_InputActionTimestop ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_InputActionToggleOverlay1 ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_InputActionToggleOverlay2 ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_InputActionToggleOverlay3 ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_InputActionToggleOverlay4 ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_InputActionToggleOverlay5 ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_InputQuit ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_InputShowPolygons ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_InputToggleNormals ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_InputToggleTangents ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_InputToggleBoundingBox ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_InputToggleCaptions ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_InputSetThreadCount1 ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_InputSetThreadCount2 ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_InputSetThreadCount4 ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, ""),
	Properties::Property( sm_kapszPropertyNames[ Property_InputSetThreadCountMax ], VALUE1( Properties::Values::String ), Properties::Flags::Valid, "Key", NULL, NULL, NULL, "")
};

InputScene::InputScene( ISystem* pSystem ) : ISystemScene(pSystem), m_pInputTask(NULL)
{
	pInputSystem = (InputSystem*)pSystem;
}

InputScene::~InputScene( void )
{
}

System::Type InputScene::GetSystemType( void )
{
	return System::Types::Input;
}

void InputScene::setDefaultHotKeys()
{	
	hotKeys.push_back(HotKey("INPUT_ACTION_1", INPUT_ACTION_1, 'Z'));
	hotKeys.push_back(HotKey("INPUT_MOVE_UP", INPUT_MOVE_UP, VK_UP));
	hotKeys.push_back(HotKey("INPUT_MOVE_DOWN", INPUT_MOVE_DOWN, VK_DOWN));
	hotKeys.push_back(HotKey("INPUT_MOVE_LEFT", INPUT_MOVE_LEFT, VK_LEFT));
	hotKeys.push_back(HotKey("INPUT_MOVE_RIGHT", INPUT_MOVE_RIGHT, VK_RIGHT));
	hotKeys.push_back(HotKey("INPUT_ACTION_TIMESTOP", INPUT_ACTION_TIMESTOP, VK_PAUSE));
	hotKeys.push_back(HotKey("INPUT_ACTION_TOGGLE_OVERLAY_1", INPUT_ACTION_TOGGLE_OVERLAY_1, VK_F1));
	hotKeys.push_back(HotKey("INPUT_ACTION_TOGGLE_OVERLAY_2", INPUT_ACTION_TOGGLE_OVERLAY_2, VK_F2));
	hotKeys.push_back(HotKey("INPUT_ACTION_TOGGLE_OVERLAY_3", INPUT_ACTION_TOGGLE_OVERLAY_3, VK_F3));
	hotKeys.push_back(HotKey("INPUT_ACTION_TOGGLE_OVERLAY_4", INPUT_ACTION_TOGGLE_OVERLAY_4, VK_F4));
	hotKeys.push_back(HotKey("INPUT_ACTION_TOGGLE_OVERLAY_5", INPUT_ACTION_TOGGLE_OVERLAY_5, VK_F5));
	hotKeys.push_back(HotKey("INPUT_QUIT", INPUT_QUIT, VK_ESCAPE));
	hotKeys.push_back(HotKey("INPUT_SHOW_POLYGONS", INPUT_SHOW_POLYGONS, 'P'));
	hotKeys.push_back(HotKey("INPUT_TOGGLE_NORMALS", INPUT_TOGGLE_NORMALS, 'N'));
	hotKeys.push_back(HotKey("INPUT_TOGGLE_TANGENTS", INPUT_TOGGLE_TANGENTS, 'T'));
	hotKeys.push_back(HotKey("INPUT_TOGGLE_BOUNDING_BOX", INPUT_TOGGLE_BOUNDING_BOX, 'B'));
	hotKeys.push_back(HotKey("INPUT_TOGGLE_CAPTIONS", INPUT_TOGGLE_CAPTIONS, 'O'));
	hotKeys.push_back(HotKey("INPUT_SET_THREAD_COUNT_1", INPUT_SET_THREAD_COUNT_1, '1'));
	hotKeys.push_back(HotKey("INPUT_SET_THREAD_COUNT_2", INPUT_SET_THREAD_COUNT_2, '2'));
	hotKeys.push_back(HotKey("INPUT_SET_THREAD_COUNT_4", INPUT_SET_THREAD_COUNT_4, '4'));
	hotKeys.push_back(HotKey("INPUT_SET_THREAD_COUNT_MAX", INPUT_SET_THREAD_COUNT_MAX, 'X'));
}

int InputScene::getHotKeyKey(int hotKeyID)
{
	unsigned numHotKeys = hotKeys.size();
	for(unsigned i=0; i<numHotKeys; i++)
	{
		if(hotKeys[i].id == hotKeyID)
			return hotKeys[i].key;
	}	
}

int InputScene::getHotKeyKey(const char* hotKeyName)
{
	unsigned numHotKeys = hotKeys.size();
	for(unsigned i=0; i<numHotKeys; i++)
	{
		if(strcmp(hotKeyName, hotKeys[i].name) == 0)
			return hotKeys[i].key;
	}
}

Error InputScene::Initialize( std::vector<Properties::Property> Properties )
{
	ASSERT( !m_bInitialized );

	setDefaultHotKeys();

	m_Input = CInput::GetInstance();

	m_pInputTask = new InputTask( this );
	ASSERT( m_pInputTask != NULL );
	if( m_pInputTask == NULL )
	{
		return Errors::Failure;
	}

	SetProperties(Properties);

	m_bInitialized = True;

	return Errors::Success;
}

void InputScene::GetProperties( Properties::Array& Properties )
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
	//Properties[iProperty + Property_InputActionConfirm].SetValue(0, m_nFunctionKey);
}

void InputScene::SetProperties( Properties::Array Properties )
{
	//ASSERT( m_bInitialized );

	Error Err;
	Err = Errors::Failure;

  // Read in the properties.
  for ( Properties::Iterator it=Properties.begin(); it != Properties.end(); it++ )
  {
    if ( it->GetFlags() & Properties::Flags::Valid )
    {
			std::string sName = it->GetName();

			m_HotKeys[sName.c_str()] = it->GetString(0);
			/*if ( sName == sm_kapszPropertyNames[Property_FKey] )
			{
				m_nFunctionKey = it->GetInt32(0);
			}
			else if ( sName == sm_kapszPropertyNames[Property_Orientaget oution] )
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
			}*/
      // Set this property to invalid since it's already been read.
      it->ClearFlag(Properties::Flags::Valid);
    }
  }
}

pcstr* InputScene::GetObjectTypes( void )
{
	return NULL;
}

ISystemObject* InputScene::CreateObject(pcstr pszName, pcstr pszType)
{
	ASSERT( m_bInitialized );

	// Create the object and add it to the object list.
	InputObject* pObject = NULL;
	if( pszType && pszName ) 
	{
		pObject = new InputObject( this, pszType, pszName);
	} 
	else 
	{
		pObject = new InputObject ( this );
	}

	ASSERT( pObject != NULL );
	if( pObject != NULL )
	{
		objects.push_back( pObject );
	}

	return pObject;
}

Error InputScene::DestroyObject( ISystemObject* pSystemObject )
{
	ASSERT( m_bInitialized );
	ASSERT( pSystemObject != NULL );

	// Cast to a InputObject so that the correct destructor will be called.
	InputObject* pObject = reinterpret_cast<InputObject*>(pSystemObject);

	// Remove the object from the list and delete it.
	objects.remove( pObject );

	SAFE_DELETE( pSystemObject );

	return Errors::Success;
}

ISystemTask* InputScene::GetSystemTask( void )
{
	return m_pInputTask;
}

System::Changes::BitMask InputScene::GetPotentialSystemChanges( void )
{
	return System::Changes::Graphics::GUI;
}

const void* InputScene::GetSystemChangeData( System::Change SystemChange )
{
	UNREFERENCED_PARAM( SystemChange );
	return NULL;
}

void InputScene::InputUpdate(f32 DeltaTime)
{
	// TODO: GAMEPAD INPUT
	// TODO: GUI INPUT
	bool bPositionModified = false;
	bool bOrientationModified = false;
	bool bOrientationReset = false;
	bool bPositionReset = false;

	u32                mModified = 0;
	f32                total_yaw = 0.0f;
	f32                total_pitch = 0.0f;

	m_Input->Read();

	if(m_Input->GetBufferedKey(getHotKeyKey(INPUT_MOVE_LEFT)))
		MyGUI::InputManager::getInstance().injectKeyPress(MyGUI::KeyCode::ArrowLeft);

	if(m_Input->GetBufferedKey(getHotKeyKey(INPUT_MOVE_RIGHT)))
		MyGUI::InputManager::getInstance().injectKeyPress(MyGUI::KeyCode::ArrowRight);

	if(m_Input->GetBufferedKey(getHotKeyKey(INPUT_MOVE_UP)))
		MyGUI::InputManager::getInstance().injectKeyPress(MyGUI::KeyCode::ArrowUp);

	if(m_Input->GetBufferedKey(getHotKeyKey(INPUT_MOVE_DOWN)))
		MyGUI::InputManager::getInstance().injectKeyPress(MyGUI::KeyCode::ArrowDown);

	if(m_Input->GetBufferedKey(getHotKeyKey(INPUT_ACTION_1)))
		MyGUI::InputManager::getInstance().injectKeyPress(MyGUI::KeyCode::Return);

	// Temp mouse input
	POINT point = m_Input->GetMousePos();
	MyGUI::InputManager::getInstance().injectMouseMove(point.x, point.y, 0);

	if(m_Input->GetBufferedKey(VK_LBUTTON))
	{
		MyGUI::InputManager::getInstance().injectMousePress(point.x, point.y, MyGUI::MouseButton::Left);
		MyGUI::InputManager::getInstance().injectMouseRelease(point.x, point.y, MyGUI::MouseButton::Left);
	}

	/*if(m_Input->GetBufferedKey(VK_LCONTROL)
		|| m_Input->GetBufferedKey(VK_RCONTROL) 
		)
		bControlKeyPressed = true;
	else
		bControlKeyPressed = false;*/

	// we'll use this later to determine if the control key is in the proper state
	// no key pressed OR (ctrl key required AND pressed) OR ctrl key not required
	//BOOL bControlKeyValid = (
	//	( pHotKeyIter == pInputSystem->aHotKeys.end() ) ||
	//	( pHotKeyIter->second->bCtrl && bControlKeyPressed ) ||
	//	!pHotKeyIter->second->bCtrl
	//	);
	BOOL bControlKeyValid = bControlKeyPressed;

	if(m_Input->GetBufferedKey(getHotKeyKey(INPUT_SHOW_POLYGONS)))
		showPolygons();

	// TODO: BROKEN
	//if(m_Input->GetBufferedKey(getHotKeyKey(INPUT_TOGGLE_NORMALS)))
	//	toggleNormals();
	// TODO: BROKEN
	//if(m_Input->GetBufferedKey(getHotKeyKey(INPUT_TOGGLE_TANGENTS)))
	//	toggleTangents();

	if(m_Input->GetBufferedKey(getHotKeyKey(INPUT_TOGGLE_BOUNDING_BOX)))
		toggleBoundingBoxes();

	if(m_Input->GetBufferedKey(getHotKeyKey(INPUT_TOGGLE_CAPTIONS)))
		toggleCaptions();

	if(m_Input->GetBufferedKey(getHotKeyKey(INPUT_SET_THREAD_COUNT_4)))
		setThreadCount(4);

	if(m_Input->GetBufferedKey(getHotKeyKey(INPUT_SET_THREAD_COUNT_2)))
		setThreadCount(2);

	if(m_Input->GetBufferedKey(getHotKeyKey(INPUT_SET_THREAD_COUNT_1)))
		setThreadCount(1);

	if(m_Input->GetBufferedKey(getHotKeyKey(INPUT_SET_THREAD_COUNT_MAX)))
		setThreadCount(0);

	// TODO: KEYUP
	if(m_Input->GetBufferedKey(getHotKeyKey(INPUT_ACTION_TIMESTOP)))
		pause();
	// TODO: KEYUP
	if(m_Input->GetBufferedKey(getHotKeyKey(INPUT_ACTION_TOGGLE_OVERLAY_5)))
		toggleOverlay(5);
	// TODO: KEYUP
	if(m_Input->GetBufferedKey(getHotKeyKey(INPUT_ACTION_TOGGLE_OVERLAY_4)))
		toggleOverlay(4);
	// TODO: KEYUP
	if(m_Input->GetBufferedKey(getHotKeyKey(INPUT_ACTION_TOGGLE_OVERLAY_3)))
		toggleOverlay(3);
	// TODO: KEYUP
	if(m_Input->GetBufferedKey(getHotKeyKey(INPUT_ACTION_TOGGLE_OVERLAY_2)))
		toggleOverlay(2);
	// TODO: KEYUP
	if(m_Input->GetBufferedKey(getHotKeyKey(INPUT_ACTION_TOGGLE_OVERLAY_1)))
		toggleOverlay(1);

	if(m_Input->GetBufferedKey(getHotKeyKey(INPUT_QUIT)))
		quit();

	// Cycle through each device and process any updates from them.  We are using the buffered method
	// of input so the data goes into an array which we need to cycle through.
	for(std::list<InputObject*>::iterator iter=objects.begin(); iter != objects.end(); iter++)
	{
		(*iter)->Update(DeltaTime);
	}

	// Cycle through all of our objects and apply the changes. Also post our change notifications to the CCM.
}

void InputScene::showPolygons()
{
	i32 polygonMode = g_Managers.pEnvironment->Variables().GetAsInt("Graphics::PolygonMode")+1;
	char t[5];
	sprintf_s(t,5,"%d", polygonMode);
	g_Managers.pEnvironment->Variables().SetValue("Graphics::PolygonMode", t);
}

void InputScene::toggleNormals()
{
	pcstr pszValue = "False";
	Bool bShowNormals = g_Managers.pEnvironment->Variables().GetAsBool("Graphics::ShowNormals");
	bShowNormals = !bShowNormals;
	if(bShowNormals)
		pszValue = "True";
	g_Managers.pEnvironment->Variables().SetValue("Graphics::ShowNormals", pszValue);
}

void InputScene::toggleTangents()
{
	pcstr pszValue = "False";
	Bool bShowTangents = g_Managers.pEnvironment->Variables().GetAsBool("Graphics::ShowTangents");
	bShowTangents = !bShowTangents;
	if(bShowTangents)
		pszValue = "True";
	g_Managers.pEnvironment->Variables().SetValue("Graphics::ShowTangents", pszValue);
}

void InputScene::toggleBoundingBoxes()
{
	pcstr pszValue = "False";
	Bool bShowBoundingBox = g_Managers.pEnvironment->Variables().GetAsBool("Graphics::ShowBoundingBox");
	bShowBoundingBox = !bShowBoundingBox;
	if(bShowBoundingBox)
		pszValue = "True";
	g_Managers.pEnvironment->Variables().SetValue("Graphics::ShowBoundingBox", pszValue);
}

void InputScene::toggleCaptions()
{
	pcstr pszValue = "False";
	Bool bShowCaptions = g_Managers.pEnvironment->Variables().GetAsBool("Graphics::ShowCaptions");
	bShowCaptions = !bShowCaptions;
	if(bShowCaptions)
		pszValue = "True";
	g_Managers.pEnvironment->Variables().SetValue("Graphics::ShowCaptions", pszValue);
}

void InputScene::setThreadCount(int numThreads)
{
	if(g_Managers.pTask != NULL)
			g_Managers.pTask->SetNumberOfThreads(numThreads);
}

void InputScene::pause()
{
	static bool bScenePaused = false;

	switch(g_Managers.pEnvironment->Runtime().GetStatus())
	{
	case IEnvironment::IRuntime::Status::Running:
		g_Managers.pEnvironment->Runtime().SetStatus(IEnvironment::IRuntime::Status::Paused);
		bScenePaused = true;
		break;
	case IEnvironment::IRuntime::Status::Paused:
		g_Managers.pEnvironment->Runtime().SetStatus(IEnvironment::IRuntime::Status::Running);
		bScenePaused = false;
		break;
	}
}

void InputScene::toggleOverlay(int numOverlay)
{
	int nToggleOverlay = 0;

	nToggleOverlay += numOverlay;
	std::list<InputObject*>& Objects = objects;
	for( std::list<InputObject*>::iterator it=Objects.begin(); it != Objects.end(); it++ )
	{
		InputObject* pObject = *it;

		if( pObject->m_Type == pObject->Type_GUI )
		{
			if( pObject->m_nFunctionKey == nToggleOverlay )
			{
				pObject->PostChanges(System::Changes::Graphics::GUI);
			}
		}
	}
}

void InputScene::quit()
{
	g_Managers.pEnvironment->Runtime().SetStatus(IEnvironment::IRuntime::Status::Quit);
}