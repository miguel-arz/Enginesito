#include "SpriteRendererComponent.h"
#include "Render/RenderEngine.h"
#include "Core/Entity.h"

CSpriteRendererComponent::CSpriteRendererComponent() 
	: Super(1u)
{}

//Actua como configure de 
CSpriteRendererComponent::CSpriteRendererComponent(const pugi::xml_node& oRoot)
	: Super(1u)
{
	Vector4 vColor;
	GET_VARIABLE_AS_VECTOR4(vColor, vColor, r, g, b, a, 255, 255, 255, 255);
	m_vColor.r = static_cast<unsigned char>(vColor.x);
	m_vColor.g = static_cast<unsigned char>(vColor.y);
	m_vColor.b = static_cast<unsigned char>(vColor.z);
	m_vColor.a = static_cast<unsigned char>(vColor.w);

	const char* sBlendMode{};
	GET_VARIABLE_VALUE(string, sBlendMode, eBlendMode, "ALPHA");

	if (strcmp(sBlendMode, "ALPHA") == 0)
	{
		m_eBlendMode = BLEND_ALPHA;
	}
	else if (strcmp(sBlendMode, "MULTIPLIED") == 0)
	{
		m_eBlendMode = BLEND_MULTIPLIED;
	}
	else if (strcmp(sBlendMode, "ADDITIVE") == 0)
	{
		m_eBlendMode = BLEND_ADDITIVE;
	}

	GET_VARIABLE_AS_VECTOR4(m_vUVs, vUVs, fU1, fV1, fU2, fV2, 0.f, 0.f, 1.f, 1.f);
	GET_VARIABLE_AS_VECTOR2(m_vSize, fSize, fWidth, fHeight, 0.f, 0.f);
	GET_VARIABLE_AS_VECTOR2(m_vPivot, fPivot, fX, fY, 0.f, 0.f);
	GET_VARIABLE_VALUE(uint, m_uLayer, uLayer, 0);
	GET_VARIABLE_VALUE(string, m_sPath, sTexturePath, "");

}

//------------

void CSpriteRendererComponent::Initialize()
{
	Super::Initialize();
}

//void CSpriteRendererComponent::Configure(pugi::xml_node& _rNode)
//{
//	Super::Configure(_rNode);
//	pugi::xml_node& oRootNode = _rNode;
//
//	Vector4 vColor;
//	GET_VARIABLE_AS_VECTOR4(vColor, vColor, r, g, b, a, 1.f, 1.f, 1.f, 1.f);
//	m_vColor.r = vColor.x;
//	m_vColor.g = vColor.y;
//	m_vColor.b = vColor.z;
//	m_vColor.a = vColor.w;
//
//	GET_VARIABLE_AS_VECTOR4(m_vUVs, vUVs, fU1, fV1, fU2, fV2, 0.f, 0.f, 1.f, 1.f);
//	GET_VARIABLE_AS_VECTOR2(m_vSize, vSize, fWidth, fHeight, 1.f, 1.f);
//	GET_VARIABLE_AS_VECTOR2(m_vPivot, vPivot, fX, fY, 0.5, 0.5);
//	GET_VARIABLE_VALUE(uint, m_uLayer, uLayer, 0u);
//	GET_VARIABLE_VALUE(string, m_sPath, sTexturePath, "");
//
//	const char* sBlendMode = "";
//	GET_VARIABLE_VALUE(string, sBlendMode, eBlendMode, "");
//
//	if (strcmp(sBlendMode, "ALPHA") == 0)
//	{
//		m_eBlendMode = BLEND_ALPHA;
//	}
//	//TODO else if para cada blend type
//
//
//	if (!m_pTexture) 
//	{
//		m_pTexture = CRenderEngine::GetInstance()->LoadTexture2D(m_sPath);
//	}
//}

void CSpriteRendererComponent::Configure()
{
	Super::Configure();

	if (!m_pTexture && !m_sPath.empty())
	{
		m_pTexture = CRenderEngine::GetInstance()->LoadTexture2D(m_sPath.c_str());
	}
}

void CSpriteRendererComponent::Awake()
{
	Super::Awake();

	CRenderEngine::GetInstance()->AddRenderer(this);
}

void CSpriteRendererComponent::BeginPlay()
{
	Super::BeginPlay();
}

void CSpriteRendererComponent::EndPlay()
{
	Super::EndPlay();
}


void CSpriteRendererComponent::Delete()
{
	Super::Delete();
	CRenderEngine::GetInstance()->UnloadTexture2D(m_pTexture);
	CRenderEngine::GetInstance()->RemoveRenderer(this);
}

void CSpriteRendererComponent::Draw()
{
	/*Rectangle oRectDest;
	oRectDest.x = m_pEntity->GetPos().x;
	oRectDest.y = m_pEntity->GetPos().y;
	oRectDest.width = m_vSize.x;
	oRectDest.height = m_vSize.y;


	BeginBlendMode(m_eBlendMode);
	{
		DrawTextureProUV(*m_pTexture, m_vUVs, oRectDest, m_vPivot, m_pEntity->GetRot(), m_vColor);
	}
	EndBlendMode();*/

	Rectangle vDest{ m_pEntity->GetPos().x, m_pEntity->GetPos().y, m_vSize.x, m_vSize.y };

	CRenderEngine::GetInstance()->SetCurrentBlendMode(m_eBlendMode);
	DrawTextureProUV(*m_pTexture, m_vUVs, vDest, m_vPivot, m_pEntity->GetRot(), m_vColor);
}


void CSpriteRendererComponent::SetLayer(unsigned int _uLayer) 
{
	CRenderEngine::GetInstance()->SetLayerDirty();
	m_uLayer = _uLayer;
}