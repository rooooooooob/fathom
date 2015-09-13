#ifndef FATHOM_SHIPWRECK_HPP
#define FATHOM_SHIPWRECK_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "jam-engine/Core/Entity.hpp"

namespace fathom
{

class Ocean;

class ShipWreck : public je::Entity
{
public:
	ShipWreck(Ocean *ocean, const sf::Vector2f& pos);


private:
	void draw(sf::RenderTarget& target, const sf::RenderStates &states) const override;

	void onUpdate() override;


	sf::Sprite sprite;
	bool discovered;
	Ocean *ocean;
};

} // fathom

#endif // FATHOM_SHIPWRECK_HPP
