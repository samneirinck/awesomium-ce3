#include "stdafx.h"
#include "Awesomium.h"
#include <IUIDraw.h>
#include <IEntitySystem.h>

CRYREGISTER_CLASS(CAwesomium)

using namespace std;
CAwesomium::CAwesomium() : m_bEnablePlugins(false), m_bVisible(false)
{

}

CAwesomium::~CAwesomium()
{
	awe_webcore_shutdown();
}

void MaterialCommand(IConsoleCmdArgs *pArgs)
{
	auto entity = gEnv->pEntitySystem->FindEntityByName(pArgs->GetArg(1));
	if (entity)
	{
		auto material = entity->GetMaterial();

		if (material)
		{
			gEnv->pLog->LogAlways("Found material %s", material->GetName());
		} else {
		}
	}
}


bool CAwesomium::Init(bool enablePlugins)
{
	if (!gEnv || !gEnv->pGame->GetIGameFramework())
	{
		gEnv->pLog->LogError("Failed to initialize Awesomium, no gameframework found. This is probably caused by calling the Init method too soon");
		return false;
	}

	IGameFramework *pGameFramework = gEnv->pGame->GetIGameFramework();

	// Register our gameframework listener
	pGameFramework->RegisterListener(this, "AwesomiumCE3", FRAMEWORKLISTENERPRIORITY_HUD);


	// Initialize Awesomium
	awe_webcore_initialize(enablePlugins, true, false, awe_string_empty(), awe_string_empty(),awe_string_empty(),
		AWE_LL_NORMAL, false, awe_string_empty(), true, awe_string_empty(), awe_string_empty(), awe_string_empty(),
		awe_string_empty(), awe_string_empty(), awe_string_empty(), true, 0, false, false, awe_string_empty());

		// Set up the base directory
	//auto gamefolder = "F:\\Games\\ce3\\Game"; //gEnv->pCryPak->GetGameFolder();
	//m_gameFolder.reset(awe_string_create_from_ascii(gamefolder, strlen(gamefolder)));
	//awe_webcore_set_base_directory(m_gameFolder.get());
	auto dir = awe_webcore_get_base_directory();

	

	awe_webcore_set_base_directory(awe_string_create_from_ascii("F:\\Games\\ce3\\Game", strlen("F:\\Games\\ce3\\Game")));

	// Temp: Move to API
	LoadElement("UI/lowerleft.htm");
	//LoadElement("UI/youtube5.htm");
	SetVisible(true);
	//

	gEnv->pConsole->RegisterInt("aw_t0", 1, 0);
	gEnv->pConsole->RegisterInt("aw_t1", 0, 0);
	gEnv->pConsole->RegisterInt("aw_s0", 0, 0);
	gEnv->pConsole->RegisterInt("aw_s1", 1, 0);
	gEnv->pConsole->AddCommand("aw_material", MaterialCommand);

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

					//gEnv->pRenderer->Draw2dImage(0,0, 1024*((float)600/1024), 1024*((float)800/1024), e->GetTextureId(), gEnv->pConsole->GetCVar("aw_s0")->GetIVal(),gEnv->pConsole->GetCVar("aw_t0")->GetIVal(),gEnv->pConsole->GetCVar("aw_s1")->GetIVal(),gEnv->pConsole->GetCVar("aw_t1")->GetIVal());
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