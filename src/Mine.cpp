#include "Mine.hpp"

#include <cmath>

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Utility/Random.hpp"

#include "Explosion.hpp"

namespace fathom
{

const float period = 100.f;

Mine::Mine(je::Level *level, const sf::Vector2f& pos)
	:je::Entity(level, "Mine", pos, sf::Vector2i(16, 16), sf::Vector2i(-8, -8))
	,wiggle(je::random(period))
	,startY(pos.y)
	,anim(level->getGame().getTexManager().get("mine.png"), 16, 16, 64, true)
{
	anim.setOrigin(8, 8);
}


void Mine::explode()
{
	if (!isDead())
	{
		level->addEntity(new Explosion(level, getPos()));
		destroy();
	}
}


// priate
void Mine::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
	target.draw(anim, states);
}

void Mine::onUpdate()
{
	static const char *triggers[] = {"Shark", "Diver"};
	for (const char *trigger : triggers)
	{
		if (level->testCollision(this, trigger))
		{
			explode();
		}
	}

	anim.advanceFrame();
	transform().setPosition(getPos().x, startY + 16 * sin(++wiggle / period));
	anim.setPosition(getPos());
}

} // fathom
