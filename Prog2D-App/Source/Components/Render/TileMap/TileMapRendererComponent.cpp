#include "tileMapRendererComponent.h"

#include "Core/Entity.h"
#include "Render/RenderEngine.h"
#include <algorithm>

CTileMapRendererComponent::CTileMapRendererComponent() :
	Super(3u)
{

}

CTileMapRendererComponent::CTileMapRendererComponent(const pugi::xml_node& oRoot) :
	Super(3u)
{
	int uLayer;
	GET_VARIABLE_VALUE(int, uLayer, uLayer, 0);
	m_uLayer = static_cast<unsigned int>(uLayer);

	const char* sMapPath;
	GET_VARIABLE_VALUE(string, sMapPath, sMapPath, "");

	if (strlen(sMapPath) > 1)
	{
		LoadTilemap(sMapPath);
	}
}

void CTileMapRendererComponent::Awake()
{
	Super::Awake();

	CRenderEngine* pRenderEngine{ CRenderEngine::GetInstance() };
	for (STileMapLayer& rLayer : m_tMapLayers)
	{
		pRenderEngine->AddRenderer(&rLayer);
	}
}

void CTileMapRendererComponent::Delete()
{
	Super::Delete();

	CRenderEngine* pRenderEngine{ CRenderEngine::GetInstance() };
	for (STileMapLayer& rLayer : m_tMapLayers)
	{
		pRenderEngine->RemoveRenderer(&rLayer);
	}

	for (STileset& rTileset : m_tTilesets)
	{
		CRenderEngine::GetInstance()->UnloadTexture2D(rTileset.pTexture);
		rTileset.pTexture = nullptr;
	}

	m_tTilesets.clear();
	m_tMapLayers.clear();
}

void CTileMapRendererComponent::LoadTilemap(const char* _sPath)
{
	START_DESERIALIZATION(_sPath, oMap, map, .lvl)

		std::string sMapFolder(_sPath);
	int iEraseIndex = static_cast<int>(sMapFolder.find_last_of("/"));
	if (iEraseIndex != std::string::npos)
	{
		sMapFolder = sMapFolder.erase(iEraseIndex + 1);
	}

	LoadTilesets(sMapFolder, oRoot);

	m_tMapLayers.clear();
	m_tMapLayers.reserve(5u);
	unsigned int uIndex{ 0 };
	FOR_EACH_CHILD_NODE(oNode, oRoot, layer)

		if (true) {
			LoadLayer(oNode, m_uLayer + uIndex);
			++uIndex;
		}

	END_FOR_EACH_CHILD_NODE

		END_DESERIALIZATION("MAP ERROR");
}

void STileMapLayer::Draw()
{
	if (!bIsVisible)
	{
		return;
	}

	const STileset* pLayerTileset{ pTileset };
	Vector2 vMapPos{ pOwnerTilemap->GetEntity()->GetPos() };
	float vMapRot{ pOwnerTilemap->GetEntity()->GetRot() };
	const Vector2 vPivot{ 0.f, 0.f };

	CRenderEngine::GetInstance()->SetCurrentBlendMode(eBlendMode);
	for (const STile& rTile : tTiles)
	{
		Rectangle vDest{ vMapPos.x + rTile.vOffset.x, vMapPos.y + rTile.vOffset.y,  pLayerTileset->vTilePixelSize.x, pLayerTileset->vTilePixelSize.y };

		DrawTextureProUV(*pLayerTileset->pTexture, rTile.vUVs, vDest, vPivot, vMapRot, vColor);
	}
}


