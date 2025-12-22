#include <memory>
#include <unordered_map>
#include "../../Object/player.hpp"
#include "../../Animator/animator.hpp"
#include "../../Base/player_state_base.hpp"
#include "../../Kind/player_state_kind.hpp"

#include "player_idle.hpp"
#include "player_dead.hpp"
#include "player_attach_weapon.hpp"
#include "player_detach_weapon.hpp"
#include "player_aim_gun.hpp"
#include "player_aim_knife.hpp"
#include "player_equip_gun.hpp"
#include "player_equip_knife.hpp"
#include "player_reload.hpp"
#include "player_shot.hpp"
#include "player_shot_rocket_launcher.hpp"
#include "player_first_side_slash_knife.hpp"
#include "player_second_side_slash_knife.hpp"
#include "player_spinning_slash_knife.hpp"
#include "player_front_kick.hpp"
#include "player_roundhouse_kick.hpp"
#include "player_escape.hpp"
#include "player_grabbed.hpp"
#include "player_stealth_kill.hpp"
#include "player_victory_pose.hpp"

#include "player_state.hpp"

player_state::State::State(Player& player, const std::shared_ptr<Animator>& animator) :
	m_player			(player),
	m_current_state		(nullptr),
	m_prev_state_kind	(PlayerStateKind::kIdle)
{
	m_states[PlayerStateKind::kIdle]					= std::make_shared<player_state::Idle>					(m_player, *this, animator);
	m_states[PlayerStateKind::kDead]					= std::make_shared<player_state::Dead>					(m_player, *this, animator);
	m_states[PlayerStateKind::kAttachWeapon]			= std::make_shared<player_state::AttachWeapon>			(m_player, *this, animator);
	m_states[PlayerStateKind::kDetachWeapon]			= std::make_shared<player_state::DetachWeapon>			(m_player, *this, animator);
	m_states[PlayerStateKind::kAimGun]					= std::make_shared<player_state::AimGun>				(m_player, *this, animator);
	m_states[PlayerStateKind::kAimKnife]				= std::make_shared<player_state::AimKnife>				(m_player, *this, animator);
	m_states[PlayerStateKind::kEquipGun]				= std::make_shared<player_state::EquipGun>				(m_player, *this, animator);
	m_states[PlayerStateKind::kEquipKnife]				= std::make_shared<player_state::EquipKnife>			(m_player, *this, animator);
	m_states[PlayerStateKind::kReload]					= std::make_shared<player_state::Reload>				(m_player, *this, animator);
	m_states[PlayerStateKind::kShot]					= std::make_shared<player_state::Shot>					(m_player, *this, animator);
	m_states[PlayerStateKind::kShotRocketLauncher]		= std::make_shared<player_state::ShotRocketLauncher>	(m_player, *this, animator);
	m_states[PlayerStateKind::kFirstSideSlashKnife]		= std::make_shared<player_state::FirstSideSlashKnife>	(m_player, *this, animator);
	m_states[PlayerStateKind::kSecondSideSlashKnife]	= std::make_shared<player_state::SecondSideSlashKnife>	(m_player, *this, animator);
	m_states[PlayerStateKind::kSpinningSlashKnife]		= std::make_shared<player_state::SpinningSlashKnife>	(m_player, *this, animator);
	m_states[PlayerStateKind::kFrontKick]				= std::make_shared<player_state::FrontKick>				(m_player, *this, animator);
	m_states[PlayerStateKind::kRoundhouseKick]			= std::make_shared<player_state::RoundhouseKick>		(m_player, *this, animator);
	m_states[PlayerStateKind::kEscape]					= std::make_shared<player_state::Escape>				(m_player, *this, animator);
	m_states[PlayerStateKind::kGrabbed]					= std::make_shared<player_state::Grabbed>				(m_player, *this, animator);
	m_states[PlayerStateKind::kStealthKill]				= std::make_shared<player_state::StealthKill>			(m_player, *this, animator);
	m_states[PlayerStateKind::kVictoryPose]				= std::make_shared<player_state::VictoryPose>			(m_player, *this, animator);

	m_current_state = m_states.at(PlayerStateKind::kIdle);
}

player_state::State::~State()
{

}

void player_state::State::Update()
{
	// 次のステートがNoneでない場合はステートを変更
	const auto next_state_kind = m_current_state->GetNextStateKind();
	if (next_state_kind != PlayerStateKind::kNone)
	{
		m_prev_state_kind = m_current_state->GetStateKind();
		m_current_state->Exit();
		m_current_state = m_states.at(next_state_kind);
		m_current_state->Enter();
	}

	m_current_state->Update();
}

void player_state::State::LateUpdate()
{
	m_current_state->LateUpdate();
}

const PlayerStateKind player_state::State::GetPrevStateKind() const
{
	return m_prev_state_kind;
}

const PlayerStateKind player_state::State::GetCurrentStateKind() const
{
	return m_current_state->GetStateKind();
}


#pragma region Try判定
#pragma endregion