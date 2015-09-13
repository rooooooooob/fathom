#include "ShipWreck.hpp"

#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Core/Game.hpp"

#include "Ocean.hpp"

namespace fathom
{

ShipWreck::ShipWreck(Ocean *ocean, const sf::Vector2f& pos)
	:je::Entity(ocean, "ShipWreck", pos, sf::Vector2i(128, 128))
	,sprite(ocean->getGame().getTexManager().get("shipwreck.png"))
	,discovered(false)
	,ocean(ocean)
{
	sprite.setPosition(pos);
}

//private
void ShipWreck::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
	target.draw(sprite, states);
}

void ShipWreck::onUpdate()
{
	if (!discovered && ocean->testCollision(this, "Diver"))
	{
		discovered = true;
		ocean->addScore(5000);
	}
}

} // fathom
