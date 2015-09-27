#ifndef FATHOM_SHARK_HPP
#define FATHOM_SHARK_HPP

#include "jam-engine/Core/Entity.hpp"
#include "jam-engine/Core/Ref.hpp"
#include "jam-engine/Graphics/Animation.hpp"

namespace fathom
{

class Diver;
class Ocean;

class Shark : public je::Entity
{
public:
	Shark(Ocean *ocean, const sf::Vector2f& pos);

	bool damage(int amount, const sf::Vector2f& bloodVeloc = sf::Vector2f());

private:
	void draw(sf::RenderTarget& target, const sf::RenderStates &states) const override;

	void onUpdate() override;

	void patrolRandomDirection();

	float getPatrolSpeed() const;

	je::Animation attackAnim;
	sf::Vector2f veloc;
	je::Ref<Diver> target;
	int hp;
	Ocean *ocean;
	int hackyCooldown;
};

} // fathom

#endif // FATHOM_SHARK_HPP
