#pragma once

#include "Core/GlobalDefines.h"
#include "Core/Entity.h"
#include "Components/Animation/Action/Action.h"

class CAnimationComponent : public CComponent
{
	DERIVED_CLASS(CAnimationComponent, CComponent);

public:

	CAnimationComponent();
	CAnimationComponent(const pugi::xml_node& oRoot);

	virtual ~CAnimationComponent() {};

	virtual void Initialize() override;
	virtual void Configure(/*pugi::xml_node& _rNode*/)override;
	virtual void Awake()override;
	virtual void BeginPlay()override;
	

	virtual void PrePhyshics(float _fTimeStep) override;
	virtual void PostPhyshics(float _fTimeStep) override;

	virtual void EndPlay()override;
	virtual void Delete()override;

	//void ConfigureActionList(pugi::xml_node& _rNode);

	CAction* GetAction(const std::string& _sActionName);

	bool CanSetAction(CAction* _pAction);

	void StartAction(const std::string& _sActionName, bool _bForce = false, float _fStartTime = 0.f);
	void StartAction(CAction* _pNewAction, bool _bForce = false, float _fStartTime = 0.f);
	void EndAction(float _fExtraTime =0.f, bool _bForceDefault = true);

	const CAction* GetCurrentAction() const { return m_pCurrentAction; }

	typedef std::vector<CAction> TActions;

private:

	TActions m_tActions{};
	CAction* m_pCurrentAction{nullptr};
	CAction* m_pDefaultAction{nullptr};
	std::string m_sDefaultActionName;

};