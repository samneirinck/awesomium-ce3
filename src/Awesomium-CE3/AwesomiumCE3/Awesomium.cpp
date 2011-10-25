#include "stdafx.h"
#include "Awesomium.h"

CRYREGISTER_CLASS(CAwesomium)

using namespace std;
CAwesomium::CAwesomium() : m_bEnablePlugins(false), m_bVisible(false)
{

}

CAwesomium::~CAwesomium()
{
}

bool CAwesomium::Init(bool enablePlugins)
{
	if (!gEnv || gEnv->pGameFramework)
	{
		gEnv->pLog->LogError("Failed to initialize Awesomium, no gameframework found. This is probably caused by calling the Init method too soon");
		return false;
	}

	// Register our gameframework listener
	gEnv->pGameFramework->RegisterListener(this, "AwesomiumCE3", FRAMEWORKLISTENERPRIORITY_HUD);

	// Set up the base directory
	auto gamefolder = gEnv->pCryPak->GetGameFolder();
	m_gameFolder.reset(awe_string_create_from_ascii(gamefolder, strlen(gamefolder)));
	awe_webcore_set_base_directory(m_gameFolder.get());

	// Initialize Awesomium
	awe_webcore_initialize(enablePlugins, true, false, awe_string_empty(), awe_string_empty(),awe_string_empty(),
		AWE_LL_NORMAL, false, awe_string_empty(), true, awe_string_empty(), awe_string_empty(), awe_string_empty(),
		awe_string_empty(), awe_string_empty(), awe_string_empty(), true, 0, false, false, awe_string_empty());


	// Temp: Move to API
	LoadElement("UI/AmmoDisplay.htm");
	SetVisible(true);
	//

	return true;
}

void CAwesomium::Shutdown()
{
	
}

void CAwesomium::OnPostUpdate(float fDeltaTime)
{
	// We only need to update when the UI is visible
	if (m_bVisible)
	{
		awe_webcore_update();
		for_each(begin(m_uiElements), end(m_uiElements), [&](shared_ptr<CUIElement>& e) {
			if (e->IsVisible())
			{
				e->OnUpdate();
			}
		});
	}
}

void CAwesomium::OnSaveGame(ISaveGame* pSaveGame)
{

}

void CAwesomium::OnLoadGame(ILoadGame* pLoadGame)
{
}

void CAwesomium::OnLevelEnd(const char* nextLevel)
{
}

void CAwesomium::OnActionEvent(const SActionEvent& event)
{
}

void CAwesomium::OnPreRender()
{
}

void CAwesomium::SetVisible(bool visible)
{
	m_bVisible = visible;
}

bool CAwesomium::IsVisible() const
{
	return m_bVisible;
}

int CAwesomium::LoadElement(const char* pathtoHtml)
{
	auto element = make_shared<CUIElement>(pathtoHtml);
	
	m_uiElements.push_back(element);

	return 0;
}