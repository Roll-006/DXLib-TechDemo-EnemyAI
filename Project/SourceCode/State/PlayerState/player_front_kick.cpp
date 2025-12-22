#include "../../Object/player.hpp"
#include "../../Kind/player_anim_kind.hpp"
#include "../../Animator/animator.hpp"
#include "../../Part/collider.hpp"
#include "../../Event/event_system.hpp"
#include "../../Kind/player_state_kind.hpp"
#include "../../Kind/player_anim_kind.hpp"
#include "player_state.hpp"
#include "player_front_kick.hpp"

player_state::FrontKick::FrontKick(Player& player, player_state::State& state, const std::shared_ptr<Animator>& animator) :
	PlayerStateBase(player, state, animator, PlayerStateKind::kFrontKick),
	m_has_trigger_created(false),
	m_has_trigger_deleted(false)
{
}

player_state::FrontKick::~FrontKick()
{
}

void player_state::FrontKick::Update()
{
	m_player.UpdateMelee();

	const auto animator = m_player.GetAnimator();
	const auto anim_kind = static_cast<PlayerAnimKind>(animator->GetAnimKind(Animator::BodyKind::kUpperBody, TimeKind::kCurrent));

	// 攻撃判定用トリガーを追加
	if (!m_has_trigger_created && animator->GetPlayRate(Animator::BodyKind::kUpperBody) > 0.3f && anim_kind == PlayerAnimKind::kFrontKick)
	{
		m_player.AddCollider(std::make_shared<Collider>(
			ColliderKind::kAttackTrigger,
			std::make_shared<Capsule>(v3d::GetZeroV(), v3d::GetZeroV(), kAttackTriggerRadius),
			&m_player));
		m_has_trigger_created = true;
	}

	// 攻撃判定用トリガーを削除
	if (!m_has_trigger_deleted && animator->GetPlayRate(Animator::BodyKind::kUpperBody) > 0.8f && anim_kind == PlayerAnimKind::kFrontKick)
	{
		m_player.RemoveCollider(ColliderKind::kAttackTrigger);
		m_has_trigger_deleted = true;
	}

	// 座標計算
	if (m_has_trigger_created && !m_has_trigger_deleted)
	{
		m_player.GetModeler()->ApplyMatrix();
		const auto model_handle = m_player.GetModeler()->GetModelHandle();

		auto right_leg_m = MV1GetFrameLocalWorldMatrix(model_handle, MV1SearchFrame(model_handle, FramePath.RIGHT_LEG));
		auto right_foot_m = MV1GetFrameLocalWorldMatrix(model_handle, MV1SearchFrame(model_handle, FramePath.RIGHT_FOOT));

		const auto right_leg_pos = matrix::GetPos(right_leg_m);
		const auto right_foot_pos = matrix::GetPos(right_foot_m);

		const auto capsule = std::static_pointer_cast<Capsule>(m_player.GetCollider(ColliderKind::kAttackTrigger)->GetShape());

		capsule->SetSegmentBeginPos(right_leg_pos, true);
		capsule->SetSegmentEndPos(right_foot_pos, true);
	}
}

void player_state::FrontKick::LateUpdate()
{
}

void player_state::FrontKick::Enter()
{
	m_has_trigger_created = false;
	m_has_trigger_deleted = false;

	m_player.SetupFrontMelee();
}

void player_state::FrontKick::Exit()
{
}

const PlayerStateKind player_state::FrontKick::GetNextStateKind()
{
	//if (m_player.GetDeltaTime() <= 0.0f)
	//{
	//	return PlayerStateKind::kNone;
	//}

	//if (m_animator->IsPlayEnd(Animator::BodyKind::kUpperBody))
	//{
	//	return PlayerStateKind::kActionNull;
	//}

	return PlayerStateKind::kNone;
}
