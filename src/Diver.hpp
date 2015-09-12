#ifndef FATHOM_DIVER_HPP
#define FATHOM_DIVER_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "jam-engine/Core/Entity.hpp"
#include "jam-engine/Core/Controller.hpp"

namespace fathom
{

class Diver : public je::Entity
{
public:
	Diver(je::Level *level, const sf::Vector2f& pos, int playerID);



private:
	void draw(sf::RenderTarget& target, const sf::RenderStates &states) const override;

	void onUpdate() override;


	enum class State
	{
		Swimming,
		Firing
	};

	const int playerID;
	sf::Sprite sprite;
	int cooldown;
	je::Controller controls;
	je::AxesSet movement;
};

} // fathom

#endif // FATHOM_DIVER_HPP
