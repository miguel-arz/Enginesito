#include "Entity.h"
#include "Level.h"
#include "Components/Render/SpriteRendererComponent.h"
#include "Components/Animation/AnimationComponent.h"

CEntity::CEntity()
	/*m_vPos(Vector2Zero()),
	m_fRot(0.f)*/
{
	
	m_tComponents.reserve(20);
}

CEntity::~CEntity()
{
	Delete();
}

void CEntity::Configure()
{

	for (CComponent* pComp : m_tComponents)
	{
		pComp->Configure();
	}

	/*pugi::xml_node oRootNode = _oDoc.first_child();
	GET_VARIABLE(string, m_sName, sName, Value, "DefaultValue");

	if (pugi::xml_node oNode = oRootNode.find_child([](const pugi::xml_node& _oNode) { return strcmp(_oNode.name(), "CSpriteRendererComponent") == 0;}))
	{
		CSpriteRendererComponent* pComp = AddComponent<CSpriteRendererComponent>();

		if (pComp)
		{
			pComp->Configure(oNode);
		}
	}

	if (pugi::xml_node oNode = oRootNode.find_child([](const pugi::xml_node& _oNode) { return strcmp(_oNode.name(), "CAnimationComponent") == 0;}))
	{
		CAnimationComponent* pComp = AddComponent<CAnimationComponent>();

		if (pComp)
		{
			pComp->Configure(oNode);
		}
	}*/
}
void CEntity::BeginPlay()
{
	for (CComponent* pComp : m_tComponents)
	{
		if (pComp)
		{
			pComp->Awake();
		}
	}
	for (CComponent* pComp : m_tComponents)
	{
		if (pComp)
		{
			pComp->BeginPlay();
		}
	}
}
void CEntity::PrePhyshics(float _fTimeStep)
{
	for (CComponent* pComp : m_tComponents)
	{
		if (pComp)
		{
			pComp->PrePhyshics(_fTimeStep);
		}
	}
}
void CEntity::PostPhyshics(float _fTimeStep)
{
	for (CComponent* pComp : m_tComponents)
	{
		if (pComp)
		{
			pComp->PostPhyshics(_fTimeStep);
		}
	}
}

void CEntity::EndPlay()
{
	for (CComponent* pComp : m_tComponents)
	{
		if (pComp)
		{
			pComp->EndPlay();
		}
	}
}
void CEntity::Delete()
{
	for (CComponent* pComp : m_tComponents)
	{
		if (pComp)
		{
			pComp->Delete();
			delete(pComp);
		}
	}
	m_tComponents.clear();
	m_pEntityLevel = nullptr;
}