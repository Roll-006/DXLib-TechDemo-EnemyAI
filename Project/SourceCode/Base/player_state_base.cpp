#include "../Object/player.hpp"
#include "../Animator/animator.hpp"
#include "../State/PlayerState/player_state.hpp"
#include "../Kind/player_state_kind.hpp"
#include "player_state_base.hpp"

PlayerStateBase::PlayerStateBase(Player& player, player_state::State& state, const std::shared_ptr<Animator>& animator, const PlayerStateKind state_kind) :
	m_player	(player),
	m_state		(state),
	m_animator	(animator),
	m_current_state_kind(state_kind)
{

}

PlayerStateBase::~PlayerStateBase()
{

}

void PlayerStateBase::Move()
{

}

void  PlayerStateBase::Crouch()
{

}
