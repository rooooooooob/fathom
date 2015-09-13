#include "Diver.hpp"

#include <sstream>

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/GamepadPredefs.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Utility/Trig.hpp"
#include "jam-engine/Utility/Random.hpp"

#include "Blood.hpp"
#include "Harpoon.hpp"

namespace fathom
{

const int maxPlayers = 3;

sf::Keyboard::Key leftKeys[maxPlayers] = {
	sf::Keyboard::Left,
	sf::Keyboard::A,
	sf::Keyboard::J
};

sf::Keyboard::Key rightKeys[maxPlayers] = {
	sf::Keyboard::Right,
	sf::Keyboard::D,
	sf::Keyboard::L
};

sf::Keyboard::Key upKeys[maxPlayers] = {
	sf::Keyboard::Up,
	sf::Keyboard::W,
	sf::Keyboard::I
};

sf::Keyboard::Key downKeys[maxPlayers] = {
	sf::Keyboard::Down,
	sf::Keyboard::S,
	sf::Keyboard::K
};

sf::Keyboard::Key fireKeys[maxPlayers] = {
	sf::Keyboard::RControl,
	sf::Keyboard::X,
	sf::Keyboard::N
};

const sf::Color playerColours[maxPlayers] = {
	sf::Color(255, 16, 16),
	sf::Color(16, 255, 16),
	sf::Color(255, 255, 16)
};

Diver::Diver(je::Level *level, const sf::Vector2f& pos, int playerID)
	:je::Entity(level, "Diver", pos, sf::Vector2i(16, 32), sf::Vector2i(-8, -16))
	,state(State::Swimming)
	,playerID(playerID)
	,cooldown(-1)
	,controls(level->getGame().getInput(), playerID)
	,swim(level->getGame().getTexManager().get("diver_swim.png"), 32, 32, 10, true)
	,shoot(level->getGame().getTexManager().get("diver_shoot.png"), 32, 32, 16, false)
	,maxhp(200)
	,hp(maxhp)
{

	assert(playerID < maxPlayers);

	controls.setAxis("move_x_gp", je::Controller::AxisBind(sf::Joystick::Axis::X));
	controls.setAxis("move_y_gp", je::Controller::AxisBind(sf::Joystick::Axis::Y));
	controls.setAxis("move_x_kb", je::Controller::AxisBind(je::Controller::Bind(leftKeys[playerID]), je::Controller::Bind(rightKeys[playerID])));
	controls.setAxis("move_y_kb", je::Controller::AxisBind(je::Controller::Bind(upKeys[playerID]), je::Controller::Bind(downKeys[playerID])));
	const je::Axes gpAxes(controls, "move_x_gp", "move_y_gp");
	const je::Axes kbAxes(controls, "move_x_kb", "move_y_kb");
	movement = je::AxesSet({kbAxes, gpAxes});

	controls.setKeybinds("fire", {
		je::Controller::Bind(fireKeys[playerID]),
		je::Binds::X360::X,
		je::Binds::X360::RT
	});

	//controls.addKeybind("fire", je::Controller::Bind(fireKeys[playerID]));



	swim.setOrigin(16.f, 16.f);
	shoot.setOrigin(16.f, 16.f);

	// really bad but not much time to do anything better (maybe put something into jam-engine for next time?)
	hpFont.loadFromFile("arial.ttf");

	hpText.setColor(playerColours[playerID]);
	hpText.setFont(hpFont);
	hpText.setCharacterSize(12);
}



bool Diver::damage(int amount)
{
	for (int i = 0; i < amount; ++i)
	{
		level->addEntity(new Blood(level, getPos(), je::lengthdir(je::randomf(2.f), je::random(180))));
	}

	if (hp < amount)
	{
		destroy();
		return true;
	}
	hp -= amount;
	return false;
}



// private
void Diver::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
	switch (state)
	{
	case State::Swimming:
		target.draw(swim, states);
		break;
	case State::Firing:
		target.draw(shoot, states);
		break;
	}
	target.draw(hpText, states);
}

void Diver::onUpdate()
{
	if (level->testCollision(this, "Explosion"))
	{
		damage(1);
	}


	switch (state)
	{
	case State::Swimming:
		{
			if (controls.isActionPressed("fire"))
			{
				state = State::Firing;
				cooldown = 64;
				shoot.setScale(swim.getScale());
				break;
			}
			const sf::Vector2f mPos(movement.getPos());
			if (je::length(mPos) > 0.2)
			{
				swim.advanceFrame();
				veloc += mPos * 1.f;
				swim.setScale(mPos.x < 0.f ? -1.f : 1.f, 1.f);
			}

			const float SWIM_SPEED = 4.f;
			if (je::length(veloc) > SWIM_SPEED)
			{
				veloc = je::lengthdir(SWIM_SPEED, je::direction(veloc));
			}
			veloc = 0.9f * veloc;
		}
		break;
	case State::Firing:
		{
			if (shoot.advanceFrame())
			{
				level->addEntity(new Harpoon(level, getPos() + sf::Vector2f(shoot.getScale().x * 16, 0.f), sf::Vector2f(shoot.getScale().x * 32, 0.f)));
				veloc.x = shoot.getScale().x * -12.f;
			}
			if (--cooldown == 0)
			{
				state = State::Swimming;
				shoot.reset();
				break;
			}
			veloc = 0.93f * veloc;
		}
		break;
	}


	transform().move(veloc);

	swim.setPosition(getPos());
	shoot.setPosition(getPos());

	hpText.setPosition(getPos().x - hpText.getLocalBounds().width / 2, getPos().y + 48);
	std::stringstream ss;
	ss << hp << " / " << maxhp;
	hpText.setString(ss.str());
}

} // fathom
