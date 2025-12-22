#pragma once
#include "../../Base/player_state_base.hpp"

class Animator;

namespace player_state
{
	class AimKnife final : public PlayerStateBase
	{
	public:
		AimKnife(Player& player, player_state::State& state, const std::shared_ptr<Animator>& animator);
		~AimKnife();

		void Update()		override;
		void LateUpdate()	override;
		void Enter()		override;
		void Exit()			override;

		[[nodiscard]] const PlayerStateKind GetNextStateKind() override;
	};
}
