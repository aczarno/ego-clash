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
#include "ObjectGUI.h"


#define PSCENE          (reinterpret_cast<OGREGraphicsScene*>(m_pSystemScene))
#define PSYSTEM         (reinterpret_cast<OGREGraphicsSystem*>(m_pSystemScene->GetSystem()))
#define POGRESCENEMGR   (PSCENE->GetOGRESceneManager())
#define POGREROOT       (reinterpret_cast<OGREGraphicsSystem*>(m_pSystem)->GetOGRERoot())

#define ASSERT_EXIST(x, y) if (!x){ASSERT(false); return y;}

#define max(a, b) (((a) > (b)) ? (a) : (b))

pcstr OGREGraphicsObjectGUI::sm_kapszPropertyNames[] =
{
	"LayoutFile"
};

const Properties::Property OGREGraphicsObjectGUI::sm_kaDefaultProperties[] =
{
	Properties::Property( sm_kapszPropertyNames[ Property_LayoutFile ],
	Properties::Values::String,
	Properties::Flags::Valid,
	NULL, NULL, NULL, NULL,
	""),
};

OGREGraphicsObjectGUI::OGREGraphicsObjectGUI(ISystemScene* pSystemScene, pcstr pszName) : OGREGraphicsObject( pSystemScene, pszName )
{
	ASSERT( Property_Count == sizeof sm_kapszPropertyNames / sizeof sm_kapszPropertyNames[ 0 ] );
	ASSERT( Property_Count == sizeof sm_kaDefaultProperties / sizeof sm_kaDefaultProperties[ 0 ] );

	/*m_Type          = OGREGraphicsObject::Type_Window;
	m_pWindow       = NULL;
	m_pTextAreaBody = NULL;
	m_pTextAreaBody = NULL;
	m_nRed          = 0;
	m_nGreen        = 0;
	m_nBlue         = 255;
	m_nAlpha        = 127;

	// 0.03f == 33 lines max on the screen.
	m_CharHeight  = 0.03f;*/
}

OGREGraphicsObjectGUI::~OGREGraphicsObjectGUI(void)
{
	//POGRESCENEMGR->destroyManualObject(m_pManualBackground);
	//POGRESCENEMGR->destroyManualObject(m_pManualForeground);
}



//-----------------------------------------------------------------------------
//
// OGREGraphicsObjectWindow::Initialize
//
// Create the two components of a window. The colored background (Panel) and the
// textual portion (TextArea). Attaches the panel element to the overlay and the
// text area element to the panel element.
//
//-----------------------------------------------------------------------------
Error OGREGraphicsObjectGUI::Initialize(
																				std::vector<Properties::Property> Properties
																				)
{
	Error Err;

	ASSERT( !m_bInitialized );

	Err = Errors::Failure;

	OGREGraphicsObject::Initialize(Properties);


	//----------------------------------------------------------------------------
	// Get our properties that were defined in the .cdf.
	//
	SetProperties(Properties);



	//-------------------------------------------------------------------------
	// Note that we are successful (of course we are!)
	//
	Err = Errors::Success;
	return Err;
}


void OGREGraphicsObjectGUI::GetProperties(
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


void OGREGraphicsObjectGUI::SetProperties(Properties::Array Properties)
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
				//m_nRed   = it->GetInt32(0);
				//m_nGreen = it->GetInt32(1);
				//m_nBlue  = it->GetInt32(2);
				//m_nAlpha = it->GetInt32(3);
				//            }
				//            else if ( sName == sm_kapszPropertyNames[Property_Position] )
				//           {
				//m_Left = it->GetFloat32(0);
				//m_Top  = it->GetFloat32(1);
				//           }
				//  else if ( sName == sm_kapszPropertyNames[Property_Size] )
				//           {
				//m_Width = it->GetFloat32(0);
				//m_Height = it->GetFloat32(1);
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
void OGREGraphicsObjectGUI::SetVisibility(bool bVisible)
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
// OGREGraphicsObjectWindow::SetCaption
//
// Changes the caption of the window.
//
//-----------------------------------------------------------------------------
void OGREGraphicsObjectGUI::SetCaption(std::string szText)
{
	/*if (m_pTextAreaCaption) {
	m_pTextAreaCaption->setCaption(szText);
	}*/
	return;
}

//-----------------------------------------------------------------------------
//
// OGREGraphicsObjectWindow::SetText
//
// Changes the text that is displayed in the window.
//
//-----------------------------------------------------------------------------
void OGREGraphicsObjectGUI::SetText(std::string szText)
{
	/*if (m_pTextAreaBody) {
	m_pTextAreaBody->setCaption(szText);
	}*/
	return;
}

//-----------------------------------------------------------------------------
//
// OGREGraphicsObjectWindow::ApplyChanges
//
// Makes changes to the window.
//
//-----------------------------------------------------------------------------
void OGREGraphicsObjectGUI::ApplyChanges(const WindowData *pData)
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
System::Types::BitMask OGREGraphicsObjectGUI::GetDesiredSystemChanges(void)
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
Error OGREGraphicsObjectGUI::ChangeOccurred(
	ISubject* pSubject,
	System::Changes::BitMask ChangeType
	)
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
