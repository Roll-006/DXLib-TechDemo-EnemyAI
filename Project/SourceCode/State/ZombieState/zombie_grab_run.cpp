#include "../../Object/zombie.hpp"
#include "../../Animator/animator.hpp"
#include "../../Kind/zombie_state_kind.hpp"
#include "zombie_state.hpp"
#include "zombie_grab_run.hpp"

zombie_state::GrabRun::GrabRun(Zombie& zombie, zombie_state::State& state, const std::shared_ptr<Animator>& animator) :
	ZombieStateBase(zombie, state, animator, ZombieStateKind::kGrabRun),
	m_track_timer(0.0f)
{

}

zombie_state::GrabRun::~GrabRun()
{

}

void zombie_state::GrabRun::Update()
{
	m_track_timer += m_zombie.GetDeltaTime();

	m_zombie.UpdateGrabRun();
}

void zombie_state::GrabRun::LateUpdate()
{
	m_zombie.OnFootIK();
}

void zombie_state::GrabRun::Enter()
{
	m_track_timer = 0.0f;

	m_zombie.SetUpAttackIntervalTime();
}

void zombie_state::GrabRun::Exit()
{

}

const ZombieStateKind zombie_state::GrabRun::GetNextStateKind()
{
	//if (m_zombie.GetDeltaTime() <= 0.0f)
	//{
	//	return ZombieStateKind::kNone;
	//}
	//// 強制NULL
	//else if (m_state.TryActionNullForcibly())
	//{
	//	return ZombieStateKind::kNone;
	//}
	//// ステルスキルされた
	//else if (m_state.TryStealthKilled())
	//{
	//	return ZombieStateKind::kStealthKilled;
	//}
	//// ノックバック
	//else if (m_state.TryKnockback())
	//{
	//	return ZombieStateKind::kKnockback;
	//}
	//// ノックバック(後ろ)
	//else if (m_state.TryBackwardKnockback())
	//{
	//	// TODO : ここに書くべきではない
	//	m_zombie.OnKnockback(-m_zombie.GetCurrentLookDir(), 70.0f, 60.0f);
	//	return ZombieStateKind::kBackwardKnockback;
	//}
	//// 死亡
	//else if (m_state.TryDead())
	//{
	//	return ZombieStateKind::kDead;
	//}
	//// 左足ダウン
	//else if (m_state.TryLeftCrouchStun())
	//{
	//	return ZombieStateKind::kCrouchLeftStun;
	//}
	//// 右足ダウン
	//else if (m_state.TryRightCrouchStun())
	//{
	//	return ZombieStateKind::kCrouchRightStun;
	//}
	//// 立ちダウン
	//else if (m_state.TryStandStun())
	//{
	//	return ZombieStateKind::kStandStun;
	//}
	//// 掴み
	//else if (m_zombie.CanGrabTarget())
	//{
	//	return ZombieStateKind::kGrab;
	//}
	//// 追跡時間超過 → NULL
	//else if (m_track_timer > kMaxTrackTime)
	//{
	//	return ZombieStateKind::kNone;
	//}

	return ZombieStateKind::kNone;
}
