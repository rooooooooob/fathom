#ifndef FATHOM_OCEAN_HPP
#define FATHOM_OCEAN_HPP

#include "jam-engine/Core/Level.hpp"

namespace fathom
{

class Ocean : public je::Level
{
public:
	Ocean(je::Game *game);



	void addScore(int amount);

private:

	void onUpdate() override;

	void beforeDraw(sf::RenderTarget& target) const override;

	void drawGUI(sf::RenderTarget& target) const override;

	void reset();



	sf::Vertex ocean[5];

	je::Camera *camera;
	mutable sf::Sprite arrow;
	int playerCount;
	int highscore;
	int score;
	sf::Font font;
	sf::Text scoreText;
};

} // fathom

#endif // FATHOM_OCEAN_HPP
