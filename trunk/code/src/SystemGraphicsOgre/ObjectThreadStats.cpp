//
// extern includes
//
#pragma warning( push, 0 )
// Temporarily switching warning level to 0 to ignore warnings in extern/Ogre
#include "Ogre.h"
#include <OgreBorderPanelOverlayElement.h>
#include <OgreHardwarePixelBuffer.h>
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
using namespace Interface;

//
// Ogre system includes
//
#include "System.h"
#include "Scene.h"
#include "Object.h"
#include "ObjectThreadStats.h"


#define PSCENE          (reinterpret_cast<OGREGraphicsScene*>(m_pSystemScene))
#define PSYSTEM         (reinterpret_cast<OGREGraphicsSystem*>(m_pSystemScene->GetSystem()))
#define POGRESCENEMGR   (PSCENE->GetOGRESceneManager())
#define POGREROOT       (reinterpret_cast<OGREGraphicsSystem*>(m_pSystem)->GetOGRERoot())

#define ASSERT_EXIST(x, y) if (!x){ASSERT(false); return y;}

#define max(a, b) (((a) > (b)) ? (a) : (b))

#define NUM_POINTS 100

extern ManagerInterfaces       g_Managers;

// Define update constants
const f32 OGREGraphicsObjectThreadStats::m_secondsPerUpdate = 1.0f;

pcstr OGREGraphicsObjectThreadStats::sm_kapszPropertyNames[] =
{
	"LayoutFile", "Position"
};

const Properties::Property OGREGraphicsObjectThreadStats::sm_kaDefaultProperties[] =
{
	Properties::Property( sm_kapszPropertyNames[ Property_LayoutFile ],
	Properties::Values::String,
	Properties::Flags::Valid,
	NULL, NULL, NULL, NULL,
	""),

	Properties::Property( sm_kapszPropertyNames[ Property_Position ],
                          VALUE1x2( Properties::Values::Float32 ),
                          Properties::Flags::Valid,
                          NULL, NULL, NULL, NULL,
                          0.0f ),
};

OGREGraphicsObjectThreadStats::OGREGraphicsObjectThreadStats(ISystemScene* pSystemScene, pcstr pszName) : OGREGraphicsObjectGUI( pSystemScene, pszName )
{
	ASSERT( Property_Count == sizeof sm_kapszPropertyNames / sizeof sm_kapszPropertyNames[ 0 ] );
	ASSERT( Property_Count == sizeof sm_kaDefaultProperties / sizeof sm_kaDefaultProperties[ 0 ] );

	m_Type = OGREGraphicsObject::Type_ThreadStats;

	m_secondsSinceLastUpdate = 0.0f;
	m_framesSinceLastUpdate = 0;

	threadStatsTabControl = NULL;
	performanceTab = NULL;
	FPSBox = NULL;
	threadsBox = NULL;
	CPUPercentBox = NULL;
	CPUTab = NULL;
	CPUChart = NULL;
	totalCPUBox = NULL;
	workloadTab = NULL;
	systemsBox = NULL;
}

OGREGraphicsObjectThreadStats::~OGREGraphicsObjectThreadStats(void)
{
}

Error OGREGraphicsObjectThreadStats::Initialize(std::vector<Properties::Property> Properties)
{
	Error Err;

	ASSERT( !m_bInitialized );

	Err = Errors::Failure;

	OGREGraphicsObject::Initialize(Properties);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/graphics/GUI/Common/Tools", "FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, false);
	MyGUI::ResourceManager::getInstance().load("FrameworkSkin.xml");

	//----------------------------------------------------------------------------
	// Get our properties that were defined in the .cdf.
	//
	SetProperties(Properties);


	MyGUI::IntSize chartMax = CPUChart->getSize();
	points.resize(NUM_POINTS);
	for(int i=0; i<NUM_POINTS; i++)
		points[i] = MyGUI::FloatPoint(i*0.01*chartMax.width,chartMax.height);

	//CPUChart->castType<MyGUI::Widget>()->setColour(MyGUI::Colour::White);
	CPUChart->setWidth(2.0f);

	//-------------------------------------------------------------------------
	// Note that we are successful (of course we are!)
	//
	Err = Errors::Success;
	return Err;
}


