#include "Explosion.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Utility/Random.hpp"

#include "Mine.hpp"

namespace fathom
{

Explosion::Explosion(je::Level *level, const sf::Vector2f& pos)
	:je::Entity(level, "Explosion", pos, sf::Vector2i(128, 128), sf::Vector2i(-64, -64))
	,anim(level->getGame().getTexManager().get("explosion.png"), 128, 128, 4, false)
{
	anim.setOrigin(64, 64);
}


void Explosion::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
	target.draw(anim, states);
}

void Explosion::onUpdate()
{
	std::vector<je::Entity*> deathToAll;
	level->findCollisions(deathToAll, this, "Mine");
	for (je::Entity *mine : deathToAll)
	{
		((Mine*)mine)->explode();
	}
	deathToAll.clear();

	if (anim.isFinished())
	{
		destroy();
	}
	anim.advanceFrame();
	transform().setPosition(getPos());
	anim.setPosition(getPos());
}

} // fathom
