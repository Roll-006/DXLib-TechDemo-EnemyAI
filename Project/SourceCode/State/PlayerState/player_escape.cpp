#include "../../Object/player.hpp"
#include "../../Kind/player_anim_kind.hpp"
#include "../../Animator/animator.hpp"
#include "../../Kind/player_state_kind.hpp"
#include "player_state.hpp"
#include "player_escape.hpp"

player_state::Escape::Escape(Player& player, player_state::State& state, const std::shared_ptr<Animator>& animator) :
	PlayerStateBase(player, state, animator, PlayerStateKind::kEscape)
{
}

player_state::Escape::~Escape()
{
}

void player_state::Escape::Update()
{
	m_player.ActivateInvincibleForcibly();
}

void player_state::Escape::LateUpdate()
{
}

void player_state::Escape::Enter()
{
}

void player_state::Escape::Exit()
{
}

const PlayerStateKind player_state::Escape::GetNextStateKind()
{
	//if (m_player.GetDeltaTime() <= 0.0f)
	//{
	//	return PlayerStateKind::kNone;
	//}

	//// 上半身アニメーション終了 → NULL
	//if (m_animator->IsPlayEnd(Animator::BodyKind::kUpperBody))
	//{
	//	return PlayerStateKind::kActionNull;
	//}

	return PlayerStateKind::kNone;
}
