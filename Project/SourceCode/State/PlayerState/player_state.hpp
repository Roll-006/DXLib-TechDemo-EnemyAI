#pragma once
class Player;
class Animator;
class PlayerStateBase;
enum class PlayerStateKind;

namespace player_state
{
	class State final
	{
	public:
		State(Player& player, const std::shared_ptr<Animator>& animator);
		~State();

		void Update();
		void LateUpdate();

		[[nodiscard]] PlayerStateKind GetPrevStateKind()	const;
		[[nodiscard]] PlayerStateKind GetCurrentStateKind() const;

		#pragma region Try判定

		#pragma endregion

	private:
		Player&																	m_player;
		std::shared_ptr<PlayerStateBase>										m_current_state;
		std::unordered_map<PlayerStateKind, std::shared_ptr<PlayerStateBase>>	m_states;
	};
}
