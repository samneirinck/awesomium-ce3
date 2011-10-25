#include "stdafx.h"
#include "UIElement.h"

using namespace std;
CUIElement::CUIElement(const char* pathToHtml) : m_pathToHtml(pathToHtml), m_bVisible(true), m_textureId(InvalidTexture), m_width(gEnv->pRenderer->GetWidth()), m_height(gEnv->pRenderer->GetHeight())
{
	// Create string from path
	m_pathToHtmlString.reset(awe_string_create_from_ascii(pathToHtml, strlen(pathToHtml)));

	// Create our view
	m_pWebview.reset(awe_webcore_create_webview(m_width, m_height, false));

	// Load the actual page
	
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