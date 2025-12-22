#include "../Object/zombie.hpp"
#include "../Animator/animator.hpp"
#include "../State/ZombieState/zombie_state.hpp"
#include "../Kind/zombie_state_kind.hpp"
#include "zombie_state_base.hpp"

ZombieStateBase::ZombieStateBase(Zombie& zombie, zombie_state::State& state, const std::shared_ptr<Animator>& animator, const ZombieStateKind state_kind) :
	m_zombie	(zombie),
	m_state		(state),
	m_animator	(animator),
	m_state_kind(state_kind)
{

}

ZombieStateBase::~ZombieStateBase()
{

}

void ZombieStateBase::Move()
{

}
