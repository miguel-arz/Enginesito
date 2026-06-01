#include "AnimationComponent.h"
#include "Core/Entity.h"
#include "Components/Render/SpriteRendererComponent.h"

CAnimationComponent::CAnimationComponent()
	: Super(2u)
{
}

CAnimationComponent::CAnimationComponent(const pugi::xml_node& oRoot)
	: Super(2u)
{
	const char* sActionList{ nullptr };
	GET_VARIABLE_VALUE(string, sActionList, sActionList, nullptr);

	if (sActionList)
	{
		START_DESERIALIZATION(sActionList, oActionListDoc, CActionList, .actl)

			for (pugi::xml_node oActionListNode = oRoot.first_child();
				oActionListNode;
				oActionListNode = oActionListNode.next_sibling())
		{
			const char* sActionPath{ nullptr };

			if (pugi::xml_attribute oValue = oActionListNode.attribute("value"))
			{
				sActionPath = oValue.as_string();
			}

			if (sActionPath && strlen(sActionPath) > 0)
			{
				START_DESERIALIZATION(sActionPath, oActionDoc, CAction, .act)

					m_tActions.emplace_back(oRoot);

				END_DESERIALIZATION("ACTION ERROR")
			}
		}

		END_DESERIALIZATION("ACTION LIST ERROR")
	}

	const char* sDefaultAction{ nullptr };
	GET_VARIABLE_VALUE(string, sDefaultAction, sDefaultAction, nullptr);

	if (sDefaultAction)
	{
		m_sDefaultActionName = sDefaultAction;
		m_pDefaultAction = GetAction(m_sDefaultActionName);
	}
}

void CAnimationComponent::Initialize()
{
	Super::Initialize();
}

void CAnimationComponent::Configure()
{
	Super::Configure();
}

void CAnimationComponent::Awake()
{
	Super::Awake();
	m_pCurrentAction = nullptr;
}

void CAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	if (m_pDefaultAction)
	{
		StartAction(m_pDefaultAction, true, 0.f);
	}
}

void CAnimationComponent::PrePhyshics(float _fTimeStep)
{
	Super::PrePhyshics(_fTimeStep);
}

void CAnimationComponent::PostPhyshics(float _fTimeStep)
{
	Super::PostPhyshics(_fTimeStep);

	if (m_pCurrentAction == nullptr)
	{
		return;
	}

	CAction::SUpdateResult oResult = m_pCurrentAction->Update(_fTimeStep);

	if (oResult.bIsFinished)
	{
		EndAction(oResult.fExtraTime, false);
	}

	if (m_pCurrentAction == nullptr)
	{
		return;
	}

	CSpriteRendererComponent* pSpriteComp = m_pEntity
		? m_pEntity->GetComponent<CSpriteRendererComponent>()
		: nullptr;

	if (pSpriteComp == nullptr)
	{
		return;
	}

	Texture* pActionTexture = m_pCurrentAction->GetTexture();

	if (pActionTexture == nullptr || pActionTexture->id == 0)
	{
		return;
	}

	if (pSpriteComp->GetTexture() != pActionTexture)
	{
		pSpriteComp->SetTexture(pActionTexture);
	}

	if (m_pCurrentAction->GetNumFrames() == 0)
	{
		return;
	}

	const CAction::SFrame& rInfo = m_pCurrentAction->GetCurrentFrameInfo();
	pSpriteComp->SetUVs(rInfo.vUVs);
}

void CAnimationComponent::EndPlay()
{
	Super::EndPlay();
}

void CAnimationComponent::Delete()
{
	Super::Delete();

	m_pCurrentAction = nullptr;
	m_pDefaultAction = nullptr;
	m_tActions.clear();
}

CAction* CAnimationComponent::GetAction(const std::string& _sActionName)
{
	for (CAction& oAction : m_tActions)
	{
		if (oAction.GetActionName() == _sActionName)
		{
			return &oAction;
		}
	}

	return nullptr;
}

bool CAnimationComponent::CanSetAction(CAction* _pAction)
{
	if (_pAction == nullptr)
	{
		return false;
	}

	if (m_pCurrentAction == nullptr)
	{
		return true;
	}

	return _pAction->GetPriority() >= m_pCurrentAction->GetPriority();
}

void CAnimationComponent::StartAction(const std::string& _sActionName, bool _bForce, float _fStartTime)
{
	CAction* pNewAction = GetAction(_sActionName);
	StartAction(pNewAction, _bForce, _fStartTime);
}

void CAnimationComponent::StartAction(CAction* _pNewAction, bool _bForce, float _fStartTime)
{
	if (_pNewAction == nullptr)
	{
		return;
	}

	if (m_pCurrentAction == _pNewAction)
	{
		return;
	}

	bool bCanInsert = _bForce || CanSetAction(_pNewAction);

	if (!bCanInsert)
	{
		return;
	}

	m_pCurrentAction = _pNewAction;
	m_pCurrentAction->Start(_fStartTime);
}

void CAnimationComponent::EndAction(float _fExtraTime, bool _bForceDefault)
{
	if (m_pCurrentAction == nullptr)
	{
		return;
	}

	switch (m_pCurrentAction->GetOnActionFinished())
	{
	case EOnActionFinished::ToDefault:
	{
		StartAction(m_pDefaultAction, true, _fExtraTime);
		break;
	}

	case EOnActionFinished::ToAction:
	{
		StartAction(m_pCurrentAction->GetNextAction(), true, _fExtraTime);
		break;
	}

	case EOnActionFinished::Freeze:
	{
		if (_bForceDefault)
		{
			StartAction(m_pDefaultAction, true, _fExtraTime);
		}
		break;
	}

	case EOnActionFinished::Loop:
	default:
	{
		if (_bForceDefault)
		{
			StartAction(m_pDefaultAction, true, _fExtraTime);
		}
		break;
	}
	}
}