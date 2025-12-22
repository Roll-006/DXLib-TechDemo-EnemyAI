#pragma once

enum class PlayerStateKind
{
	kNone = -1,

	kIdle,
	kDead,
	kGrabbed,
	kFrontKick,
	kRoundhouseKick,
	kSuplex,
	kEscape,
	kStealthKill,
	kFinishOff,
	kEscapeWithKnife,
	kVictoryPose,
	kAttachWeapon,
	kDetachWeapon,
	kEquipKnife,
	kAimKnife,
	kStabKnife,
	kFirstSideSlashKnife,
	kSecondSideSlashKnife,
	kSpinningSlashKnife,
	kParry,
	kEquipGun,
	kAimGun,
	kShot,
	kShotRocketLauncher,
	kReload,
};
