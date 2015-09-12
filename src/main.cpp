#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-Engine/Utility/Random.hpp"

#include "Diver.hpp"
#include "Shark.hpp"
#include "Mine.hpp"

int main()
{
	const int width = 640;
	const int height = 480;
	je::Game game(width, height, 30);
	je::Level *level = new je::Level(&game, width, height);
	game.setLevel(level);
	for (int i = 0; i < 1; ++i)
		level->addEntity(new fathom::Diver(level, sf::Vector2f(je::randomf(width), je::randomf(height)), i));
	level->addEntity(new fathom::Shark(level, sf::Vector2f(je::randomf(width), je::randomf(height))));
	for (int i = 0; i < 32; ++i)
		level->addEntity(new fathom::Mine(level, sf::Vector2f(je::randomf(width), je::randomf(height))));
	return game.execute();
}
