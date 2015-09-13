#include "Diver.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Utility/Trig.hpp"

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

Diver::Diver(je::Level *level, const sf::Vector2f& pos, int playerID)
	:je::Entity(level, "Diver", pos, sf::Vector2i(16, 32), sf::Vector2i(-8, -16))
	,playerID(playerID)
	,cooldown(-1)
	,controls(level->getGame().getInput(), playerID)
	,swim(level->getGame().getTexManager().get("diver_swim.png"), 32, 32, 10, true)
{

	assert(playerID < maxPlayers);

	//controls.setAxis("move_x_gp", je::Controller::AxisBind(sf::Joystick::Axis::PovX));
	//controls.setAxis("move_y_gp", je::Controller::AxisBind(sf::Joystick::Axis::PovX));
	controls.setAxis("move_x_kb", je::Controller::AxisBind(je::Controller::Bind(leftKeys[playerID]), je::Controller::Bind(rightKeys[playerID])));
	controls.setAxis("move_y_kb", je::Controller::AxisBind(je::Controller::Bind(upKeys[playerID]), je::Controller::Bind(downKeys[playerID])));
	const je::Axes gpAxes(controls, "move_x_gp", "move_y_gp");
	const je::Axes kbAxes(controls, "move_x_kb", "move_y_kb");
	movement = je::AxesSet({kbAxes, gpAxes});


	swim.setOrigin(16.f, 16.f);
}


void Diver::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
	target.draw(swim, states);
}

void Diver::onUpdate()
{
	const float SWIM_SPEED = 4.f;
	const sf::Vector2f mPos(movement.getPos());
	if (je::length(mPos) > 0.2)
	{
		swim.advanceFrame();
		veloc += mPos * 1.f;
		swim.setScale(mPos.x < 0.f ? -1.f : 1.f, 1.f);
	}

	if (je::length(veloc) > SWIM_SPEED)
	{
		veloc = je::lengthdir(SWIM_SPEED, je::direction(veloc));
	}

	veloc = 0.9f * veloc;

	transform().move(veloc);

	swim.setPosition(getPos());
}

} // fathom
