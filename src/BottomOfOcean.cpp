#include "BottomOfOcean.hpp"

#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Utility/Random.hpp"

namespace fathom
{

float wigglePeriod = 256.f;

BottomOfOcean::BottomOfOcean(je::Level *level, const sf::Vector2f& pos)
	:je::Entity(level, "BottomOfOcean", pos, sf::Vector2i(64, 64))
	,sprite(level->getGame().getTexManager().get("bottom_of_ocean.png"))
	,seaweed(level->getGame().getTexManager().get("seaweed.png"))
	,wiggle(je::randomf(wigglePeriod))
{
	sprite.setPosition(pos);
	seaweed.setPosition(16 + je::random(level->getWidth() - 16), pos.y);
	seaweed.setOrigin(16, 120);
}

//private
void BottomOfOcean::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
	target.draw(sprite, states);
	target.draw(seaweed, states);
}

void BottomOfOcean::onUpdate()
{
	seaweed.setRotation(20.f * sin(wiggle / ++wigglePeriod));
}

} // fathom
