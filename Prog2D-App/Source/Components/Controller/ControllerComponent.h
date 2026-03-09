#pragma once

#include "Core/Component.h"

class CAnimationComponent;

class CControllerComponent : public CComponent
{
	DERIVED_CLASS(CControllerComponent, CComponent)

private:
	CAnimationComponent* m_pAnimComponent{ nullptr };

public:
	CControllerComponent();
	CControllerComponent(const pugi::xml_node& oRoot);

	virtual ~CControllerComponent() {};

	virtual void Initialize() override;
	virtual void Delete() override;
	virtual void Configure() override;
	virtual void Awake() override;
	virtual void BeginPlay() override;
	virtual void EndPlay() override;
	virtual void PrePhyshics(float _fDeltaTime) override;
	virtual void PostPhyshics(float _fDeltaTime) override;
};

