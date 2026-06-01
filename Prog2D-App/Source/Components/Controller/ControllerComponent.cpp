#include "ControllerComponent.h"
#include "Core/Entity.h"
#include "Components/Animation/AnimationComponent.h"

const float SPEED = 100.f;

CControllerComponent::CControllerComponent() :
	Super(5u)
{
}

CControllerComponent::CControllerComponent(const pugi::xml_node& oRoot) :
	Super(5u)
{
}

void CControllerComponent::Initialize()
{
	Super::Initialize();
}

void CControllerComponent::Delete()
{
	Super::Delete();
}

void CControllerComponent::Configure()
{
	Super::Configure();
}

void CControllerComponent::Awake()
{
	Super::Awake();

	m_pAnimComponent = GetEntity()->GetComponent<CAnimationComponent>();
}

void CControllerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void CControllerComponent::EndPlay()
{
	Super::EndPlay();
}

void CControllerComponent::PrePhyshics(float _fDeltaTime)
{
	Super::PrePhyshics(_fDeltaTime);

	Vector2 vMove = { 0.f, 0.f };


	if (IsKeyDown(KEY_A)) vMove.x -= 1.f;
	if (IsKeyDown(KEY_D)) vMove.x += 1.f;
	if (IsKeyDown(KEY_W)) vMove.y -= 1.f;
	if (IsKeyDown(KEY_S)) vMove.y += 1.f;


	if (Vector2Length(vMove) < EPS_3)
	{
		const std::string& sAction = m_pAnimComponent->GetCurrentAction()->GetActionName();

		if (sAction != "idle")
		{
			m_pAnimComponent->StartAction("idle");
		}
		return;
	}

	vMove = Vector2Normalize(vMove);

	const std::string& sAction = m_pAnimComponent->GetCurrentAction()->GetActionName();
	

	const char* pNextAction = nullptr;

	if (vMove.x <= -EPS_3)
	{
		pNextAction = "walk_left";
	}
	else if (vMove.x >= EPS_3)
	{
		pNextAction = "walk_right";
	}
	else if (vMove.y >= EPS_3)
	{
		pNextAction = "walk_down";
	}
	else
	{
		pNextAction = "walk_up";
	}

	if (sAction != pNextAction)
	{
		m_pAnimComponent->StartAction(pNextAction);
	}

	GetEntity()->SetPos(GetEntity()->GetPos() + vMove * SPEED * _fDeltaTime);
}

void CControllerComponent::PostPhyshics(float _fDeltaTime)
{
	Super::PostPhyshics(_fDeltaTime);
}
