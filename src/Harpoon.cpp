#include "Harpoon.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"

#include "Diver.hpp"
#include "Mine.hpp"
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
	if (je::Ref<Shark> toKill = level->testCollision(this, "Shark"))
	{
		toKill->damage(30, veloc * 0.2f);
		destroy();
		return;
	}
	if (je::Ref<Shark> toKill = level->testCollision(this, "Diver"))
	{
		toKill->damage(20, veloc * 0.2f);
		destroy();
		return;
	}
	if (je::Ref<Mine> toKill = level->testCollision(this, "Mine"))
	{
		toKill->explode();
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
