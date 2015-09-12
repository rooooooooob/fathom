#include "Mine.hpp"

#include <cmath>

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"

namespace fathom
{

Mine::Mine(je::Level *level, const sf::Vector2f& pos)
	:je::Entity(level, "Mine", pos, sf::Vector2i(16, 16), sf::Vector2i(-8, -8))
	,startY(pos.y)
	,anim(level->getGame().getTexManager().get("mine.png"), 16, 16, 64, true)
{
	anim.setOrigin(8, 8);
}


void Mine::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
	target.draw(anim, states);
}

void Mine::onUpdate()
{
	anim.advanceFrame();
	transform().setPosition(getPos().x, startY + 16 * sin(++wiggle / 100.f));
	anim.setPosition(getPos());
}

} // fathom
