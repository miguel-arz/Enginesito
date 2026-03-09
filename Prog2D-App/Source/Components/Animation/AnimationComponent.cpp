#include "AnimationComponent.h"
#include "Core/Entity.h"
#include "Components/Render/SpriteRendererComponent.h"
#include <vector>

CAnimationComponent::CAnimationComponent()
	: Super(2u)
{
}

CAnimationComponent::CAnimationComponent(const pugi::xml_node& oRoot)
{
	const char* sActionList{ nullptr };
	GET_VARIABLE_VALUE(string, sActionList, sActionList, nullptr);
	if (sActionList)
	{
		START_DESERIALIZATION(sActionList, oActionListDoc, CActionList, .actl)

			for (pugi::xml_node oNode = oRoot.first_child(); oNode; oNode = oNode.next_sibling())
			{
				const char* sActionPath{ nullptr };
				GET_ATTRIBUTE(string, sActionPath, value, nullptr);
				if (sActionPath)
				{
					START_DESERIALIZATION(sActionPath, oActionDoc, CAction, .act)

						m_tActions.emplace_back(oRoot);

					END_DESERIALIZATION("ACTION LIST ERROR")
				}
			};

		END_DESERIALIZATION("ACTION LIST ERROR")
	}

	const char* sDefaultAction{ nullptr };
	GET_VARIABLE_VALUE(string, sDefaultAction, sDefaultAction, nullptr);
	if (sDefaultAction)
	{
		for (CAction& oAction : m_tActions)
		{
			if (oAction.GetActionName().compare(sDefaultAction) == 0)
			{
				m_pDefaultAction = &oAction;
				break;
			}
		}
	}
}

void CAnimationComponent::Initialize()
{
	Super::Initialize();
	/*m_tActions.clear();
	m_tActions.reserve(13u);

	m_pDefaultAction = nullptr;*/

}

void CAnimationComponent::Configure()
{
	Super::Configure();
	/*pugi::xml_node& oRootNode = _rNode;

	GET_VARIABLE_VALUE(string, m_sDefaultActionName, sDefaultAction, "");

	std::string sActionList;
	GET_VARIABLE_VALUE(string, sActionList, sActionList, "");

	pugi::xml_document oDoc;
	pugi::xml_parse_result oResult = oDoc.load_file("resources/orkito/orkito.actl");
	if (oResult)
	{
		pugi::xml_node oListNode = oDoc.first_child();
		ConfigureActionList(oListNode);
	}
	m_pDefaultAction =  GetAction(m_sDefaultActionName);*/
}

//void CAnimationComponent::ConfigureActionList(pugi::xml_node& _rNode)
//{
//	pugi::xml_node& oRootNode = _rNode;
//	CREATE_COLLECTION(CAction, m_tActions, CAction);
//}

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

	if (m_pCurrentAction)
	{
		CAction::SUpdateResult oResult = m_pCurrentAction->Update(_fTimeStep);
		if (oResult.bIsFinished)
		{
			EndAction(oResult.fExtraTime, false);
		}
	}
	if (CSpriteRendererComponent* pSpriteComp = m_pEntity->GetComponent<CSpriteRendererComponent>())
	{
		if (pSpriteComp->GetTexture() != m_pCurrentAction->GetTexture())
		{
			pSpriteComp->SetTexture(m_pCurrentAction->GetTexture());
		}
		const CAction::SFrame& rInfo = m_pCurrentAction->GetCurrentFrameInfo();
		pSpriteComp->SetUVs(rInfo.vUVs);

	}
}

void CAnimationComponent::EndPlay()
{
	Super::EndPlay();
}


void CAnimationComponent::Delete()
{
	Super::Delete();

	m_tActions.clear();
	
}

CAction* CAnimationComponent::GetAction(const std::string& _sActionName) 
{
	CAction* pAction = nullptr;
	unsigned int uSize = static_cast<unsigned int>(m_tActions.size());
	for (unsigned int i = 0u;i < uSize; ++i)
	{
		if (m_tActions[i].GetActionName() == _sActionName)
		{
			pAction = &m_tActions[i];
		}
	}
	return pAction;
}

bool CAnimationComponent::CanSetAction(CAction* _pAction)
{
	bool bCanInsert(false);
	if (_pAction)
	{
		bCanInsert = !m_pCurrentAction || _pAction->GetPriority() >= m_pCurrentAction->GetPriority();
	}

	return bCanInsert;
}


void CAnimationComponent::StartAction(const std::string& _sActionName, bool _bForce, float _fStartTime)
{
	CAction* pNewAction = GetAction(_sActionName);
	StartAction(pNewAction, _bForce);
}

void CAnimationComponent::StartAction(CAction* _pNewAction, bool _bForce, float _fStartTime  /*=0.f*/)
{
	bool bCanInsert = _bForce || CanSetAction(_pNewAction);

	if (_pNewAction && bCanInsert)
	{
		m_pCurrentAction = _pNewAction;
		m_pCurrentAction->Start(_fStartTime);
	}
}

void CAnimationComponent::EndAction(float _fExtraTime, bool _bForceDefault)
{
	switch (m_pCurrentAction->GetOnActionFinished())
	{
	case EOnActionFinished::ToDefault:
	{
		StartAction(m_pDefaultAction, true, _fExtraTime);
	}
	break;
	case EOnActionFinished::ToAction:
	{
		StartAction(m_pCurrentAction->GetNextAction(), true, _fExtraTime);
	}
	break;
	case EOnActionFinished::Freeze:
	{
		if (_bForceDefault)
		{
			StartAction(m_pDefaultAction, true, _fExtraTime);
		}
	}
	break;
	case EOnActionFinished::Loop:
	default:
	{
		if (_bForceDefault)
		{
			StartAction(m_pDefaultAction, true, _fExtraTime);
		}
	}
	break;
	}
}



