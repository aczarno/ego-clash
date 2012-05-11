#pragma once

#include "ObjectGUI.h"

class OGREGraphicsScene;

///////////////////////////////////////////////////////////////////////////////
/// <summary>
///   This is the base class for a GUI type window. It consists of a colored
///   background with a caption and body text.
/// </summary>
///////////////////////////////////////////////////////////////////////////////
class OGREGraphicsObjectThreadStats: public OGREGraphicsObjectGUI
{
	friend OGREGraphicsScene;

protected:

	OGREGraphicsObjectThreadStats( ISystemScene* pSystemScene, pcstr pszName );
	~OGREGraphicsObjectThreadStats( void );

	/// <summary cref="OGREGraphicsObjectWindow::Initialize">
	///   Implementation of the <c>ISystem::Initialize</c> function.
	/// </summary>
	/// <param name="Properties">Initializes the object with the properties specified by <paramref name="Properties"/>.</param>
	/// <returns>Error.</returns>
	/// <seealso cref="OGREGraphicsObject::Initialize"/>
	virtual Error Initialize( std::vector<Properties::Property> Properties );

	/// <summary cref="OGREGraphicsObjectWindow::GetProperties">
	///   Implementation of the <c>ISystem::GetProperties</c> function.
	/// </summary>
	/// <param name="Properties">Gets the properties of the object</param>
	/// <seealso cref="ISystem::GetProperties"/>
	virtual void GetProperties( Properties::Array& Properties );

	/// <summary cref="OGREGraphicsObjectWindow::SetProperties">
	///   Implementation of the <c>ISystem::SetProperties</c> function.
	/// </summary>
	/// <param name="Properties">Sets the properties of the object</param>
	/// <seealso cref="ISystem::SetProperties"/>
	virtual void SetProperties( Properties::Array Properties );

	/// <summary cref="OGREGraphicsObjectWindow::GetDesiredSystemChanges">
	///   Implementation of the <c>IGeometryObject::GetDesiredSystemChanges</c> function.
	/// </summary>
	/// <returns>System::Types::BitMask - System changes desired by the object.</returns>
	/// <seealso cref="ISystem::GetSystemType"/>
	virtual System::Types::BitMask GetDesiredSystemChanges(void);

	/// <summary cref="OGREGraphicsObjectWindow::ChangeOccurred">
	///   Implementation of the <c>IObserver::ChangeOccurred</c> function.
	/// </summary>
	/// <param name="pSubject">Subject of this notification.</param>
	/// <param name="ChangeType">Type of notification for this object.</param>
	/// <returns>Error.</returns>
	/// <seealso cref="ISystem::ChangeOccurred"/>
	virtual Error ChangeOccurred(ISubject* pSubject, System::Changes::BitMask ChangeType);

	/// <summary cref="OGREGraphicsObjectWindow::SetVisibility">
	///   Enable/disable visibility
	/// </summary>
	/// <param name="bVisible">bool - window is visable?</param>
	void SetVisibility(bool bVisible);

	/// <summary cref="OGREGraphicsObjectChart::ApplyChanges">
	///   Update this window with the given data.
	/// </summary>
	/// <param name="WindowData">const WindowData * - New window data</param>
	/// <seealso cref="OGREGraphicsObjectWindow::ApplyChanges"/>
	virtual void ApplyChanges(const WindowData *);

	virtual void Update(f32 DeltaTime);

protected:

	void updatePerformanceStats();
	void updateCPUStats();
	void addCPUChartPoint(float point);
	void updateWorkloadStats();

	//
	// Window Graphics Object
	//
	enum PropertyTypes
	{
		Property_LayoutFile,
		Property_Position,
		Property_Count
	};

	static pcstr                        sm_kapszPropertyNames[];
	static const Properties::Property   sm_kaDefaultProperties[];

  static const f32										m_secondsPerUpdate;
  f32																	m_secondsSinceLastUpdate;
  i32																	m_framesSinceLastUpdate;

	MyGUI::TabControl*									threadStatsTabControl;
	MyGUI::TabItem*											performanceTab;
	MyGUI::TextBox*											FPSBox;
	MyGUI::TextBox*											threadsBox;
	MyGUI::TextBox*											CPUPercentBox;
	MyGUI::TabItem*											CPUTab;
	MyGUI::TextBox*											totalCPUBox;
	MyGUI::PolygonalSkin*								CPUChart;
	MyGUI::TabItem*											workloadTab;
	MyGUI::TextBox*											systemsBox;

	std::vector<MyGUI::FloatPoint>			points;
};
