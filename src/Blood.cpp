#include "Blood.hpp"

#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Utility/Random.hpp"

namespace fathom
{

Blood::Blood(je::Level *level, const sf::Vector2f& pos, const sf::Vector2f& veloc)
	:je::Entity(level, "Blood", pos, sf::Vector2i(8, 8), sf::Vector2i(-4, -4))
	,sprite(level->getGame().getTexManager().get("blood.png"))
	,veloc(veloc)
	,cooldown(je::randomf(64 + je::random(128)))
{
	sprite.setColor(sf::Color(255, 255, 255, 128 + je::random(127)));
	sprite.setOrigin(4, 4);
	sprite.setRotation(je::random(360));
}



void Blood::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
	target.draw(sprite, states);
}

void Blood::onUpdate()
{
	veloc.y += 0.02f;

	if (--cooldown <= 0)
	{
		destroy();
	}

	transform().move(veloc);
	sprite.setPosition(getPos());
}

} // fathom
