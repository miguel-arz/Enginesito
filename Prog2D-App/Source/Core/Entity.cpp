#include "Entity.h"

CEntity::CEntity()
{
	m_tComponents.reserve(20);
}

CEntity::~CEntity()
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
}

void CEntity::Initialize()
{
	for (CComponent* pComp : m_tComponents)
	{
		if (pComp)
		{
			pComp->Initialize();
		}
	}
}
void CEntity::BeginPlay()
{
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
}