#include "stdafx.h"
#include "Awesomium.h"

#include <Awesomium/awesomium_capi.h>

CRYREGISTER_CLASS(CAwesomium)

CAwesomium::CAwesomium()
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

	gEnv->pGameFramework->RegisterListener(this, "AwesomiumCE3", FRAMEWORKLISTENERPRIORITY_HUD);

	awe_webcore_initialize(enablePlugins, true, false, awe_string_empty(), awe_string_empty(),awe_string_empty(),
		AWE_LL_NORMAL, false, awe_string_empty(), true, awe_string_empty(), awe_string_empty(), awe_string_empty(),
		awe_string_empty(), awe_string_empty(), awe_string_empty(), true, 0, false, false, awe_string_empty());

	return true;
}

void CAwesomium::Shutdown()
{

}

void CAwesomium::OnPostUpdate(float fDeltaTime)
{

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