void OGREGraphicsObjectThreadStats::GetProperties(Properties::Array& Properties)
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
	// Modify the default values.
	//
	/*    if (m_pWindow)
	{
	Properties[iProperty + Property_Color].SetValue(0, m_nRed);
	Properties[iProperty + Property_Color].SetValue(1, m_nGreen);
	Properties[iProperty + Property_Color].SetValue(2, m_nBlue);
	Properties[iProperty + Property_Color].SetValue(3, m_nAlpha);

	Properties[iProperty + Property_Position].SetValue(0, m_pWindow->getLeft());
	Properties[iProperty + Property_Position].SetValue(0, m_pWindow->getTop());

	Properties[iProperty + Property_Size].SetValue(0, m_pWindow->getWidth());
	Properties[iProperty + Property_Size].SetValue(0, m_pWindow->getHeight());
	}*/
}


void OGREGraphicsObjectThreadStats::SetProperties(Properties::Array Properties)
{
	//
	// Read in the properties.
	//
	for ( Properties::Iterator it=Properties.begin(); it != Properties.end(); it++ )
	{
		if ( it->GetFlags() & Properties::Flags::Valid )
		{
			std::string sName = it->GetName();

			if ( sName == sm_kapszPropertyNames[Property_LayoutFile] )
			{
				widgets = MyGUI::LayoutManager::getInstance().loadLayout(it->GetString(0));

				// Grab all of our widgets
				for(MyGUI::VectorWidgetPtr::iterator iter = widgets.begin(); iter != widgets.end(); iter++)
				{
					const std::string name = (*iter)->getName();

					if(name == "ThreadStats")
						threadStatsTabControl = (*iter)->castType<MyGUI::TabControl>();
				}

				// Get references to our required components.
				unsigned numChildren = threadStatsTabControl->getChildCount();
				for(unsigned i=0; i<numChildren; i++)
				{
					const std::string name = threadStatsTabControl->getChildAt(i)->getName();
					if(name == "PerformanceTab")
					{
						performanceTab = threadStatsTabControl->getChildAt(i)->castType<MyGUI::TabItem>();
						FPSBox = performanceTab->getChildAt(0)->castType<MyGUI::TextBox>();
						threadsBox = performanceTab->getChildAt(1)->castType<MyGUI::TextBox>();
						CPUPercentBox = performanceTab->getChildAt(2)->castType<MyGUI::TextBox>();
					}
					else if(name == "CPUTab")
					{
						CPUTab = threadStatsTabControl->getChildAt(i)->castType<MyGUI::TabItem>();
						totalCPUBox = CPUTab->getChildAt(0)->castType<MyGUI::TextBox>();

						// create widget with skin that contain specific sub skin - PolygonalSkin
						MyGUI::Widget* client = CPUTab->getChildAt(1)->findWidget("CPUChart");
						MyGUI::Widget* widget = client->createWidget<MyGUI::Widget>("PolygonalSkin", MyGUI::IntCoord(MyGUI::IntPoint(), client->getSize()), MyGUI::Align::Stretch);
						// get main subskin
						MyGUI::ISubWidget* main = widget->getSubWidgetMain();
						CPUChart = main->castType<MyGUI::PolygonalSkin>();
					}
					else if(name == "WorkloadTab")
					{
						workloadTab = threadStatsTabControl->getChildAt(i)->castType<MyGUI::TabItem>();
						systemsBox = workloadTab->getChildAt(0)->castType<MyGUI::TextBox>();
					}
				}

				// Check that all our required components have been found.
				if(	!threadStatsTabControl
					|| !performanceTab
					|| !CPUTab
					|| !workloadTab
					|| !FPSBox
					|| !threadsBox
					|| !CPUPercentBox
					|| !systemsBox
					|| !CPUChart
					|| !totalCPUBox)
				{
					ASSERT(false);
				}


			}
			else if(sName == sm_kapszPropertyNames[Property_Position])
			{
				float x = 0.0f;
				float y = 0.0f;

				x = (float)PSYSTEM->GetOGRERenderWindow()->getWidth() * it->GetFloat32(0);
				y = (float)PSYSTEM->GetOGRERenderWindow()->getHeight() * it->GetFloat32(1);

				threadStatsTabControl->setPosition((int)x, (int)y);
			}
			else
			{
				ASSERT(False);
			}

			//
			// Set this property to invalid since it's already been read.
			//
			it->ClearFlag(Properties::Flags::Valid);
		}
	}
}

