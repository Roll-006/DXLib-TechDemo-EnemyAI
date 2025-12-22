#include "../../Object/player.hpp"
#include "../../Animator/animator.hpp"
#include "../../Event/event_system.hpp"
#include "../../Kind/player_state_kind.hpp"
#include "player_state.hpp"
#include "player_grabbed.hpp"

player_state::Grabbed::Grabbed(Player& player, player_state::State& state, const std::shared_ptr<Animator>& animator) :
	PlayerStateBase(player, state, animator, PlayerStateKind::kGrabbed)
{
}

player_state::Grabbed::~Grabbed()
{
}

void player_state::Grabbed::Update()
{
	m_player.UpdateGrabbed();
}

void player_state::Grabbed::LateUpdate()
{
	m_player.OnFootIK();
}

void player_state::Grabbed::Enter()
{
	const OnGrabEvent event{ m_player.GetModeler(), m_player.GetObjHandle() };
	EventSystem::GetInstance()->Publish(event);
}

void player_state::Grabbed::Exit()
{
}

const PlayerStateKind player_state::Grabbed::GetNextStateKind()
{
	//if (m_player.GetDeltaTime() <= 0.0f)
	//{
	//	return PlayerStateKind::kNone;
	//}

	//const auto state_controller = m_player.GetStateController();

	//if (state_controller->TryDead(&m_player))
	//{
	//	return PlayerStateKind::kDead;
	//}
	//if (m_player.IsEscape())
	//{
	//	return PlayerStateKind::kEscape;
	//}
	//if (!state_controller->TryGrabbed(&m_player))
	//{
	//	return PlayerStateKind::kActionNull;
	//}

	return PlayerStateKind::kNone;
}
