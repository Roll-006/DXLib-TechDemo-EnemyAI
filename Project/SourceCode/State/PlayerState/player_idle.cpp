#include "../../Object/player.hpp"
#include "../../Kind/player_anim_kind.hpp"
#include "../../Animator/animator.hpp"
#include "../../Kind/player_state_kind.hpp"
#include "player_state.hpp"
#include "player_idle.hpp"

player_state::Idle::Idle(Player& player, player_state::State& state, const std::shared_ptr<Animator>& animator) :
	PlayerStateBase(player, state, animator, PlayerStateKind::kIdle),
	m_non_move_time(0.0f)
{
}

player_state::Idle::~Idle()
{
}

void player_state::Idle::Update()
{
	m_player.CalcMoveSpeedStop();

	// 非移動時間を計測したい場合はコメント解除
	// m_non_move_time += FPS::GetDeltaTime();
}

void player_state::Idle::LateUpdate()
{
}

void player_state::Idle::Enter()
{
	m_animator->AttachResultAnim(static_cast<int>(PlayerAnimKind::kIdle));
}

void player_state::Idle::Exit()
{
}

const PlayerStateKind player_state::Idle::GetNextStateKind()
{
	//if (m_player.GetDeltaTime() <= 0.0f) { return PlayerStateKind::kNone; }

	//// 入力があった場合、Moveへ移行
	//if (m_player.GetStateController()->TryMove(m_player))
	//{
	//	return PlayerStateKind::kMove;
	//}

	return PlayerStateKind::kNone;
}