//-----------------------------------------------------------------------------
//
// OGREGraphicsObjectWindow::SetVisibility
//
// Sets the window's visibility. This also sets the text area's visibility since
// it is attached to the window.
//
//-----------------------------------------------------------------------------
void OGREGraphicsObjectThreadStats::SetVisibility(bool bVisible)
{
	/*if (!m_pWindow)
	return;

	if (bVisible) {
	m_pWindow->show();
	} else {
	m_pWindow->hide();
	}
	m_pManualBackground->setVisible(bVisible);
	m_pManualForeground->setVisible(bVisible);*/

	return;
}

//-----------------------------------------------------------------------------
//
// OGREGraphicsObjectWindow::ApplyChanges
//
// Makes changes to the window.
//
//-----------------------------------------------------------------------------
void OGREGraphicsObjectThreadStats::ApplyChanges(const WindowData *pData)
{
	/*if (!pData)
	return;

	if (pData->nFlags & WINDOW_SHOW)
	{
	SetVisibility(pData->bShow);
	}
	if (pData->nFlags & WINDOW_CAPTION)
	{
	SetCaption(pData->sCaption);
	}
	if (pData->nFlags & WINDOW_BODY)
	{
	SetText(pData->sBody);
	}
	*/
	return;
}

//-----------------------------------------------------------------------------
//
// OGREGraphicsObjectWindow::GetDesiredSystemChanges
//
// Lets the CCM know what changes we would like to know about.
//
//-----------------------------------------------------------------------------
System::Types::BitMask OGREGraphicsObjectThreadStats::GetDesiredSystemChanges(void)
{
	return System::Changes::Graphics::GUI;
}

//-----------------------------------------------------------------------------
//
// OGREGraphicsObjectWindow::ChangeOccurred
//
// When a change is made that we are interested in the CCM calls this method.
// Here we need to get the needed information from the system that posted the
// change.
//
//-----------------------------------------------------------------------------
Error OGREGraphicsObjectThreadStats::ChangeOccurred(ISubject* pSubject,	System::Changes::BitMask ChangeType)
{
	UNREFERENCED_PARAM(pSubject);
	static int i = 0;

	Error Err = Errors::Failure;

	if (ChangeType & (System::Changes::Graphics::GUI))
	{
		const WindowData *pWindowData;

		IGUIObject* pGUIObj = dynamic_cast<IGUIObject*>(pSubject);
		pWindowData = pGUIObj->GetWindowData();
		ApplyChanges(pWindowData);
	}

	Err = Errors::Success;
	return Err;
}

void OGREGraphicsObjectThreadStats::Update(f32 DeltaTime)
{
	// Don't do anything if this window is not visible.
	if (!threadStatsTabControl->getVisible())
		return;

	// Only get it if it has been a while.
	m_framesSinceLastUpdate++;
	m_secondsSinceLastUpdate += DeltaTime;

	if (m_secondsSinceLastUpdate > m_secondsPerUpdate) 
	{
		// Get our most recent performance statistics
		if(performanceTab->getVisible())
			updatePerformanceStats();

		//if(CPUTab->getVisible())
			updateCPUStats();

		if(workloadTab->getVisible())
			updateWorkloadStats();

		// Start counting again toward the next update.
		m_secondsSinceLastUpdate = 0.0f;
		m_framesSinceLastUpdate = 0;
	}
}

