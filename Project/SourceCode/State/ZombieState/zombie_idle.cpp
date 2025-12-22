#include "../../Object/zombie.hpp"
#include "../../Kind/zombie_anim_kind.hpp"
#include "../../Animator/animator.hpp"
#include "../../Kind/zombie_state_kind.hpp"
#include "zombie_state.hpp"
#include "zombie_idle.hpp"

zombie_state::Idle::Idle(Zombie& zombie, zombie_state::State& state, const std::shared_ptr<Animator>& animator) :
	ZombieStateBase(zombie, state, animator, ZombieStateKind::kIdle)
{

}

zombie_state::Idle::~Idle()
{

}

void zombie_state::Idle::Update()
{
	m_zombie.CalcMoveSpeedStop();
}

void zombie_state::Idle::LateUpdate()
{

}

void zombie_state::Idle::Enter()
{

}

void zombie_state::Idle::Exit()
{

}

const ZombieStateKind zombie_state::Idle::GetNextStateKind()
{
	if (m_zombie.GetDeltaTime() <= 0.0f)
	{
		return ZombieStateKind::kNone;
	}

	return ZombieStateKind::kNone;
}
