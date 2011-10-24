#pragma once
#include "Headers/IAwesomium.h"

#include <CryExtension/Impl/ClassWeaver.h>
#include <IGameFramework.h>

class CAwesomium : public IAwesomium, public IGameFrameworkListener
{
	CRYINTERFACE_BEGIN()
	CRYINTERFACE_ADD(IAwesomium)
	CRYINTERFACE_END()
	
	CRYGENERATE_SINGLETONCLASS(CAwesomium, "Awesomium", 0x0, 0x1)

public:
	// IAwesomium interface
	virtual bool Init(bool enablePlugins) override;
	virtual void Shutdown() override;
	// -IAwesomium

	// IGameFrameworkListener
	virtual void OnPostUpdate(float fDeltaTime) override;
	virtual void OnSaveGame(ISaveGame* pSaveGame) override;
	virtual void OnLoadGame(ILoadGame* pLoadGame) override;
	virtual void OnLevelEnd(const char* nextLevel) override;
	virtual void OnActionEvent(const SActionEvent& event) override;
	virtual void OnPreRender() override;
	// -IGameFrameworkListener



protected:
	bool m_bEnablePlugins;
};