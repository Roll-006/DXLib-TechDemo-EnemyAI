#include "../../Object/player.hpp"
#include "../../Animator/animator.hpp"
#include "../../Kind/player_state_kind.hpp"
#include "player_state.hpp"
#include "player_aim_knife.hpp"

player_state::AimKnife::AimKnife(Player& player, player_state::State& state, const std::shared_ptr<Animator>& animator) :
	PlayerStateBase(player, state, animator, PlayerStateKind::kAimKnife)
{
}

player_state::AimKnife::~AimKnife()
{
}

void player_state::AimKnife::Update()
{
	m_player.StopSearchStealthKillTarget();
	m_player.StopSearchMeleeTarget();
	m_player.AllowCalcLookDir();
	m_player.SetLookDirOffsetValueForAim();
	m_player.DirOfCameraForward();

	m_player.GetCurrentHeldWeapon()->Update();
}

void player_state::AimKnife::LateUpdate()
{
	const auto camera = ObjAccessor::GetInstance()->GetObj<ObjBase>(ObjName.MAIN_CAMERA);
	const auto aim_dir = camera->GetTransform()->GetForward(CoordinateKind::kWorld);

	// ボーン位置補正
	m_player.GetFramePosCorrector()->CorrectAimPoseFramePos(
		m_player.GetModeler()->GetModelHandle(),
		aim_dir);
}

void player_state::AimKnife::Enter()
{
	const auto cinemachine_brain = CinemachineBrain::GetInstance();
	const auto camera_controller = std::static_pointer_cast<ControlVirtualCamerasController>(
		cinemachine_brain->GetVirtualCameraController(VirtualCameraControllerKind::kControl));

	camera_controller->GetHaveVirtualCamera(ObjName.ROT_CONTROL_VIRTUAL_CAMERA)->Deactivate();
	camera_controller->GetHaveVirtualCamera(ObjName.AIM_CONTROL_VIRTUAL_CAMERA)->Activate();

	m_player.DetachWeapon(m_player.GetCurrentEquipWeapon(WeaponSlotKind::kSub));
	m_player.HoldWeapon(m_player.GetCurrentEquipWeapon(WeaponSlotKind::kSub));
}

void player_state::AimKnife::Exit()
{
	const auto cinemachine_brain = CinemachineBrain::GetInstance();
	const auto camera_controller = std::static_pointer_cast<ControlVirtualCamerasController>(
		cinemachine_brain->GetVirtualCameraController(VirtualCameraControllerKind::kControl));

	cinemachine_brain->SetBlendTime(0.3f);
	camera_controller->GetHaveVirtualCamera(ObjName.ROT_CONTROL_VIRTUAL_CAMERA)->Activate();
	camera_controller->GetHaveVirtualCamera(ObjName.AIM_CONTROL_VIRTUAL_CAMERA)->Deactivate();

	m_player.ReleaseWeapon();
	m_player.AttachWeapon(m_player.GetCurrentEquipWeapon(WeaponSlotKind::kSub));
}

PlayerStateKind player_state::AimKnife::GetNextStateKind()
{
	if (m_player.GetDeltaTime() <= 0.0f)
	{
		return PlayerStateKind::kNone;
	}
	// 銃に切り替え
	else if (m_state.TryEquipGun())
	{
		return PlayerStateKind::kEquipGun;
	}
	// ナイフ解除
	else if (!m_state.TryAimKnife())
	{
		return PlayerStateKind::kEquipKnife;
	}
	// 刺突
	else if (m_state.TryStabKnife())
	{
		return PlayerStateKind::kStabKnife;
	}

	return PlayerStateKind::kNone;
}
