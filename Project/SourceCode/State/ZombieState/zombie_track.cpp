#include "../../Object/zombie.hpp"
#include "../../Animator/animator.hpp"
#include "../../Kind/zombie_state_kind.hpp"
#include "zombie_state.hpp"
#include "zombie_track.hpp"

zombie_state::Track::Track(Zombie& zombie, zombie_state::State& state, const std::shared_ptr<Animator>& animator) :
	ZombieStateBase	(zombie, state, animator, ZombieStateKind::kTrack),
	m_in_sight_timer(0.0f)
{

}

zombie_state::Track::~Track()
{

}

void zombie_state::Track::Update()
{
	// 追跡中の移動・向き制御などがあればここ
}

void zombie_state::Track::LateUpdate()
{

}

void zombie_state::Track::Enter()
{
	m_in_sight_timer = 0.0f;
}

void zombie_state::Track::Exit()
{

}

ZombieStateKind zombie_state::Track::GetNextStateKind()
{
	if (m_zombie.GetDeltaTime() <= 0.0f)
	{
		return ZombieStateKind::kNone;
	}
	// 強制待機
	else if (m_state.TryWaitForcibly())
	{
		return ZombieStateKind::kIdle;
	}
	// ダッシュ攻撃
	else if (m_state.TryRunAttack())
	{
		return ZombieStateKind::kGrabRun;
	}
	// 追跡終了 → 待機
	else if (!m_state.TryTrack() && !m_state.TryGrabRun())
	{
		return ZombieStateKind::kIdle;
	}

	return ZombieStateKind::kNone;
}