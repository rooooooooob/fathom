#include "Coin.hpp"

#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Utility/Random.hpp"
#include "jam-engine/Utility/Trig.hpp"

namespace fathom
{

Coin::Coin(je::Level *level, const sf::Vector2f& pos)
	:je::Entity(level, "Coin", pos, sf::Vector2i(4, 6))
	,spin(level->getGame().getTexManager().get("coin_spin.png"), 4, 6, 3 + je::random(2))
	,cooldown(16 + je::random(24))
	,veloc(je::lengthdir(0.4f + je::randomf(1.4f), je::randomf(60.f) + 60.f))
{
}


//private
void Coin::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
	target.draw(spin, states);
}

void Coin::onUpdate()
{
	veloc.y += 0.085f;
	transform().move(veloc);
	if (--cooldown == 0)
	{
		destroy();
	}
	spin.setPosition(getPos());
}

} // fathom
