#include "stdafx.h"
#include "UIElement.h"

#include <IGame.h>
#include <IGameFramework.h>
#include <IActorSystem.h>

using namespace std;

awe_string* CUIElement::s_javascriptObjectName = awe_string_create_from_ascii("awesomiumce3", strlen("awesomiumce3"));
int __count = 0;

CUIElement::CUIElement(const char* pathToHtml) : m_pathToHtml(pathToHtml), m_bVisible(true), m_textureId(InvalidTexture), m_width(1024), m_height(1024)
{
	// Create string from path
	m_pathToHtmlString = awe_string_create_from_ascii(pathToHtml, strlen(pathToHtml));

	// Create our view
	m_pWebview = awe_webcore_create_webview(m_width, m_height, false);

	// Create our javascript object
	awe_webview_create_object(m_pWebview, s_javascriptObjectName);
	
	// Temporary tests
	SetObjectProperty("version", "1.0.0.0");
	SetObjectProperty("author", "ins");

	// Load the actual page
	awe_webview_load_file(m_pWebview, m_pathToHtmlString, awe_string_empty());

	awe_webview_set_transparent(m_pWebview, true);
	__count++;
}


CUIElement::~CUIElement()
{
	//awe_webview_destroy(m_pWebview);	
	awe_string_destroy(m_pathToHtmlString);
}

void CUIElement::OnUpdate()
{
	if (awe_webview_is_dirty(m_pWebview))
	{
		auto render = awe_webview_render(m_pWebview);
		
		// The buffer is managed by Awesomium, we do not need to clean this up ourselves
		m_pRenderBuffer = awe_renderbuffer_get_buffer(render);

		if (m_textureId == InvalidTexture)
		{
				m_textureId = CreateTexture();
					auto entity = gEnv->pEntitySystem->FindEntityByName("cabin_table1");

					auto material = entity->GetMaterial();

			
		}  else {
			UpdateTexture();
		}

		/*auto actor = gEnv->pGame->GetIGameFramework()->GetClientActor();

		if (actor)
		{
			auto cmd = "updateHealth";
			auto cmdString = awe_string_create_from_ascii(cmd, strlen(cmd));
			//awe_js_
			auto val = awe_jsvalue_create_integer_value((int)actor->GetHealth());
			
			auto arr = awe_jsarray_create((const awe_jsvalue**)&val, 1);

			awe_webview_call_javascript_function(m_pWebview, awe_string_empty(), cmdString, arr, awe_string_empty());
			// ;
			awe_string_destroy(cmdString);

		}*/

	}
}

void CUIElement::SetObjectProperty(const char* propertyName, const char* propertyValue)
{
	auto propertyNameString = awe_string_create_from_ascii(propertyName, strlen(propertyName));
	auto propertyValueString = awe_string_create_from_ascii(propertyValue, strlen(propertyValue));
	auto propertyJSValue = awe_jsvalue_create_string_value(propertyValueString);

	
	awe_webview_set_object_property(m_pWebview, s_javascriptObjectName, propertyNameString, propertyJSValue);

	awe_jsvalue_destroy(propertyJSValue);
	awe_string_destroy(propertyValueString);
	awe_string_destroy(propertyNameString);
}

void CUIElement::UpdateTexture()
{
	gEnv->pRenderer->UpdateTextureInVideoMemory(m_textureId, const_cast<unsigned char*>(m_pRenderBuffer), 0, 0, m_width, m_height, eTF_A8R8G8B8);

}

int i=0;

int CUIElement::CreateTexture()
{
	auto material = gEnv->p3DEngine->GetMaterialManager()->FindMaterial("cemono/Game/Levels/Forest/TestMaterial");
	if (material)
	{
		gEnv->pEntitySystem->FindEntityByName("screen1")->SetMaterial(material);
		return material->GetShaderItem().m_pShaderResources->GetTexture(EFTT_DIFFUSE)->m_Sampler.m_pITex->GetTextureID();
	}

	return -1;

	//return gEnv->pRenderer->SF_CreateTexture(m_width, m_height, 0, const_cast<unsigned char*>(m_pRenderBuffer), eTF_A8R8G8B8, 0);
}

void CUIElement::SetVisible(bool visible)
{
	m_bVisible = visible;
}

bool CUIElement::IsVisible() const
{
	return m_bVisible;
}

int CUIElement::GetTextureId() const
{
	return m_textureId;
}