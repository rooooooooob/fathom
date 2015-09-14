#include "jam-engine/Core/Game.hpp"

#include "Ocean.hpp"

int main()
{
	const int width = 640;
	const int height = 480;
	je::Game game(width, height, 30);
	game.setLevel(new fathom::Ocean(&game, 6400));
	return game.execute();
}
