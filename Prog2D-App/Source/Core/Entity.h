#pragma once
#include "Core/Component.h"
#include <vector>
#include <assert.h>
#include <algorithm>
#include "Prog2D-Raylib/raylib.h"
#include "Prog2D-Raylib/raymath.h"
#include "Core/pugixml.hpp"

class CLevel;

class CEntity
{
public:
	CEntity();
	~CEntity();

	//void Initialize();
	void Configure();
	void BeginPlay();
	

	void PrePhyshics(float _fTimeStep) ;
	void PostPhyshics(float _fTimeStep) ;

	void EndPlay();
	void Delete();


	template <class T> 
	T* AddComponent()
	{
		if (T* pComp = GetComponent<T>())
		{
			return pComp; 
		}

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

	template <typename T>
	T* AddComponent(const pugi::xml_node& oNode)
	{
		if (T* pComp = GetComponent<T>())
		{
			return pComp;
		}

		T* pNewComp = new T(oNode);
		CComponent* pComp = dynamic_cast<CComponent*>(pNewComp);

		if (pComp)
		{
			m_tComponents.emplace_back(pComp);
			pComp->SetEntity(this);
			pComp->Initialize();

			std::sort(m_tComponents.begin(), m_tComponents.end(),
				[](const CComponent* _pLeft, const CComponent* _pRight)
				{
					return _pLeft->GetPriority() > _pRight->GetPriority();
				});
		}
		else
		{
			delete pNewComp;
			pNewComp = nullptr;
			assert(false);
		}

		return pNewComp;
	}
	template <class T>
	T* GetComponent()
	{
		T* pReturn = nullptr;

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

	const Vector2& GetPos() const { return m_vPos; };
	void SetPos(const Vector2& _vPos) { m_vPos = _vPos; };

	float GetRot() const { return m_fRot; }
	void SetRot(float _fRot) { m_fRot = _fRot; }

	const std::string& GetName() const { return m_sName; }
	void SetName(const std::string& _sName) { m_sName = _sName; }

		 
private:

	std::vector<CComponent*> m_tComponents;
	Vector2 m_vPos = Vector2Zero();
	float m_fRot = 0.f;
	std::string m_sName;

	CLevel* m_pEntityLevel = nullptr;

};

