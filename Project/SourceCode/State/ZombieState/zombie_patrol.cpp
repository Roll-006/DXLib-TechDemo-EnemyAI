#include "../../Object/zombie.hpp"
#include "../../Animator/animator.hpp"
#include "../../Kind/zombie_state_kind.hpp"
#include "zombie_state.hpp"
#include "zombie_patrol.hpp"

zombie_state::Patrol::Patrol(Zombie& zombie, zombie_state::State& state, const std::shared_ptr<Animator>& animator) :
	ZombieStateBase(zombie, state, animator, ZombieStateKind::kPatrol)
{

}

zombie_state::Patrol::~Patrol()
{

}

void zombie_state::Patrol::Update()
{

}

void zombie_state::Patrol::LateUpdate()
{

}

void zombie_state::Patrol::Enter()
{

}

void zombie_state::Patrol::Exit()
{

}

ZombieStateKind zombie_state::Patrol::GetNextStateKind()
{
	if (m_zombie.GetDeltaTime() <= 0.0f)
	{
		return ZombieStateKind::kNone;
	}
	// 強制待機
	else if (m_state.TryWaitForcibly())
	{
		return ZombieStateKind::kWait;
	}
	// 巡回終了 → 待機
	else if (m_zombie.GetPatrolRouteGiver()->IsEnd())
	{
		return ZombieStateKind::kWait;
	}
	// ダッシュ攻撃
	else if (m_state.TryRunAttack())
	{
		return ZombieStateKind::kRunAttack;
	}
	// 追跡
	else if (m_state.TryTrack())
	{
		return ZombieStateKind::kTrack;
	}

	return ZombieStateKind::kNone;
}
