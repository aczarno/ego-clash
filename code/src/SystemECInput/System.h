#ifndef INPUTSYSTEM_H_
#define INPUTSYSTEM_H_

class InputSystem : public ISystem
{
public:
	InputSystem();
	virtual ~InputSystem();

protected:
	/// <summary>
	///   Gets the name of the system.  Only custom systems can return a custom name.
	///   <para>
	///	    Non-custom system must return a pre-defined name in Systems::Names that matches with the
	////     type.
	///	  </para>
	/// </summary>
	/// <returns>The name of the system.</returns>
	virtual pcstr GetName( void );

	/// <summary>
	///   Gets the system type for this system.
	/// </summary>
	/// <remarks>
	///   This must function even w/o initialization.
	/// </remarks>
	/// <returns>The type of the system.</returns>
	virtual System::Type GetSystemType( void );

	/// <summary>
	///   One time initialization function for the system.
	/// </summary>
	/// <param name="Properties">Property structure array to fill in.</param>
	/// <returns>An error code.</returns>
	virtual Error Initialize( std::vector<Properties::Property> Properties );

	/// <summary>
	///   Gets the properties of this system.
	/// </summary>
	/// <remarks>
	///   Implementation must work prior to initialization.
	/// </remarks>
	/// <param name="Properties">Property structure array to fill</param>
	virtual void GetProperties( std::vector<Properties::Property>& Properties );

	/// <summary>
	///   Sets the properties for this system.
	/// </summary>
	/// <param name="Properties">Property structure array to get values from.</param>
	virtual void SetProperties( std::vector<Properties::Property> Properties );

	/// <summary>
	///   Creates a system scene for containing system objects.
	/// </summary>
	/// <returns>The newly create system scene.</returns>
	virtual ISystemScene* CreateScene( void );

	/// <summary>
	///   Destroys a system scene.
	/// </summary>
	/// <param name="pSystemScene">The scene to destroy. Any objects within are destroyed.</param>
	/// <returns>An error code.</returns>
	//
	virtual Error DestroyScene( ISystemScene* pSystemScene );

	void SetKeys();

	enum HotKeyTypes
  {
    HotKey_Up,
    HotKey_Down,
    HotKey_Left,
    HotKey_Right,
		HotKey_LP,
		HotKey_MP,
		HotKey_HP,
		HotKey_LK,
		HotKey_MK,
		HotKey_HK,
		HotKey_Start,
		HotKey_Select,
		HotKey_Home,
    HotKey_ResetView,
    HotKey_Quit,
    HotKey_PolygonMode,
    HotKey_ShowNormals,
    HotKey_ShowTangents,
    HotKey_ShowBoundingBox,
    HotKey_ShowCaptions,
    HotKey_SetThreadCountTo1,
    HotKey_SetThreadCountTo2,
    HotKey_SetThreadCountTo4,
    HotKey_SetThreadCountToMax,
    HotKey_ToggleOverlay1,
    HotKey_ToggleOverlay2,
    HotKey_ToggleOverlay3,
    HotKey_ToggleOverlay4,
    HotKey_ToggleOverlay5,
    HotKey_Count
  };

	static const char* sm_kapszPropertyNames[];
  static const Properties::Property sm_kaDefaultProperties[];

	
public:
	struct HotKey 
	{
		std::string sKey;
		bool bCtrl;
  };
  
	std::map<const char*, HotKey*> mHotKeys;
};

#endif // INPUTSYSTEM_H_