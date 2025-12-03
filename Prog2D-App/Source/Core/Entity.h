#pragma once
#include "Core/Component.h"
#include <vector>
#include <assert.h>
#include <algorithm>

class CEntity
{
public:
	CEntity();
	~CEntity();

	virtual void Initialize();
	virtual void BeginPlay();

	virtual void PrePhyshics(float _fTimeStep) ;
	virtual void PostPhyshics(float _fTimeStep) ;

	virtual void EndPlay();
	virtual void Delete();


	template <class T> 
	T* AddComponent()
	{
		T* pNewComp = new T();
		CComponent* pComp = dynamic_cast<CComponent*>(pNewComp);

		if (pComp)
		{
			m_tComponents.emplace_back(pComp);
			pComp->SetEntity(this);
			pComp->Initialize();

			sort(m_tComponents.begin(), m_tComponents.end(), [](const CComponent* _pLeft, const CComponent* _pRight) {return _pLeft->GetPriority() > _pRight->GetPriority(); });
		}
		else
		{
			assert(false);
			delete pNewComp;
			pNewComp = nullptr;
		}
		return pNewComp;
	}

	template <class T>
	T* GetComponent()
	{
		T* pReturn;

		//implementar dynamisc cast

		size_t iSize = m_tComponents.size();
		for(size_t i = 0; i < iSize; i++)
		{
			pReturn = dynamic_cast<T*>(m_tComponents[i]);
			if (pReturn)
			{
				break;
			}
		}
		return pReturn;
	}


private:
	std::vector<CComponent*> m_tComponents;
};

