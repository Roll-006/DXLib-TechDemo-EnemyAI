#include "../../Object/player.hpp"
#include "../../Animator/animator.hpp"
#include "../../Kind/player_state_kind.hpp"
#include "player_state.hpp"
#include "player_aim_gun.hpp"

player_state::AimGun::AimGun(Player& player, player_state::State& state, const std::shared_ptr<Animator>& animator) :
	PlayerStateBase(player, state, animator, PlayerStateKind::kAimGun),
	m_elapsed_time(0.0f)
{
}

player_state::AimGun::~AimGun()
{
}

void player_state::AimGun::Enter()
{
	m_elapsed_time = 0.0f;

	// カメラ設定
	const auto brain = CinemachineBrain::GetInstance();
	const auto controller =
		std::static_pointer_cast<ControlVirtualCamerasController>(
			brain->GetVirtualCameraController(VirtualCameraControllerKind::kControl));

	brain->SetBlendTime(0.3f);

	if (auto rot = controller->GetHaveVirtualCamera(ObjName.ROT_CONTROL_VIRTUAL_CAMERA))
	{
		rot->Deactivate();
	}
	if (auto aim = controller->GetHaveVirtualCamera(ObjName.AIM_CONTROL_VIRTUAL_CAMERA))
	{
		aim->Activate();
	}

	m_player.DetachWeapon(m_player.GetCurrentEquipWeapon(WeaponSlotKind::kMain));
	m_player.HoldWeapon(m_player.GetCurrentEquipWeapon(WeaponSlotKind::kMain));

	if (m_state.GetPrevStateKind() != PlayerStateKind::kShot)
	{
		const auto gun =
			std::static_pointer_cast<GunBase>(m_player.GetCurrentHeldWeapon());
		gun->InitCrossHairRange();

		EventSystem::GetInstance()->Publish(
			AimGunEvent(gun->GetTransform()->GetPos(CoordinateKind::kWorld),
				TimeScaleLayerKind::kPlayer));
	}
}

void player_state::AimGun::Update()
{
	m_elapsed_time += m_player.GetDeltaTime();

	m_player.StopSearchStealthKillTarget();
	m_player.StopSearchMeleeTarget();
	m_player.AllowCalcLookDir();
	m_player.SetLookDirOffsetValueForAim();
	m_player.DirOfCameraForward();

	const auto gun =
		std::static_pointer_cast<GunBase>(m_player.GetCurrentHeldWeapon());
	gun->CalcShotTimer();
}

void player_state::AimGun::LateUpdate()
{
	const auto gun		= std::static_pointer_cast<GunBase>(m_player.GetCurrentHeldWeapon());
	const auto camera	= ObjAccessor::GetInstance()->GetObj<ObjBase>(ObjName.MAIN_CAMERA);
	const auto aim_dir	= camera->GetTransform()->GetForward(CoordinateKind::kWorld);

	m_player.GetFramePosCorrector()->CorrectAimPoseFramePos(m_player.GetModeler()->GetModelHandle(), aim_dir);

	if (m_state.GetPrevStateKind() == PlayerStateKind::kShot)
	{
		if (m_elapsed_time > kWaitTime)
		{
			gun->CalcCrossHairRange(m_player.GetMoveVelocity());
		}
	}
	else
	{
		gun->CalcCrossHairRange(m_player.GetMoveVelocity());
	}

	gun->CalcCrossHairPos();
	gun->CalcTargetPos();
	gun->SetAimDir(aim_dir);
	gun->SetPosOnRay(camera->GetTransform()->GetPos(CoordinateKind::kWorld));
}

void player_state::AimGun::Exit()
{
	const auto brain = CinemachineBrain::GetInstance();
	const auto controller =
		std::static_pointer_cast<ControlVirtualCamerasController>(
			brain->GetVirtualCameraController(VirtualCameraControllerKind::kControl));

	brain->SetBlendTime(0.3f);

	if (auto rot = controller->GetHaveVirtualCamera(ObjName.ROT_CONTROL_VIRTUAL_CAMERA))
	{
		rot->Activate();
	}
	if (auto aim = controller->GetHaveVirtualCamera(ObjName.AIM_CONTROL_VIRTUAL_CAMERA))
	{
		aim->Deactivate();
	}

	m_player.ReleaseWeapon();
	m_player.AttachWeapon(m_player.GetCurrentEquipWeapon(WeaponSlotKind::kMain));
}

const PlayerStateKind player_state::AimGun::GetNextStateKind()
{
	//if (m_player.GetDeltaTime() <= 0.0f)
	//{
	//	return PlayerStateKind::kNone;
	//}
	//// エイム解除
	//else if (!m_state.IsAimGun())
	//{
	//	return PlayerStateKind::kEquipGun;
	//}
	//// リロード
	//else if (m_state.TryReload())
	//{
	//	return PlayerStateKind::kReload;
	//}
	//// ショット
	//else if (m_state.TryPullTrigger())
	//{
	//	const auto gun =
	//		std::static_pointer_cast<GunBase>(m_player.GetCurrentHeldWeapon());

	//	if (gun->GetGunKind() == GunKind::kRocketLauncher)
	//	{
	//		return PlayerStateKind::kShotRocketLauncher;
	//	}
	//	return PlayerStateKind::kShot;
	//}

	return PlayerStateKind::kNone;
}
