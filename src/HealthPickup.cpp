#include "HealthPickup.hpp"

#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Core/Game.hpp"

namespace fathom
{

HealthPickup::HealthPickup(je::Level *level, const sf::Vector2f& pos, Type type)
	:je::Entity(level, "HealthPickup", pos, sf::Vector2i(8, 8))
	,sprite(level->getGame().getTexManager().get(type == Type::Regular ? "health.png" : "golden_health.png"))
	,type(type)
{
	sprite.setPosition(pos);
}


HealthPickup::Type HealthPickup::getType() const
{
	return type;
}

//private
void HealthPickup::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
	target.draw(sprite, states);
}

void HealthPickup::onUpdate()
{
}

} // fathom
