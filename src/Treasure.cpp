#include "Treasure.hpp"

#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Core/Game.hpp"

#include "Ocean.hpp"

namespace fathom
{

Treasure::Treasure(Ocean *ocean, const sf::Vector2f& pos)
	:je::Entity(ocean, "Treasure", pos, sf::Vector2i(16, 16))
	,animation(ocean->getGame().getTexManager().get("treasure_chest.png"), 16, 16, 8, false)
	,cooldown(-1)
	,ocean(ocean)
{
	animation.setPosition(pos);
}


//private
void Treasure::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
	target.draw(animation, states);
}

void Treasure::onUpdate()
{
	if (cooldown >= 0)
	{
		if (--cooldown == 0)
		{
			destroy();
		}
		animation.advanceFrame();
	}
	else if (level->testCollision(this, "Diver"))
	{
		cooldown = 32;
		ocean->addScore(250);
	}
}

} // fathom
