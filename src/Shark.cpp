#include "Shark.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Utility/Trig.hpp"
#include "jam-engine/Utility/Random.hpp"

#include "Diver.hpp"
#include "Blood.hpp"
#include "Ocean.hpp"

namespace fathom
{

const int minPatrolSpeed = 1.f;
const float maxPatrolSpeed = 2.f;

Shark::Shark(Ocean *ocean, const sf::Vector2f& pos)
	:je::Entity(ocean, "Shark", pos, sf::Vector2i(48, 24), sf::Vector2i(-24, -12))
	,attackAnim(ocean->getGame().getTexManager().get("shark_bite.png"), 48, 24, 4, true)
	,target()
	,hp(30)
	,ocean(ocean)
	,hackyCooldown(128) // to stop sharks from dying immediately to mines
{
	attackAnim.setOrigin(24, 12);

	veloc.x = je::choose({je::randomf(1.f), -je::randomf(1.f)});

	// delete mines around shark so they don't immediately die... (couldn't fix in Ocean)
	std::vector<je::Ref<je::Entity>> mines;
	ocean->findCollisions(mines, sf::Rect<int>(getPos().x - 64, getPos().y - 48, 128, 96), "Mine");
	for (const je::Ref<Entity>& mine : mines)
	{
		mine->destroy();
	}
}


bool Shark::damage(int amount, const sf::Vector2f& bloodVeloc)
{
	if (hp > 0)
	{
		for (int i = 0; i < amount; ++i)
		{
			level->addEntity(new Blood(level, getPos(), bloodVeloc + je::lengthdir(je::randomf(0.8f), je::random(180))));
		}
		veloc += bloodVeloc;
		if (hp <= amount)
		{
			ocean->addScore(100);
			hp = 0;
			return true;
		}
		hp -= amount;
	}
	return false;
}

// private
void Shark::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
	target.draw(attackAnim, states);
}

void Shark::onUpdate()
{
	if (hp <= 0)
	{
		if (--hp < -64)
		{
			destroy();
		}
		if (hp < -16)
		{
			veloc.y = -1.f - je::randomf(0.55f);
		}
		transform().move(veloc);
		level->addEntity(new Blood(level, getPos(), sf::Vector2f(-0.25f + je::randomf(0.5f), 0.f)));
		attackAnim.setScale(attackAnim.getScale().x, -1.f);
	}
	else // alive
	{
		if (hackyCooldown > 0)
		{
			--hackyCooldown;
		}
		if (hackyCooldown == 0)
		{
			auto expl = level->testCollision(this, "Explosion");
			if (expl)
			{
				damage(1, je::lengthdir(6.f, je::pointDistance(expl->getPos(), getPos())));
			}
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
			std::vector<je::Ref<Entity>> closeDivers;
			const sf::Rect<int> region(getPos().x - 192 + attackAnim.getScale().x * 64, getPos().y - 128, 192*2, 128*2);
			level->findCollisions(closeDivers, region, "Diver",
				[](je::Entity&e) -> bool
				{
					return ((Diver&)e).getState() != Diver::State::Dead;
				}
			);
			for (je::Ref<Entity>& diver : closeDivers)
			{
				if (!target || je::pointDistance(getPos(), diver->getPos()) < je::pointDistance(getPos(), target->getPos()))
				{
					target = diver;
				}
			}

			if (!target)
			{
				if (veloc.x > 0.f)
				{
					if (getPos().x > level->getWidth() - 64 || level->testCollision(sf::Rect<int>(getPos().x, getPos().y - 27, 64, 56), "Mine"))
					{
						veloc.x = -getPatrolSpeed();
					}
				}
				else
				{
					if (getPos().x < 64 || level->testCollision(sf::Rect<int>(getPos().x - 64, getPos().y - 27, 64, 56), "Mine"))
					{
						veloc.x = getPatrolSpeed();
					}
				}
			}
		}
		attackAnim.setScale(veloc.x < 0.f ? -1.f : 1.f, 1.f);
		transform().move(veloc);
		if (getPos().x > level->getWidth() - 24)
		{
			transform().setPosition(level->getWidth() - 24, getPos().y);
		}
		if (getPos().x < 24)
		{
			transform().setPosition(24, getPos().y);
		}
		if (getPos().y > level->getHeight() - 64 - 8)
		{
			transform().setPosition(getPos().x, level->getHeight() - 64 - 8);
		}
		if (getPos().x < 24)
		{
			transform().setPosition(getPos().x, 24);
		}
	}

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
