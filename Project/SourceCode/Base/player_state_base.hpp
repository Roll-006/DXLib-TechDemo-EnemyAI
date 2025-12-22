#pragma once
class Player;
class Animator;
namespace player_state { class State; }
enum class PlayerStateKind;

class PlayerStateBase abstract
{
public:
	PlayerStateBase(Player& player, player_state::State& state, const std::shared_ptr<Animator>& animator, const PlayerStateKind state_kind);
	~PlayerStateBase();

	virtual void Update()		abstract;
	virtual void LateUpdate()	abstract;
	virtual void Enter()		abstract;
	virtual void Exit()			abstract;

	[[nodiscard]] PlayerStateKind GetPrevStateKind()	const { return m_prev_state_kind; }
	[[nodiscard]] PlayerStateKind GetCurrentStateKind() const { return m_current_state_kind; }
	[[nodiscard]] virtual PlayerStateKind GetNextStateKind() abstract;

protected:
	#pragma region 汎用行動
	void Move();
	void Crouch();
	#pragma endregion

protected:
	Player&						m_player;
	player_state::State&		m_state;
	std::shared_ptr<Animator>	m_animator;
	PlayerStateKind				m_prev_state_kind;
	PlayerStateKind				m_current_state_kind;
};
