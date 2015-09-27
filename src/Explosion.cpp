#include "Explosion.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Physics/CircleMask.hpp"
#include "jam-engine/Utility/Random.hpp"

#include "Mine.hpp"

namespace fathom
{

const je::CircleMask explosionMasks[6] = {
	5 / 2, 20 / 2, 36 / 2, 42 / 2, 45 / 2, 52 / 2
};

Explosion::Explosion(je::Level *level, const sf::Vector2f& pos)
	:je::Entity(level, "Explosion", pos, explosionMasks[0].clone())
	,maskIndex(0)
	,anim(level->getGame().getTexManager().get("explosion.png"), 128, 128, 4, false)
{
	transform().setPosition(pos); // to make masks be in right pos
	anim.setOrigin(64, 64);
}


void Explosion::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
	target.draw(anim, states);
}

void Explosion::onUpdate()
{
	std::vector<je::Ref<je::Entity>> deathToAll;
	level->findCollisions(deathToAll, this, "Mine");
	for (je::Ref<Mine> mine : deathToAll)
	{
		mine->explode();
	}
	deathToAll.clear();

	if (anim.isFinished())
	{
		destroy();
	}
	if (anim.advanceFrame())
	{
		setMask(explosionMasks[++maskIndex].clone());
	}
	transform().setPosition(getPos());
	anim.setPosition(getPos());
}

} // fathom
