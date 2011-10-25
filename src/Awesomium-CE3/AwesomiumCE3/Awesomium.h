#pragma once
#include "Headers/IAwesomium.h"
#include "UIElement.h"

#include <IGameFramework.h>
#include <Awesomium/awesomium_capi.h>
#include <CryExtension/Impl/ClassWeaver.h>

class CAwesomium : public IAwesomium, public IGameFrameworkListener
{
	CRYINTERFACE_BEGIN()
		CRYINTERFACE_ADD(IAwesomium)
	CRYINTERFACE_END()
	
	//CRYGENERATE_SINGLETONCLASS(CAwesomium, "Awesomium", 0x2386a062a90e40b4, 0xbb3761084a4e5895)
	CRYGENERATE_CLASS(CAwesomium, "Awesomium", 0x2386a062a90e40b4, 0xbb3761084a4e5895)

public:
	// IAwesomium interface
	virtual bool Init(bool enablePlugins) override;
	virtual void Shutdown() override;
	virtual void SetVisible(bool visible) override;
	virtual bool IsVisible() const override;
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
	bool m_bVisible;
	std::vector<std::shared_ptr<CUIElement>> m_uiElements;
	
	virtual int LoadElement(const char* pathToHtml);


};