void OGREGraphicsObjectThreadStats::updatePerformanceStats()
{
	// Get instrumentation updates.
	IService::IInstrumentation& inst = g_Managers.pService->Instrumentation();

	// Get the basic stats: average FPS of recent frames, and thread count.
	f32 frameRate = inst.getCurrentFPS();
	i32 activeThreads = inst.getActiveThreadCount();

	// Format the start of the stream.
	std::stringstream outputStream;
	outputStream << "FPS: " << (int)frameRate;
	FPSBox->setCaption(outputStream.str());
	outputStream.str(std::string());

	outputStream << "Thread(s): " << activeThreads;
	threadsBox->setCaption(outputStream.str());
	outputStream.str(std::string());

	// One counter per processor, plus one for _Total.
	i32 numCounters = inst.getNumCounters();
	f64* CPUPercent = new f64[numCounters];
	if (CPUPercent == NULL) 
		return;

	inst.getCPUCounters( CPUPercent );

	// Get all individual CPU counters; don't show the last one ("Total") because it's shown elsewhere.
	for (int i = 0; i < numCounters-1; i++) 
	{
		//outputStream << "\n";
		// This code "guesses" at the order of the counters, and figures that counters are passed
		// in the order 0-n, Total.  This could be made more automatic, but we'd need 
		// instrumentation code to tell us the actual order.
		//
		// Processors are numbered from 0.  Number them from 1 here to be a bit more user friendly.
		outputStream << " CPU " << i+1 << ": " << (int)CPUPercent[i] << "%\n";
	}
	delete [] CPUPercent;

	//FPSBox->setCaption("FPS: " + (int)frameRate);
	//threadsBox->setCaption("Thread(s): " + activeThreads);
	CPUPercentBox->setCaption(outputStream.str());
}

void OGREGraphicsObjectThreadStats::updateCPUStats()
{
	// Get instrumentation updates.
	IService::IInstrumentation& inst = g_Managers.pService->Instrumentation();

	// One counter per processor, plus one for _Total.
	i32 numCounters = inst.getNumCounters();
	f64* CPUPercent = new f64[numCounters];
	if (CPUPercent == NULL)
		return;
	inst.getCPUCounters( CPUPercent );

	// Arrange the data for display.  We have new data and a new caption.
	//m_windowData.nDataPoint = (f32)CPUPercent[numCounters-1];
	addCPUChartPoint((float)CPUPercent[numCounters-1]);
	CPUChart->setPoints(points);

	std::stringstream captionStream;
	captionStream << "Total CPU: " << (int)CPUPercent[numCounters-1] << "%";
	totalCPUBox->setCaption(captionStream.str());
	//m_windowData.sCaption = captionStream.str();

	// Free up locally-allocated stuff.
	delete [] CPUPercent;

//return &m_windowData;
	//CPUChart->getTexture()
}

void OGREGraphicsObjectThreadStats::addCPUChartPoint(float point)
{
	int i;

	MyGUI::IntSize chartSize = CPUChart->getSize();
	//-------------------------------------------------------------------------
	// Get rid of our oldest piece of data and add in the newest.
	//
	for(i=0; i<NUM_POINTS-1; i++)
	{
		points[i] = points[i+1];
		points[i].left = i*0.01*chartSize.width;
	}

	points[i] = MyGUI::FloatPoint(i*0.01*chartSize.width, chartSize.height - (point*0.01*chartSize.height));

	//UpdateChart();

	return;
}

