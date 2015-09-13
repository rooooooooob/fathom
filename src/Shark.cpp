#include "Shark.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Utility/Trig.hpp"
#include "jam-engine/Utility/Random.hpp"

#include "Diver.hpp"
#include "Blood.hpp"

namespace fathom
{

const int minPatrolSpeed = 1.f;
const float maxPatrolSpeed = 2.f;

Shark::Shark(je::Level *level, const sf::Vector2f& pos)
	:je::Entity(level, "Shark", pos, sf::Vector2i(48, 24), sf::Vector2i(-24, -12))
	,attackAnim(level->getGame().getTexManager().get("shark_bite.png"), 48, 24, 4, true)
	,target(nullptr)
	,hp(30)
{
	attackAnim.setOrigin(24, 12);

	veloc.x = je::choose({je::randomf(1.f), -je::randomf(1.f)});
}


bool Shark::damage(int amount)
{
	for (int i = 0; i < amount; ++i)
	{
		level->addEntity(new Blood(level, getPos(), je::lengthdir(je::randomf(0.8f), je::random(180))));
	}

	if (hp <= amount)
	{
		destroy();
		return true;
	}
	hp -= amount;
	return false;
}

// private
void Shark::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
	target.draw(attackAnim, states);
}

void Shark::onUpdate()
{
	if (level->testCollision(this, "Explosion"))
	{
		damage(1);
	}

	if (target)
	{
		const int dist = je::pointDistance(getPos(), target->getPos());
		if (dist < 32)
		{
			attackAnim.advanceFrame();
			if (dist < 16)
			{
				if (target->damage(1))
				{
					patrolRandomDirection();
				}
			}
		}
		else if (dist < 1920)
		{
			veloc += je::lengthdir(0.5, je::pointDirection(getPos(), target->getPos()));
		}
		else
		{
			patrolRandomDirection();
		}

		if (je::length(veloc) > 6.f)
		{
			veloc = je::lengthdir(6.f, je::direction(veloc));
		}
		veloc *= 0.95f;
	}
	else
	{
		std::vector<Entity*> closeDivers;
		const sf::Rect<int> region(getPos().x - 192 + attackAnim.getScale().x * 64, getPos().y - 128, 192*2, 128*2);
		level->findCollisions(closeDivers, region, "Diver");
		for (Entity *diver : closeDivers)
		{
			if (!target || je::pointDistance(getPos(), diver->getPos()) < je::pointDistance(getPos(), target->getPos()))
			{
				target = static_cast<Diver*>(diver);
			}
		}

		if (!target)
		{
			if (veloc.x > 0.f)
			{
				if (getPos().x > level->getWidth() - 64 || level->testCollision(this, "Mine", 32))
				{
					veloc.x = -getPatrolSpeed();
				}
			}
			else
			{
				if (getPos().x < 64 || level->testCollision(this, "Mine", -32))
				{
					veloc.x = getPatrolSpeed();
				}
			}
		}
	}
	attackAnim.setScale(veloc.x < 0.f ? -1.f : 1.f, 1.f);
	transform().move(veloc);
	attackAnim.setPosition(getPos());
}

void Shark::patrolRandomDirection()
{
	target = nullptr;
	veloc.x = je::choose({getPatrolSpeed(), -getPatrolSpeed()});
}

float Shark::getPatrolSpeed() const
{
	return minPatrolSpeed + je::randomf(maxPatrolSpeed - minPatrolSpeed);
}

} // fathom
