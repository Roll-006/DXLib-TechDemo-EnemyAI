#include "../../Object/player.hpp"
#include "../../Kind/player_anim_kind.hpp"
#include "../../Animator/animator.hpp"
#include "../../Kind/player_state_kind.hpp"
#include "../../Command/command_handler.hpp"
#include "player_state.hpp"
#include "player_idle.hpp"

player_state::Idle::Idle(Player& player, player_state::State& state, const std::shared_ptr<Animator>& animator) :
	PlayerStateBase(player, state, animator, PlayerStateKind::kIdle),
	m_non_move_time(0.0f)
{
	m_walk_forward_anim_kind		.at(Animator::BodyKind::kUpperBody) = PlayerAnimKind::kIdle;
	m_crouch_walk_forward_anim_kind	.at(Animator::BodyKind::kUpperBody) = PlayerAnimKind::kIdle;
	m_crouch_anim_kind				.at(Animator::BodyKind::kUpperBody) = PlayerAnimKind::kIdle;
}

player_state::Idle::~Idle()
{
}

void player_state::Idle::Update()
{
	BasicMove();
}

void player_state::Idle::LateUpdate()
{
}

void player_state::Idle::Enter()
{
	
}

void player_state::Idle::Exit()
{
}

const PlayerStateKind player_state::Idle::GetNextStateKind()
{
	if (m_player.GetDeltaTime() <= 0.0f)
	{
		return PlayerStateKind::kNone;
	}
	// 銃装備状態
	if (m_state.TryEquipGunShortcut())
	{
		return PlayerStateKind::kEquipGun;
	}
	// 銃装備状態
	if (m_state.TryEquipGun())
	{
		return PlayerStateKind::kEquipGun;
	}
	// リロード
	if (m_state.TryReload())
	{
		return PlayerStateKind::kReload;
	}
	// ナイフ装備状態
	if (m_state.GetPrevStateKind() == PlayerStateKind::kStealthKill)
	{
		return PlayerStateKind::kEquipKnife;
	}
	// 回転切り
	if (m_state.TrySpinningSlash())
	{
		return PlayerStateKind::kSpinningSlashKnife;
	}
	// 切り裂く(第一段階)
	if (m_state.TryFirstSideSlashKnife())
	{
		return PlayerStateKind::kFirstSideSlashKnife;
	}

	return PlayerStateKind::kNone;
}
