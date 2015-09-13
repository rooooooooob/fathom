#include "Ocean.hpp"

#include "jam-engine/Core/Camera.hpp"
#include "jam-Engine/Utility/Random.hpp"

#include "Diver.hpp"
#include "Shark.hpp"
#include "Mine.hpp"

namespace fathom
{

Ocean::Ocean(je::Game *game)
	:je::Level(game, 640, 9999)
{
	const sf::Color top(60, 130, 170);
	const sf::Color bottom = sf::Color::Black;
	ocean[0] = ocean[4] = sf::Vertex(sf::Vector2f(0.f, 0.f), top);
	ocean[1] = sf::Vertex(sf::Vector2f(getWidth(), 0.f), top);
	ocean[2] = sf::Vertex(sf::Vector2f(getWidth(), getHeight()), bottom);
	ocean[3] = sf::Vertex(sf::Vector2f(0.f, getHeight()), bottom);


	for (int i = 0; i < 3; ++i)
		addEntity(new Diver(this, sf::Vector2f(je::randomf(getWidth()), je::randomf(480)), i));

	for (int i = 0; i < 16; ++i)
		addEntity(new Shark(this, sf::Vector2f(je::randomf(getWidth()), je::randomf(getHeight()))));

	for (int i = 0; i < 256; ++i)
		addEntity(new Mine(this, sf::Vector2f(je::randomf(getWidth()), je::randomf(getHeight()))));

	camera = new je::Camera(this, 10, 0.5f, sf::Rect<int>(0, 0, 640, 480));
}


// private
void Ocean::onUpdate()
{
	sf::Vector2f avgPos;
	for (const je::Entity *diver : entities.at("Diver"))
	{
		avgPos += diver->getPos();
	}
	avgPos *= (1.f / entities.at("Diver").size());
	camera->update(avgPos);
}

void Ocean::beforeDraw(sf::RenderTarget& target) const
{
	target.draw(ocean, 5, sf::PrimitiveType::Quads);
}

} // fathom
