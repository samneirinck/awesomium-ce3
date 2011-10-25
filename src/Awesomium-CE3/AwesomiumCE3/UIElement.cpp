#include "stdafx.h"
#include "UIElement.h"

using namespace std;

awe_string* CUIElement::s_javascriptObjectName = awe_string_create_from_ascii("awesomiumce3", strlen("awesomiumce3"));

CUIElement::CUIElement(const char* pathToHtml) : m_pathToHtml(pathToHtml), m_bVisible(true), m_textureId(InvalidTexture), m_width(gEnv->pRenderer->GetWidth()), m_height(gEnv->pRenderer->GetHeight())
{
	// Create string from path
	m_pathToHtmlString.reset(awe_string_create_from_ascii(pathToHtml, strlen(pathToHtml)));

	// Create our view
	m_pWebview.reset(awe_webcore_create_webview(m_width, m_height, false));

	// Create our javascript object
	awe_webview_create_object(m_pWebview.get(), s_javascriptObjectName);
	
	// Temporary tests
	SetObjectProperty("version", "1.0.0.0");
	SetObjectProperty("author", "ins");

	// Load the actual page
	awe_webview_load_file(m_pWebview.get(), m_pathToHtmlString.get(), awe_string_empty());


}


CUIElement::~CUIElement()
{
	
}

void CUIElement::OnUpdate()
{
	if (awe_webview_is_dirty(m_pWebview.get()))
	{
		auto render = awe_webview_render(m_pWebview.get());

		// The buffer is managed by Awesomium, we do not need to clean this up ourselves
		m_pRenderBuffer = awe_renderbuffer_get_buffer(render);

		if (m_textureId == InvalidTexture)
		{
			m_textureId = CreateTexture();
		}  else {
			UpdateTexture();
		}

	}
}

void CUIElement::SetObjectProperty(const char* propertyName, const char* propertyValue)
{
	auto propertyNameString = awe_string_create_from_ascii(propertyName, strlen(propertyName));
	auto propertyValueString = awe_string_create_from_ascii(propertyValue, strlen(propertyValue));
	auto propertyJSValue = awe_jsvalue_create_string_value(propertyValueString);

	
	awe_webview_set_object_property(m_pWebview.get(), s_javascriptObjectName, propertyNameString, propertyJSValue);

	awe_jsvalue_destroy(propertyJSValue);
	awe_string_destroy(propertyValueString);
	awe_string_destroy(propertyNameString);
}

void CUIElement::UpdateTexture()
{
	gEnv->pRenderer->UpdateTextureInVideoMemory(m_textureId, const_cast<unsigned char*>(m_pRenderBuffer), 0, 0, m_width, m_height, eTF_A8R8G8B8);
}

int CUIElement::CreateTexture()
{
	return gEnv->pRenderer->SF_CreateTexture(m_width, m_height, 0, const_cast<unsigned char*>(m_pRenderBuffer), eTF_A8R8G8B8, 0);
}

void CUIElement::SetVisible(bool visible)
{
	m_bVisible = visible;
}

bool CUIElement::IsVisible() const
{
	return m_bVisible;
}