void OGREGraphicsObjectThreadStats::updateWorkloadStats()
{
	// Get instrumentation updates.
	IService::IInstrumentation& inst = g_Managers.pService->Instrumentation();

	// Get access to Audio system for audio data
	ISystem* pAudioSystem = (ISystem*) g_Managers.pService->SystemAccess().GetSystem( System::Types::Audio );

	// Format the start of the stream.
	std::stringstream outputStream;
	i32 cpuCount = inst.getCPUCount();
	i32 jobCount = inst.getJobCount();

	// Get the workload job ratios.
	f32* jobRatios = new f32[jobCount];
	if ( jobRatios == NULL )
		return;

	inst.getJobRatios( jobRatios );

	// Hook up the display names.
	bool indexUsed;
	for (int i = 0; i < jobCount; i++) 
	{
		indexUsed = false;
		switch (i) {
			case System::TypeIndices::Geometry:
				outputStream << " " << System::DisplayNames::Geometry << ": ";
				indexUsed = true;
				break;

			case System::TypeIndices::Graphics:
				outputStream << "\n " << System::DisplayNames::Graphics << ": ";
				indexUsed = true;
				break;

			case System::TypeIndices::PhysicsCollision:
				outputStream << "\n " << System::DisplayNames::PhysicsCollision << ": ";
				indexUsed = true;
				break;

			case System::TypeIndices::Audio:
				outputStream << "\n " << System::DisplayNames::Audio << ": ";
				indexUsed = true;
				break;

			case System::TypeIndices::Input:
				outputStream << "\n " << System::DisplayNames::Input << ": ";
				indexUsed = true;
				break;

			case System::TypeIndices::AI:
				outputStream << "\n " << System::DisplayNames::AI << ": ";
				indexUsed = true;
				break;

			case System::TypeIndices::Animation:
				outputStream << "\n " << System::DisplayNames::Animation << ": ";
				indexUsed = true;
				break;

			case System::TypeIndices::Scripting:
				outputStream << "\n " << System::DisplayNames::Scripting << ": ";
				indexUsed = true;
				break;

			default:
				// Show the custom types, if we've found them.
				/*if ( i == (int)System::Types::GetIndex ( System::Types::MakeCustom ( 0 ) ) ) {
				outputStream << "\n " << System::DisplayNames::Tree << ": ";
				indexUsed = true;
				} else if ( i == (int)System::Types::GetIndex ( System::Types::MakeCustom ( 2 ) ) ) {
				outputStream << "\n " << System::DisplayNames::Fire << ": ";
				indexUsed = true;
				} else {
				// There are lots of unused system type slots; don't display
				// them unless we add a new system type.

				// Consider adding some special handing of System::Types::Null, in case
				// somebody accidentally files some job workloads there.

				// DONOTHING
				}*/

				break;
		}

		// The job array has a few slots we don't use.  If we aren't keeping stats for this index,
		// don't try to display it.
		if ( indexUsed ) {
			// Job ratios show the amount of one available core that a job is using, so they're a kind
			// of utilization number.  On a 4 core machine, they can vary between 0 and 4.
			// Scale it here to a percent of the overall workload.
			f32 rawPercent;

			// Audio is a special case; it has its own internal thread not scheduled or tracked
			// through the job system, so we need to get stats differently (directly from the
			// audio system).
			if (i == System::Types::Audio) {
				rawPercent = pAudioSystem->GetCPUUsage();
			} else {
				rawPercent = ((jobRatios[i] * 100.0f)/(f32)cpuCount);
			}

			// Round to nearest integer, then make sure each subsystem has something to report.
			i32 percent = (i32)( rawPercent + 0.5f );
			if (percent == 0) {
				// A zero makes it look like we're claiming a subsystem is totally idle, so just claim 1%.
				outputStream << "1%";  // In this font, "<" looks like an arrow and "~" looks like a "-".  Neither looks right.
			} else {
				outputStream << percent << "%";
			}
		}
	}

	// Clean up.
	delete [] jobRatios;

	systemsBox->setCaption(outputStream.str());
}