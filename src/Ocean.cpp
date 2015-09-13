#include "Ocean.hpp"

#include <sstream>

#include "jam-engine/Core/Camera.hpp"
#include "jam-engine/Core/Game.hpp"
#include "jam-Engine/Utility/Random.hpp"
#include "jam-engine/Utility/Trig.hpp"

#include "Diver.hpp"
#include "Shark.hpp"
#include "Mine.hpp"
#include "Treasure.hpp"

namespace fathom
{

Ocean::Ocean(je::Game *game)
	:je::Level(game, 900, 9999)
	,arrow(game->getTexManager().get("arrow.png"))
	,playerCount(1)
	,highscore(0)
	,score(0)
{
	const sf::Color top(60, 130, 170);
	const sf::Color bottom = sf::Color::Black;
	ocean[0] = ocean[4] = sf::Vertex(sf::Vector2f(0.f, 0.f), top);
	ocean[1] = sf::Vertex(sf::Vector2f(getWidth(), 0.f), top);
	ocean[2] = sf::Vertex(sf::Vector2f(getWidth(), getHeight()), bottom);
	ocean[3] = sf::Vertex(sf::Vector2f(0.f, getHeight()), bottom);


	camera = new je::Camera(this, 16.f, 1.f, sf::Rect<int>(0, 0, 640, 480));
	camera->snap(sf::Vector2f(getWidth() / 2, 999));

	arrow.setOrigin(16.f, 16.f);

	reset();

	// really bad but not much time to do anything better (maybe put something into jam-engine for next time?)
	font.loadFromFile("arial.ttf");

	scoreText.setColor(sf::Color(192, 255, 255));
	scoreText.setFont(font);
	scoreText.setCharacterSize(16);
	scoreText.setPosition(16, 16);
}


void Ocean::addScore(int amount)
{
	score += amount;
	highscore = std::max(score, highscore);
}


// private
void Ocean::onUpdate()
{
	if (getGame().getInput().isKeyPressed(sf::Keyboard::Key::Num1))
	{
		playerCount = 1;
	}
	if (getGame().getInput().isKeyPressed(sf::Keyboard::Key::Num2))
	{
		playerCount = 2;
	}
	if (getGame().getInput().isKeyPressed(sf::Keyboard::Key::Num3))
	{
		playerCount = 3;
	}
	if (getGame().getInput().isKeyPressed(sf::Keyboard::Key::R))
	{
		reset();
	}

	if (entities.at("Diver").empty())
		reset();

	sf::Vector2f avgPos;
	for (const je::Entity *diver : entities.at("Diver"))
	{
		avgPos += diver->getPos();
	}
	avgPos *= (1.f / entities.at("Diver").size());
	camera->update(avgPos + sf::Vector2f(0.f, 96.f));

	std::stringstream ss;
	ss << "Score: \t" << score << "\nHighscore: " << highscore;
	scoreText.setString(ss.str());
}

void Ocean::beforeDraw(sf::RenderTarget& target) const
{
	target.draw(ocean, 5, sf::PrimitiveType::Quads);
}

void Ocean::drawGUI(sf::RenderTarget& target) const
{
	for (const je::Entity *entity : entities.at("Diver"))
	{
		const Diver& diver = *((Diver*)entity);
		if (!camera->getScreenRect().contains(diver.getPos()))
		{
			sf::Color col(diver.getColor());
			col.a = 128;
			arrow.setColor(col);
			const float angle = je::pointDirection(camera->getPosition(), diver.getPos());
			sf::Vector2f offset = je::lengthdir(1.f, angle);
			offset.x *= 300;
			offset.y *= 220;
			arrow.setPosition(camera->getPosition() + offset);
			arrow.setRotation(-angle);
			target.draw(arrow);
		}
	}

	target.draw(scoreText);
}


void Ocean::reset()
{
	clearEntities();

	const int safeDepth = 480;

	for (int i = 0; i < playerCount; ++i)
	{
		addEntity(new Diver(this, sf::Vector2f(je::randomf(getWidth()), je::randomf(safeDepth)), i));
	}

	for (int i = 0; i < 16; ++i)
	{
		addEntity(new Shark(this, sf::Vector2f(je::randomf(getWidth()), je::randomf(getHeight() - safeDepth * 2) + safeDepth * 2)));
	}

	for (int i = 0; i < 320; ++i)
	{
		int mx, my;
		do
		{
			mx = je::randomf(getWidth());
			my = je::randomf(getHeight() - safeDepth * 1.3f) + safeDepth * 1.3f;
		}
		while (testCollision(sf::Rect<int>(mx - 128, my - 128, 256, 256), "Shark"));
		addEntity(new Mine(this, sf::Vector2f(mx, my)));
	}

	for (int i = 0; i < 32; ++i)
	{
		const int ty = getHeight() - je::random(getHeight() / 2 + je::random(getHeight() / 2));
		addEntity(new Treasure(this, sf::Vector2f(je::random(getWidth()), ty)));
	}

	camera->snap(sf::Vector2f(getWidth() / 2, 999));

	score = 0;
}

} // fathom
