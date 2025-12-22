#include "../../Object/player.hpp"
#include "../../Animator/animator.hpp"
#include "../../Event/event_system.hpp"
#include "../../Kind/player_state_kind.hpp"
#include "player_state.hpp"
#include "player_victory_pose.hpp"

player_state::VictoryPose::VictoryPose(Player& player, State& state, const std::shared_ptr<Animator>& animator) :
    PlayerStateBase(player, state, animator, PlayerStateKind::kVictoryPose),
    m_camera_controller(nullptr)
{
}

player_state::VictoryPose::~VictoryPose()
{
}

void player_state::VictoryPose::Update()
{
}

void player_state::VictoryPose::LateUpdate()
{
}

void player_state::VictoryPose::Enter()
{
    const auto cinemachine_brain = CinemachineBrain::GetInstance();
    m_camera_controller = std::make_shared<GameClearVirtualCamerasController>(m_player.GetModeler()->GetModelHandle(), m_player.GetTransform());
    cinemachine_brain->AddVirtualCameraController(m_camera_controller);

    const VictoryPoseEvent event{ m_player.GetTransform(), m_player.GetModeler() };
    EventSystem::GetInstance()->Publish(event);
}

void player_state::VictoryPose::Exit()
{
    const auto cinemachine_brain = CinemachineBrain::GetInstance();
    cinemachine_brain->RemoveVirtualCameraController(m_camera_controller);
    m_camera_controller = nullptr;
}

const PlayerStateKind player_state::VictoryPose::GetNextStateKind()
{
    return PlayerStateKind::kNone;
}