void CTileMapRendererComponent::LoadTilesets(std::string _sTilemapFolderPath, const pugi::xml_node& _oMapNode)
{
	m_tTilesets.clear();
	m_tTilesets.reserve(2u);

	FOR_EACH_CHILD_NODE(oNode, _oMapNode, tileset)
		STileset newTileset;
	std::string sTexturePath{ "" };

	GET_ATTRIBUTE(int, newTileset.iIndex, firstgid, 0)
		pugi::xml_node oRoot(oNode);
	GET_VARIABLE(string, sTexturePath, image, source, "")

		if (newTileset.iIndex > 0 && !sTexturePath.empty())
		{
			newTileset.pTexture = CRenderEngine::GetInstance()->LoadTexture2D((_sTilemapFolderPath + sTexturePath).c_str());
			GET_ATTRIBUTE(int, newTileset.iColumns, columns, 1);
			GET_ATTRIBUTE(int, newTileset.iRows, tilecount, 1);
			newTileset.iRows /= newTileset.iColumns;
			GET_ATTRIBUTES_AS_VECTOR2(newTileset.vTilePixelSize, tilewidth, tileheight, 16.f, 16.f);
			newTileset.vTileUVSize = Vector2(1.f / static_cast<float>(newTileset.iColumns), 1.f / static_cast<float>(newTileset.iRows));

			m_tTilesets.emplace_back(newTileset);
		}

	END_FOR_EACH_CHILD_NODE;

	std::sort(m_tTilesets.begin(), m_tTilesets.end(),
		[](const STileset& _pLeft, STileset& _pRight)
		{
			return _pLeft.iIndex < _pRight.iIndex;
		});
}

void CTileMapRendererComponent::LoadLayer(pugi::xml_node& oNode, unsigned int uLayerIndex)
{
	STileMapLayer oNewLayer;
	oNewLayer.pOwnerTilemap = this;
	GET_ATTRIBUTE(string, oNewLayer.sName, name, "");

	oNewLayer.uLayer = uLayerIndex;
	GET_LAYER_PROPERTY(int, oNewLayer.uLayer, oNode, layer, uLayerIndex);

	int iLayerWidth, iLayerHeight;
	GET_ATTRIBUTE(int, iLayerWidth, width, 10);
	GET_ATTRIBUTE(int, iLayerHeight, height, 10);
	oNewLayer.tTiles.reserve(iLayerWidth * iLayerHeight);

	GET_NODE(oDataNode, oNode, data);
	const char* sData = oDataNode.child_value();

	const STileset* pTileset{ nullptr };

	unsigned int uX{ 0 };
	unsigned int uY{ 0 };

	const char* pIt{ sData };
	const char* pEnd{ sData + strlen(sData) };

	while (pIt < pEnd) {
		char* next;
		int iTileId = std::strtol(pIt, &next, 10);

		if (iTileId != 0)
		{
			if (!pTileset)
			{
				if (m_tTilesets.empty())
				{
					TraceLog(LOG_ERROR, "NO TILESET");
					return;
				}

				unsigned int uTilesetIndex{ 0 };
				while (uTilesetIndex < m_tTilesets.size() && m_tTilesets[uTilesetIndex].iIndex <= iTileId)
				{
					++uTilesetIndex;
				}

				if (uTilesetIndex >= m_tTilesets.size())
				{
					pTileset = &m_tTilesets.back();
				}
				else
				{
					pTileset = &m_tTilesets[uTilesetIndex - 1];
				}
				oNewLayer.pTileset = pTileset;
			}

			while (static_cast<int>(uX) >= iLayerWidth)
			{
				uX -= iLayerWidth;
				++uY;
			}

			iTileId -= pTileset->iIndex;
			STile oNewTile;
			oNewTile.vOffset = Vector2(static_cast<float>(uX) * pTileset->vTilePixelSize.x, static_cast<float>(uY) * pTileset->vTilePixelSize.y);
			Vector2 vTileUV1 = Vector2(static_cast<float>(iTileId % pTileset->iColumns) * pTileset->vTileUVSize.x, static_cast<float>(iTileId / pTileset->iColumns) * pTileset->vTileUVSize.y);
			oNewTile.vUVs = Vector4(vTileUV1.x, vTileUV1.y, vTileUV1.x + pTileset->vTileUVSize.x, vTileUV1.y + pTileset->vTileUVSize.y);

			oNewLayer.tTiles.emplace_back(oNewTile);
		}

		++uX;
		pIt = next + 1;
	}

	if (!oNewLayer.tTiles.empty())
	{
		m_tMapLayers.emplace_back(oNewLayer);
	}
}
