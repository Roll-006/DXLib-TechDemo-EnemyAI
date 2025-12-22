#include "../../Object/zombie.hpp"
#include "../../Animator/animator.hpp"
#include "../../Kind/zombie_state_kind.hpp"
#include "zombie_state.hpp"
#include "zombie_stand_up.hpp"

zombie_state::StandUp::StandUp(Zombie& zombie, zombie_state::State& state, const std::shared_ptr<Animator>& animator) :
	ZombieStateBase(zombie, state, animator, ZombieStateKind::kStandUp)
{

}

zombie_state::StandUp::~StandUp()
{

}

void zombie_state::StandUp::Update()
{
	if (m_zombie.CanAction())
	{
		m_zombie.CalcAttackIntervalTime();
	}

	m_zombie.DisallowStealthKill();
}

void zombie_state::StandUp::LateUpdate()
{

}

void zombie_state::StandUp::Enter()
{

}

void zombie_state::StandUp::Exit()
{

}

ZombieStateKind zombie_state::StandUp::GetNextStateKind()
{
	if (m_zombie.GetDeltaTime() <= 0.0f)
	{
		return ZombieStateKind::kNone;
	}
	// ステルスキルされた
	else if (m_state.TryStealthKilled())
	{
		return ZombieStateKind::kStealthKilled;
	}
	// ノックバック
	else if (m_state.TryKnockback())
	{
		return ZombieStateKind::kKnockback;
	}
	// ノックバック(後ろ)
	else if (m_state.TryBackwardKnockback())
	{
		// TODO : ここに書くべきではない
		m_zombie.OnKnockback(-m_zombie.GetCurrentLookDir(), 70.0f, 60.0f);
		return ZombieStateKind::kBackwardKnockback;
	}
	// 上半身アニメーション終了 → NULL
	else if (m_animator->IsPlayEnd(Animator::BodyKind::kUpperBody))
	{
		return ZombieStateKind::kIdle;
	}

	return ZombieStateKind::kNone;
}
