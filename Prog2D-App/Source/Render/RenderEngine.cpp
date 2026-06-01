#include "RenderEngine.h"
#include "Render/RenderItem.h"

#include "Components/Render/SpriteRendererComponent.h"
#include "../../Prog2D-Raylib/Source/Prog2D-Raylib/raylib.h"


CRenderEngine::STextureData::STextureData(Image& _rImage) 
{
	oTexture = LoadTextureFromImage(_rImage);
	uNumReferences = 1u;
}

CRenderEngine::STextureData::~STextureData()
{
	if (oTexture.id != 0)
	{
		UnloadTexture(oTexture);
		oTexture.id = 0;
	}
}

void CRenderEngine::InitializeRenderer(int _iScreenWidht, int _iScreenHeight, const char* _sName)
{
	m_vWindowSize.x = static_cast<float>(_iScreenWidht);
	m_vWindowSize.y = static_cast<float>(_iScreenHeight);
	m_sTitle = _sName;

	InitWindow(_iScreenWidht, _iScreenHeight, _sName);

	m_bIsLayerDirty = false;
}

void CRenderEngine::DeleteRenderer() 
{
	UnloadAllTextures2D();
}

void CRenderEngine::Draw()
{
	if (m_bIsLayerDirty)
	{
		m_bIsLayerDirty = false;
		sort(m_tRenderers.begin(), m_tRenderers.end(), [](const IRenderItem* _pLeft, const IRenderItem* _pRight)
			{return _pLeft->GetLayer() < _pRight->GetLayer();});

		m_bIsLayerDirty = false;

	}
	BeginDrawing();

	ClearBackground(BLACK);

	for (IRenderItem* pRenderItem : m_tRenderers)
	{
		pRenderItem->Draw();
	}
	EndBlendMode();
	EndDrawing();

	TTextureDatas::iterator it = m_tTextureDatas.begin();

	while (it != m_tTextureDatas.end())
	{
		if (it->uNumReferences == 0u)
		{
			it = m_tTextureDatas.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void CRenderEngine::AddRenderer(IRenderItem* _pRenderItem)
{
	if (!_pRenderItem)
	{
		return;
	}

	for (IRenderItem* pRenderItem : m_tRenderers)
	{
		if (pRenderItem == _pRenderItem)
		{
			return;
		}
	}

	m_tRenderers.emplace_back(_pRenderItem);
	m_bIsLayerDirty = true;
}

void CRenderEngine::RemoveRenderer(IRenderItem* _pRenderItem)
{
	TRenderItems::iterator it;
	for (it = m_tRenderers.begin(); it != m_tRenderers.end(); ++it)
	{
		if (*it == _pRenderItem)
		{
			break;
		}
	}

	if (it != m_tRenderers.end())
	{
		m_tRenderers.erase(it);
	}
}

Texture2D* CRenderEngine::LoadTexture2D(const std::string& _sFilePath)
{
	for (STextureData& rData : m_tTextureDatas)
	{
		if (_sFilePath == rData.sFilePath)
		{

			++rData.uNumReferences;
			return &rData.oTexture;	
		}
	}

	Image oImage = LoadImage(_sFilePath.c_str());

	if (oImage.data == nullptr)
	{
		TraceLog(LOG_ERROR, "Cant load image: %s", _sFilePath.c_str());
		return nullptr;
	}

	m_tTextureDatas.emplace_back(oImage);

	STextureData& rNewData = m_tTextureDatas.back();
	rNewData.sFilePath = _sFilePath;

	UnloadImage(oImage);

	return &rNewData.oTexture;
}

Texture2D* CRenderEngine::LoadTexture2D(Image& _rImage)
{
	m_tTextureDatas.emplace_back(_rImage);
	return &m_tTextureDatas.back().oTexture;
}

Texture2D* CRenderEngine::LoadTexture2D(Texture2D* _pTexture)
{
	if (!_pTexture)
	{
		return _pTexture;
	}

	for (STextureData& rData : m_tTextureDatas)
	{
		if (rData.oTexture.id == _pTexture->id)
		{
			++rData.uNumReferences;
			return &rData.oTexture;
		}
	}
	return _pTexture;
}

void CRenderEngine::UnloadTexture2D(Texture* _pTexture)
{
	TTextureDatas::iterator it = m_tTextureDatas.begin();

	for (;it != m_tTextureDatas.end(); ++it)
	{
		if (&it->oTexture == _pTexture)
		{
			if (it->uNumReferences > 0u)
			{
				--it->uNumReferences;
			}
			break;
		}
	}

	
}

void CRenderEngine::UnloadTexture2D(unsigned int _uTextureId)
{
	TTextureDatas::iterator it = m_tTextureDatas.begin();

	for (;it != m_tTextureDatas.end(); ++it)
	{
		if (it->oTexture. id == _uTextureId)
		{
			if (it->uNumReferences > 0u)
			{
				--it->uNumReferences;
			}
			break;
		}
	}

	
}

void CRenderEngine::UnloadAllTextures2D()
{
	m_tTextureDatas.clear();
}

//void CRenderEngine::AddSpriteRenderer(CSpriteRendererComponent* _pSpriteComp)
//{
//	if (_pSpriteComp)
//	{
//		for (CSpriteRendererComponent* pComp : m_tSpriteRenderers)
//		{
//			if (pComp == _pSpriteComp)
//			{
//				return;
//			}
//		}
//		m_tSpriteRenderers.emplace_back(_pSpriteComp);
//		m_bIsLayerDirty = false;
//
//		
//	}
//}
//
//void CRenderEngine::RemoveSpriteRenderer(CSpriteRendererComponent* _pSpriteComp)
//{
//	TRenderItems::iterator it = m_tSpriteRenderers.begin();
//
//	for (;it != m_tSpriteRenderers.end(); ++it)
//	{
//		if (*it == _pSpriteComp)
//		{	
//			break;
//		}
//	}
//
//	if (it != m_tSpriteRenderers.end())
//	{
//		m_tSpriteRenderers.erase(it);
//	}
//
//}


