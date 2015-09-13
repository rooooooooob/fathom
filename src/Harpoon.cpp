#include "Harpoon.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"

#include "Diver.hpp"
#include "Shark.hpp"

namespace fathom
{

Harpoon::Harpoon(je::Level *level, const sf::Vector2f& pos, const sf::Vector2f& veloc)
	:je::Entity(level, "Harpoon", pos, sf::Vector2i(9, 2), sf::Vector2i(-5, -1))
	,veloc(veloc)
{
	sprite.setTexture(level->getGame().getTexManager().get("harpoon.png"));
	sprite.setOrigin(5, 1);
	sprite.setPosition(pos);
	sprite.setScale(veloc.x > 0.f ? 1.f : -1.f, 1.f);
}

void Harpoon::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
	target.draw(sprite, states);
}

void Harpoon::onUpdate()
{
	je::Entity* toKill = level->testCollision(this, "Shark");
	if (toKill)
	{
		((Shark*)toKill)->damage(30);
		destroy();
		return;
	}
	toKill = level->testCollision(this, "Diver");
	if (toKill)
	{
		((Diver*)toKill)->damage(30);
		destroy();
		return;
	}

	veloc *= 0.9f;
	veloc.y += 0.1f;
	if (veloc.x < 2.f && veloc.x > -0.2f)
	{
		destroy();
	}
	transform().move(veloc);
	sprite.setPosition(getPos());
}

} // fathom
