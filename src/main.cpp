#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"

#include "Diver.hpp"

int main()
{
	je::Game game(640, 480, 30);
	je::Level *level = new je::Level(&game, 640, 480);
	game.setLevel(level);
	level->addEntity(new fathom::Diver(level, sf::Vector2f(320, 240), 0));
	return game.execute();
}
