#include "Diver.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"

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
	:je::Entity(level, "Diver", pos, sf::Vector2i(16, 32))
	,playerID(playerID)
	,cooldown(-1)
	,controls(level->getGame().getInput(), playerID)
{
	sprite.setTexture(level->getGame().getTexManager().get("boat.png"));

	assert(playerID < maxPlayers);

	controls.setAxis("move_x_gp", je::Controller::AxisBind(sf::Joystick::Axis::PovX));
	controls.setAxis("move_y_gp", je::Controller::AxisBind(sf::Joystick::Axis::PovX));
	controls.setAxis("move_x_kb", je::Controller::AxisBind(je::Controller::Bind(leftKeys[playerID]), je::Controller::Bind(rightKeys[playerID])));
	controls.setAxis("move_y_kb", je::Controller::AxisBind(je::Controller::Bind(upKeys[playerID]), je::Controller::Bind(downKeys[playerID])));
	movement = je::AxesSet({
		je::Axes(controls, "move_x_gp", "move_y_gp"),
		je::Axes(controls, "move_x_kb", "move_y_kb")
	});
}


void Diver::draw(sf::RenderTarget& target, const sf::RenderStates &states) const
{
	target.draw(sprite, states);
}

void Diver::onUpdate()
{
}

} // fathom
