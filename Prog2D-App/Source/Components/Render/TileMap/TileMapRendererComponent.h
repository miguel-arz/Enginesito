#pragma once

#include "Core/Component.h"
#include "Render/RenderItem.h"
#include "../../Prog2D-Raylib/Source/Prog2D-Raylib/raylib.h"
#include "../../Prog2D-Raylib/Source/Prog2D-Raylib/raymath.h"
#include <vector>

struct STile
{
	Vector4 vUVs;
	Vector2 vOffset;
};

struct STileset
{
	int iIndex{ 0 };
	Texture2D* pTexture{ nullptr };
	Vector2 vTilePixelSize{ 16.f, 16.f };
	Vector2 vTileUVSize{ 1.f, 1.f };
	int iColumns{ 1 };
	int iRows{ 1 };
};

struct STileMapLayer : IRenderItem
{
	std::string sName{ "" };
	std::vector<STile> tTiles{};
	class CTileMapRendererComponent* pOwnerTilemap{};

	Color vColor{ WHITE };
	BlendMode eBlendMode{ BLEND_ALPHA };
	const STileset* pTileset{ nullptr };
	unsigned int uLayer{ 0 };
	bool bIsVisible{ true };

	void Draw() override;
	unsigned int GetLayer() const override { return uLayer; }
};

class CTileMapRendererComponent : public CComponent
{
	DERIVED_CLASS(CTileMapRendererComponent, CComponent)

private:
	std::vector<STileMapLayer> m_tMapLayers;
	std::vector<STileset> m_tTilesets;
	unsigned int m_uLayer{ 0 };

public:
	CTileMapRendererComponent();
	CTileMapRendererComponent(const pugi::xml_node& oRoot);

	virtual ~CTileMapRendererComponent() {};

	void Awake() override;
	void Delete() override;
	void LoadTilemap(const char* _sPath);

private:
	void LoadTilesets(std::string _sTilemapFolderPath, const pugi::xml_node& _oMapNode);
	void LoadLayer(pugi::xml_node& _oLayerNode, unsigned int uLayerIndex);
};

