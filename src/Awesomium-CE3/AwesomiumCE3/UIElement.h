#pragma once

#include <Awesomium/awesomium_capi.h>

class CUIElement
{
public:
	CUIElement(const char* pathToHtml);
	virtual ~CUIElement();

	virtual void OnUpdate();
	virtual void SetVisible(bool visible);
	virtual bool IsVisible() const;
	virtual void SetObjectProperty(const char* propertyName, const char* propertyValue);
	virtual int GetTextureId() const;

protected:
	virtual int CreateTexture();
	virtual void UpdateTexture();



	static const int InvalidTexture = -1;
	const char* m_pathToHtml;
	bool m_bVisible;
	int m_textureId;
	int m_width;
	int m_height;

	awe_webview*  m_pWebview;
	awe_string* m_pathToHtmlString;
	const unsigned char* m_pRenderBuffer;


	static awe_string* s_javascriptObjectName;

};

