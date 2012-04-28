#ifndef INPUTOBJECT_H_
#define INPUTOBJECT_H_

#include "..\ECInputLib\ECInputManager.h"

class InputSystem;
class InputScene;
///////////////////////////////////////////////////////////////////////////////
/// <summary>
///   Implementation of the ISystemObject interface.
///   See Interfaces\System.h for a definition of the class and its functions.
/// </summary>
///////////////////////////////////////////////////////////////////////////////

class InputObject : public ISystemObject, public IGeometryObject, public IGUIObject, public IBehaviorObject
{
	friend class InputScene;
	friend class InputTask;
protected:
	InputObject( ISystemScene* pSystemScene );
	InputObject( ISystemScene* pSystemScene, pcstr pszType, pcstr pszName);
	virtual ~InputObject( void );

	/// <summary cref="InputObject::GetSystemType">
	///   Implementation of the <c>ISystemObject::GetSystemType</c> function.
	///   Lets this object know when a registered aspects of interest has changed 
	///   (this function will be called when other systems make changes this object should know about).
	/// </summary>
	/// <returns>System::Type - Type of this system.</returns>
	/// <seealso cref="ISystemObject::GetSystemType"/>
	virtual System::Type GetSystemType( void );

	/// <summary cref="InputObject::Initialize">
	///   Implementation of the <c>ISystem::Initialize</c> function.
	/// </summary>
	/// <param name="Properties">Initializes the input object with the properties specified by <paramref name="Properties"/>.</param>
	/// <returns>Error.</returns>
	/// <seealso cref="ISystem::Initialize"/>
	virtual Error Initialize( std::vector<Properties::Property> Properties );

	/// <summary cref="InputObject::GetProperties">
	///   Implementation of the <c>ISystem::GetProperties</c> function.
	/// </summary>
	/// <param name="Properties">Gets the properties of the input object</param>
	/// <seealso cref="ISystem::GetProperties"/>
	void GetProperties( Properties::Array& Properties );

	/// <summary cref="InputObject::SetProperties">
	///   Implementation of the <c>ISystem::SetProperties</c> function.
	/// </summary>
	/// <param name="Properties">Sets the properties of the input object</param>
	/// <seealso cref="ISystem::SetProperties"/>
	void SetProperties( Properties::Array Properties );

	/// <summary cref="InputObject::GetDesiredSystemChanges">
	///   Implementation of the <c>IGeometryObject::GetDesiredSystemChanges</c> function.
	/// </summary>
	/// <returns>System::Types::BitMask - System changes desired by the input object.</returns>
	/// <seealso cref="ISystemObject::GetSystemType"/>
	virtual System::Types::BitMask GetDesiredSystemChanges( void );

	/// <summary cref="InputObject::ChangeOccurred">
	///   Lets this object know when a registered aspects of interest has changed 
	/// </summary>
	/// <param name="pSubject">Subject of this notification.</param>
	/// <param name="ChangeType">Type of notification for this object.</param>
	/// <returns>Error.</returns>
	/// <seealso cref="IObserver::ChangeOccurred"/>
	virtual Error ChangeOccurred( ISubject* pSubject, System::Changes::BitMask ChangeType );

	/// <summary cref="InputObject::GetPotentialSystemChanges">
	///   Implementation of the <c>ISubject::GetPotentialSystemChanges</c> function.
	/// </summary>
	/// <returns>System::Changes::BitMask - Returns systems changes possible for this input.</returns>
	/// <seealso cref="ISubject::GetPotentialSystemChanges"/>
	virtual System::Changes::BitMask GetPotentialSystemChanges( void );

public:
	/// <summary cref="IGeometryObject::GetPosition">
	///   Implementation of the IGeometryObject GetPosition function.
	/// </summary>
	virtual const Math::Vector3* GetPosition( void );

	/// <summary cref="IGeometryObject::GetOrientation">
	///   Implementation of the IGeometryObject GetOrientation function.
	/// </summary>
	virtual const Math::Quaternion* GetOrientation( void );

  /// <summary cref="AIObject::GetBehavior">
  ///   Implementation of the <c>IBehaviorObject::GetBehavior</c> function.
  /// </summary>
  /// <returns>Returns the current behavior of this AI object.</returns>
  /// <seealso cref="IBehaviorObject::GetScale"/>
  virtual const Behavior GetBehavior( void );
protected:
	/// <summary cref="IGeometryObject::GetScale">
	///   Implementation of the IGeometryObject GetScale function.
	/// </summary>
	virtual const Math::Vector3* GetScale( void );

	/// <summary cref="IGUIObject::GetWindowData">
	///   Implementation of the IGUIObject GetWindowData function.
	/// </summary>
	virtual const WindowData* GetWindowData( void );

	/// <summary cref="AIObject::SetBehavior">
  ///   Set the current behavior for this AI object.  
  ///   This will notify other systems of the changed behavior.
  /// </summary>
  /// <param name="Behavior">The desired behavior.</param>
  void SetBehavior( Interface::Behavior Behavior );

	void Update(f32 deltaTime);
	void SetKeys();

	Math::Vector3                       m_Position;

	// NOTE: m_Orientation is not really storing a Quaternion.  The data structure is being
	//       used to store pitch and yaw information.
	Math::Quaternion                    m_Orientation;

	Interface::Behavior									m_Behavior;

	f32                                 m_Yaw;
	f32                                 m_Pitch;
	f32                                 m_Roll;

	static pcstr                        sm_kapszTypeNames[];

	enum Types
	{
		Type_Controlled, Type_GUI
	};
	Types                               m_Type;
	bool																m_bVisible;

	WindowData                          m_LayoutData;

	std::string                         m_sName;
	int                                 m_nFunctionKey;

	f32																	m_nMoveLeftRight;
  f32																	m_nOldLeft;
  f32																	m_nOldRight;

	// Activated move information
	struct MoveDetails
	{
		CMove		Move;
		float		RecordedTime;
	};

	float																m_RunTime;

	CECInputManager*										m_Input;
	std::list<MoveDetails>							m_Moves;

	std::map<const char*, std::string>	m_HotKeys;

	CMoveMap														m_AvailableMoves;

	enum PropertyTypes
	{
		Property_FKey,
		Property_Orientation,
		Property_PunchA,
		Property_PunchB,
		Property_PunchC,
		Property_KickA,
		Property_KickB,
		Property_KickC,
		Property_Up,
		Property_Down,
		Property_Back,
		Property_Forward,
		Property_Count,
		Property_Instrumentation
	};

	static const char*                  sm_kapszPropertyNames[];
	static const Properties::Property   sm_kaDefaultProperties[];
};

#endif // INPUTOBJECT_H_