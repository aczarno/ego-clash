#ifndef INPUTSCENE_H_
#define INPUTSCENE_H_

#include "System.h"

class InputSystem;
class InputTask;
class InputObject;
class CInput;
///////////////////////////////////////////////////////////////////////////////
/// <summary>
///   <c>InputScene</c> Implementation of the ISystemScene interface.
///   The input scene contains all the input objects
/// </summary>
///////////////////////////////////////////////////////////////////////////////

class InputScene : public ISystemScene
{
	friend class InputSystem;
	friend class InputTask;

public:
	//static bool __stdcall EnumSuitableDevicesCB(LPCDIDEVICEINSTANCE lpddi,
	//	LPDIRECTINPUTDEVICE8 lpdid,
	//	DWORD dwFlags,
	//	DWORD dwRemaining,
	//	LPVOID pvRef);
protected:

	InputScene( ISystem* pSystem );
	~InputScene( void );

	/// <summary cref="InputScene::GetSystemType">
	///   Implementation of the <c>ISystemScene::GetSystemType</c> function.
	/// </summary>
	/// <returns>System::Type - Type of this system.</returns>
	/// <seealso cref="ISystemScene::GetSystemType"/>
	virtual System::Type GetSystemType( void );

	/// <summary cref="InputScene::InputUpdate">
	/// This function must be called every frame.  It updates the input scene.
	/// </summary>
	/// <param name="DeltaTime">Elapsed time since the last frame.</param>
	/// <seealso cref="ISystemTask::Update"/>
	void InputUpdate(f32 DeltaTime);

	/// <summary cref="InputScene::Initialize">
	///   Implementation of the <c>ISystemScene::Initialize</c> function.
	///   One time initialization function for the scene.
	/// </summary>
	/// <param name="Properties">Initializes the input scene with the properties specified by <paramref name="Properties"/>.</param>
	/// <returns>Error.</returns>
	/// <seealso cref="ISystemScene::Initialize"/>
	virtual Error Initialize( std::vector<Properties::Property> Properties );

	/// <summary cref="InputScene::GetProperties">
	///   Implementation of the <c>ISystemScene::GetProperties</c> function.
	///   Gets the properties of this scene.
	/// </summary>
	/// <param name="Properties">Gets the properties of the sound scene</param>
	/// <seealso cref="ISystemScene::GetProperties"/>
	virtual void GetProperties( Properties::Array& Properties );

	/// <summary cref="InputScene::SetProperties">
	///   Implementation of the <c>ISystemScene::SetProperties</c> function.
	///   Sets the properties for this scene.
	/// </summary>
	/// <param name="Properties">Sets the properties of the input scene</param>
	/// <seealso cref="ISystem::SetProperties"/>
	virtual void SetProperties( Properties::Array Properties );

	/// <summary cref="InputScene::GetObjectTypes">
	///   Implementation of the <c>ISystemScene::GetObjectTypes</c> function.
	///   Get all the available object types as names.
	/// </summary>
	/// <returns>pcstr* - A NULL terminated array of object type names.</returns>
	/// <seealso cref="ISystemScene::GetObjectTypes"/>
	virtual pcstr* GetObjectTypes( void );

	/// <summary cref="InputScene::CreateObject">
	///   Implementation of the <c>ISystemScene::CreateObject</c> function.
	///   Creates a system object used to extend a UObject.
	/// </summary>
	/// <param name="pszName">The unique name for this object.</param>
	/// <param name="pszType">The object type to create.</param>
	/// <returns>ISystemObject* - The newly created system object.</returns>
	/// <seealso cref="ISystemScene::CreateObject"/>
	virtual ISystemObject* CreateObject( pcstr pszName, pcstr pszType );

	/// <summary cref="InputScene::DestroyObject">
	///   Implementation of the <c>ISystemScene::DestroyObject</c> function.
	///   Destroys a system object.
	/// </summary>
	/// <param name="pSystemObject">The system object to destroy.</param>
	/// <returns>Error - Any error codes.</returns>
	/// <seealso cref="ISystemScene::DestroyObject"/>
	virtual Error DestroyObject( ISystemObject* pSystemObject );

