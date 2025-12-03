#pragma once
#include "Core/GlobalDefines.h"
class CEntity;
class CComponent
{
public:
	CComponent()
		: m_pEntity(nullptr),
		m_uPriority(0u)
	{
	};
	CComponent(CEntity* _pEntity)
		: m_pEntity(_pEntity),
		m_uPriority(0u)
	{
	};
	CComponent(unsigned int _uPriority)
		: m_pEntity(nullptr),
		m_uPriority(0u)
	{
	};
	CComponent(CEntity* _pEntity, unsigned int _uPriority)
		: m_pEntity(_pEntity),
		m_uPriority(_uPriority)
	{
	};



	virtual ~CComponent()
	{
		m_pEntity = nullptr;
	};

	CEntity* GetEntity() const { return m_pEntity; }
	void SetEntity(CEntity* _pEntity) { m_pEntity = _pEntity; }

	unsigned int GetPriority() const {return m_uPriority;}
	void SetPriority(unsigned int _uPriority) { m_uPriority = _uPriority; }

	virtual void Initialize() {};
	virtual void BeginPlay() {};

	virtual void PrePhyshics(float _fTimeStep) {UNUSED_VARIABLE (_fTimeStep)};
	virtual void PostPhyshics(float _fTimeStep) { UNUSED_VARIABLE(_fTimeStep) };

	virtual void EndPlay() {};
	virtual void Delete() {};

protected:
	CEntity* m_pEntity = nullptr;
private:
	unsigned int m_uPriority = 0;
};