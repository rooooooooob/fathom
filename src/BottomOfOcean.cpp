#include "BottomOfOcean.hpp"

#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Core/Game.hpp"

namespace fathom
{

BottomOfOcean::BottomOfOcean(je::Level *level, const sf::Vector2f& pos)
	:je::Entity(level, "BottomOfOcean", pos, sf::Vector2i(64, 64))
	,sprite(level->getGame().getTexManager().get("bottom_of_ocean.png"))
{
	sprite.setPosition(pos);
}

//private
void BottomOfOcean::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
	target.draw(sprite, states);
}

void BottomOfOcean::onUpdate()
{
}

} // fathom
