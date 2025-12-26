#include "../Object/zombie.hpp"
#include "../Animator/animator.hpp"
#include "../State/ZombieState/zombie_state.hpp"
#include "../Kind/zombie_state_kind.hpp"
#include "../Kind/zombie_anim_kind.hpp"
#include "zombie_state_base.hpp"

ZombieStateBase::ZombieStateBase(Zombie& zombie, zombie_state::State& state, const std::shared_ptr<Animator>& animator, const ZombieStateKind state_kind) :
	m_zombie	(zombie),
	m_state		(state),
	m_animator	(animator),
	m_state_kind(state_kind),
	m_prev_run	(false)
{

}

ZombieStateBase::~ZombieStateBase()
{

}

void ZombieStateBase::Move()
{
	m_zombie.Move();

	// ダッシュ
	if (m_state.TryRun())
	{
		m_zombie.CalcMoveSpeedRun();
		m_prev_run = true;

		m_animator->AttachResultAnim(static_cast<int>(ZombieAnimKind::kMoveForwardRun));
	}
	// 歩く
	else if (m_state.TryWalk())
	{
		m_zombie.CalcMoveSpeed();
		m_prev_run = false;

		m_animator->AttachResultAnim(static_cast<int>(ZombieAnimKind::kMoveForwardWalk));
	}
	// どちらでもない場合は以前の状態を引き継ぐ
	else if(m_prev_run)
	{
		m_zombie.CalcMoveSpeedRun();

		m_animator->AttachResultAnim(static_cast<int>(ZombieAnimKind::kMoveForwardRun));
	}
	else
	{
		m_zombie.CalcMoveSpeed();

		m_animator->AttachResultAnim(static_cast<int>(ZombieAnimKind::kMoveForwardWalk));
	}

	if (m_zombie.CanAction())
	{
		m_zombie.CalcAttackIntervalTime();
	}
}
