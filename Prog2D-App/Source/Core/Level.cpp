#include "Level.h"
#include "Core/Entity.h"
#include "Components/IncludeComponents.h"

CLevel::CLevel()
{
}

CLevel::~CLevel()
{
	Delete();
};

void CLevel::LoadLevel(const char* _sPath)
{
	{
		if (strstr(_sPath, ".ld")) {
			pugi::xml_document oLevel; pugi::xml_parse_result oResult = oLevel.load_file(_sPath); if (oResult) {
				pugi::xml_node oRoot = oLevel.first_child(); if (oRoot && strcmp(oRoot.name(), "CLevel") == 0) {

		m_tEntities.reserve(20u);
	FOR_EACH_CHILD_NODE(oNode, oRoot, CEntity)
		pugi::xml_node& oRoot{ oNode };

	CEntity* pNewEntity = new CEntity();

	Vector2 vEntityPosition;
	GET_VARIABLE_AS_VECTOR2(vEntityPosition, vPosition, fX, fY, 0.f, 0.f);
	float fEntityRotation;
	GET_VARIABLE_VALUE(float, fEntityRotation, fRotation, 0.f);
	pNewEntity->SetPos(vEntityPosition);
	pNewEntity->SetRot(fEntityRotation);

	const char* sEntityDataPath;
	GET_VARIABLE_VALUE(string, sEntityDataPath, sFilePath, "");
	if (strlen(sEntityDataPath) > 1)
	{
		START_DESERIALIZATION(sEntityDataPath, oEntity, CEntity, .ed)

			std::string sEntityName;
		GET_VARIABLE_VALUE(string, sEntityName, sName, "");
		pNewEntity->SetName(sEntityName);

		if (pugi::xml_node oCollectionNode = oRoot.find_child([](const pugi::xml_node& _oNode) { return strcmp(_oNode.name(), "tComponents") == 0;})) {
			for (pugi::xml_node oChild = oCollectionNode.first_child(); oChild; oChild = oChild.next_sibling()) {
				const char* sComponentType{ "" }; pugi::xml_node oNode{ oChild }; if (pugi::xml_attribute oValue = oNode.attribute("sType")) {
					sComponentType = oValue.as_string();
				}
				else {
					sComponentType = "";
				}; if (strcmp(sComponentType, "SpriteRendererComponent") == 0) {
					(*pNewEntity).AddComponent<CSpriteRendererComponent>(oChild);
				}
				else if (strcmp(sComponentType, "AnimationComponent") == 0) {
					(*pNewEntity).AddComponent<CAnimationComponent>(oChild);
				}
				else if (strcmp(sComponentType, "TileMapRendererComponent") == 0) {
					(*pNewEntity).AddComponent<CTileMapRendererComponent>(oChild);
				}
				else if (strcmp(sComponentType, "ControllerComponent") == 0) {
					(*pNewEntity).AddComponent<CControllerComponent>(oChild);
				}
			}
		};

		END_DESERIALIZATION("ENTITY LOAD ERROR.")
	}

	m_tEntities.push_back(pNewEntity);
	END_FOR_EACH_CHILD_NODE

	END_DESERIALIZATION("LEVEL LOAD ERROR")
}

void CLevel::Configure()
{
	for (CEntity* pEntity : m_tEntities)
	{
		pEntity->Configure();
	}
}

void CLevel::Delete()
{
	// Prevents RemoveEntity from breaking entities iteration
	m_bCanRemoveEntities = false;

	for (CEntity* pEntity : m_tEntities)
	{
		pEntity->Delete();

		delete pEntity;
		pEntity = nullptr;
	}

	m_bCanRemoveEntities = true;
	m_tEntities.clear();
}

void CLevel::BeginPlay()
{
	for (CEntity* pEntity : m_tEntities)
	{
		pEntity->BeginPlay();
	}
}

void CLevel::EndPlay()
{
	for (CEntity* pEntity : m_tEntities)
	{
		pEntity->EndPlay();
	}
}

void CLevel::PrePhysics(float _fDeltaTime)
{
	for (CEntity* pEntity : m_tEntities)
	{
		pEntity->PrePhyshics(_fDeltaTime);
	}
}

void CLevel::PostPhysics(float _fDeltaTime)
{
	for (CEntity* pEntity : m_tEntities)
	{
		pEntity->PostPhyshics(_fDeltaTime);
	}
}

void CLevel::RemoveEntity(CEntity* _pEntity)
{
	if (!m_bCanRemoveEntities)
	{
		return;
	}

	for (TLevelEntities::iterator it{ m_tEntities.begin() }; it != m_tEntities.end(); ++it)
	{
		if (*it == _pEntity)
		{
			m_tEntities.erase(it);
			break;
		}
	}
}