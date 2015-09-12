#include "Shark.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Utility/Trig.hpp"

#include "Diver.hpp"

namespace fathom
{

Shark::Shark(je::Level *level, const sf::Vector2f& pos)
	:je::Entity(level, "Shark", pos, sf::Vector2i(48, 24), sf::Vector2i(-24, -12))
	,attackAnim(level->getGame().getTexManager().get("shark_bite.png"), 48, 24, 4, true)
	,target(nullptr)
{
	attackAnim.setOrigin(24, 12);
}


void Shark::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
	target.draw(attackAnim, states);
}

void Shark::onUpdate()
{
	if (target)
	{
		const int dist = je::pointDistance(getPos(), target->getPos());
		if (dist < 32)
		{
			attackAnim.advanceFrame();
			if (dist < 16)
			{
				// hurt player
			}
		}
		else if (dist < 1920)
		{
			veloc += je::lengthdir(0.5, je::pointDirection(getPos(), target->getPos()));
		}
		else
		{
			target = nullptr;
			veloc = sf::Vector2f(0.f, 0.f);
		}
	}
	else
	{
		std::vector<Entity*> closeDivers;
		const sf::Rect<int> region(getPos().x - 192, getPos().x - 128, 192*2, 128*2);
		level->findCollisions(closeDivers, region, "Diver");
		for (Entity *diver : closeDivers)
		{
			if (!target || je::pointDistance(getPos(), diver->getPos()) < je::pointDistance(getPos(), target->getPos()))
			{
				target = static_cast<Diver*>(diver);
			}
		}
	}

	if (je::length(veloc) > 6.f)
	{
		veloc = je::lengthdir(6.f, je::direction(veloc));
	}
	veloc *= 0.95f;
	attackAnim.setScale(veloc.x < 0.f ? -1.f : 1.f, 1.f);
	transform().move(veloc);
	attackAnim.setPosition(getPos());
}

} // fathom
