#pragma once

#include <vector>
#include <assert.h>
#include <algorithm>
#include "Core/Singleton.h"
#include "Prog2D-Raylib/raylib.h"
#include "Prog2D-Raylib/raymath.h"
#include <string>
#include <list>


//class CSpriteRendererComponent;

class IRenderItem;

class CRenderEngine : public ISingleton<CRenderEngine>
{
public:

	struct STextureData
	{
		/*STextureData();*/
		STextureData(Image& _rImage);
		~STextureData();

		std::string sFilePath;
		Texture2D oTexture{};
		unsigned int uNumReferences	= 0u;
	};


	typedef std::list<STextureData> TTextureDatas;
	typedef std::vector<IRenderItem*> TRenderItems;

	void InitializeRenderer(int _iScreenWidht, int _iScreenHeight, const char* _sName);
	void DeleteRenderer();
	void Draw();

	void AddRenderer(IRenderItem* _pRenderItem);
	void RemoveRenderer(IRenderItem* _pRenderItem);

	Texture2D* LoadTexture2D(const std::string& _sFilePath);
	Texture2D* LoadTexture2D(Image& _rImage);
	Texture2D* LoadTexture2D(Texture2D* _pTexture);

	void UnloadTexture2D(Texture* _pTexture);
	void UnloadTexture2D(unsigned int _uTextureId);


	/*void AddSpriteRenderer(CSpriteRendererComponent* _pSpriteComp);

	void RemoveSpriteRenderer(CSpriteRendererComponent* _pSpriteComp);*/

	void SetLayerDirty()
	{
		m_bIsLayerDirty = true;
	}

	const Vector2& GetWindowSize() const { return m_vWindowSize; }

	const BlendMode& GetCurrentBlendMode() const { return m_eCurrentBlendMode; }
	void SetCurrentBlendMode(BlendMode eNewBlendMode)
	{
		if (eNewBlendMode != m_eCurrentBlendMode)
		{
			BeginBlendMode(eNewBlendMode);
			m_eCurrentBlendMode = eNewBlendMode;
		}
	}


private:

	Vector2 m_vWindowSize;
	const char* m_sTitle;

	TTextureDatas m_tTextureDatas;
	TRenderItems m_tRenderers;

	bool m_bIsLayerDirty = false;
	BlendMode m_eCurrentBlendMode{ BLEND_ALPHA };

	void UnloadAllTextures2D();
};