	/// <summary cref="InputScene::GetSystemTask">
	///   Implementation of the <c>ISystemScene::GetSystemTask</c> function.
	///   Returns a pointer to the task that this scene needs to perform on its objects.
	/// </summary>
	/// <returns>ISystemTask* - The task for this scene.</returns>
	/// <seealso cref="ISystemScene::GetSystemTask"/>
	virtual ISystemTask* GetSystemTask( void );

	/// <summary cref="InputScene::GetPotentialSystemChanges">
	///   Implementation of the <c>ISubject::GetPotentialSystemChanges</c> function.
	///   Identifies the system changes that this subject could possibly make.
	/// </summary>
	/// <returns>System::Changes::BitMask - A bitmask of the possible system changes.</returns>
	/// <seealso cref="ISubject::GetPotentialSystemChanges"/>
	virtual System::Changes::BitMask GetPotentialSystemChanges( void );

	/// <summary cref="InputScene::GetSystemChangeData">
	///   Implementation of the <c>ISubject::GetPotentialSystemChanges</c> function.
	///   Identifies the system changes that this subject could possibly make.
	/// </summary>
	/// <param name="SystemChange">A bitmask of the changes in the input scene.</param>
	virtual const void* GetSystemChangeData( System::Change SystemChange );

	void showPolygons();
	void toggleNormals();
	void toggleTangents();
	void toggleBoundingBoxes();
	void toggleCaptions();
	void setThreadCount(int numThreads);
	void pause();
	void toggleOverlay(int numOverlay);
	void quit();
protected:
	struct HotKey
	{
		const char* name;
		int id;
		int key;

		HotKey(const char* _name, int _id, int _key) : name(_name), id(_id), key(_key) {}
	};

	std::vector<HotKey>										hotKeys;

	void setDefaultHotKeys();
	int getHotKeyKey(int hotKeyID);
	int getHotKeyKey(const char* hotKeyName);

	// These three variables are used for determining what hotkey combination was used
	InputSystem*													pInputSystem;
	
	CInput*																m_Input;

	std::map<std::string, unsigned long>  m_aKeyboard;
	//InputSystem::hotKeyIt           pHotKeyIter;

	// Main task for the input scene
	InputTask*														m_pInputTask;

	// Input scene objects
	std::list<InputObject*>								objects;

	// Enable catching mouse movements
	bool																	MouseMoveEnabled;
	bool																	bControlKeyPressed;


	//LPDIRECTINPUT8                  pDI;		  // The DirectInput object
	//DIACTIONFORMAT                  diaf;

	f32																		fRotateLeftRight;
	f32																		fRotateUpDown;
	f32																		fMoveLeftRight;
	f32																		fMoveForwardBack;
	f32																		fMoveUpDown;

	//
	// For the keyboard, we need to save the amount moved on a keydown so that it can be reversed on a keyup.  We
	// cannot recalculate because DeltaTime is slightly different every update so you will end up with drifting.
	//
	f32                             fOldForward;
	f32                             fOldBack;
	f32                             fOldLeft;
	f32                             fnOldRight;
	f32                             fOldUp;
	f32                             fOldDown;

	std::map<const char*, std::string>	m_HotKeys;

	enum PropertyTypes
	{
		Property_InputActionConfirm,
		Property_InputActionCancel,
		Property_InputMoveLeft,
		Property_InputMoveRight,
		Property_InputMoveUp,
		Property_InputMoveDown,
		Property_InputActionTimestop,
		Property_InputActionToggleOverlay1,
		Property_InputActionToggleOverlay2,
		Property_InputActionToggleOverlay3,
		Property_InputActionToggleOverlay4,
		Property_InputActionToggleOverlay5,
		Property_InputQuit,
		Property_InputShowPolygons,
		Property_InputToggleNormals,
		Property_InputToggleTangents,
		Property_InputToggleBoundingBox,
		Property_InputToggleCaptions,
		Property_InputSetThreadCount1,
		Property_InputSetThreadCount2,
		Property_InputSetThreadCount4,
		Property_InputSetThreadCountMax,
		Property_Count
	};

	static const char*                  sm_kapszPropertyNames[];
	static const Properties::Property   sm_kaDefaultProperties[];

	//
	// All of the devices attached to the PC
	//
#define MAX_INPUT_DEVICES 5
	u32                             m_nDevices;

	//LPDIRECTINPUTDEVICE8            m_pInputDevices[MAX_INPUT_DEVICES];
};

#endif // INPUTSCENE_H_