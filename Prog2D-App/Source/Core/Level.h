#pragma once

#include "Entity.h"

class CLevel
{
public:
	typedef std::vector<CEntity*> TLevelEntities;

private:
	TLevelEntities m_tEntities;
	bool m_bCanRemoveEntities{ true };

public:
	CLevel();

	~CLevel();

	void LoadLevel(const char* _sPath);
	void Configure();
	void Delete();
	void BeginPlay();
	void EndPlay();
	void PrePhysics(float _fDeltaTime);
	void PostPhysics(float _fDeltaTime);

	void RemoveEntity(CEntity* _pEntity);
};

