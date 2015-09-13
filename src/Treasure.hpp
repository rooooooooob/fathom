#ifndef FATHOM_TREASURE_HPP
#define FATHOM_TREASURE_HPP

#include "jam-engine/Core/Entity.hpp"
#include "jam-engine/Graphics/Animation.hpp"

namespace fathom
{

class Ocean;

class Treasure : public je::Entity
{
public:
	Treasure(Ocean *ocean, const sf::Vector2f& pos);


private:
	void draw(sf::RenderTarget& target, const sf::RenderStates &states) const override;

	void onUpdate() override;


	je::Animation animation;
	int cooldown;
	Ocean *ocean;
};

} // fathom

#endif // FATHOM_TREASURE_HPP
