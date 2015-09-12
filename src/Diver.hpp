#ifndef FATHOM_DIVER_HPP
#define FATHOM_DIVER_HPP

#include "jam-engine/Core/Entity.hpp"
#include "jam-engine/Core/Controller.hpp"
#include "jam-engine/Graphics/Animation.hpp"

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
	int cooldown;
	je::Controller controls;
	je::AxesSet movement;
	je::Animation swim;
	sf::Vector2f veloc;
};

} // fathom

#endif // FATHOM_DIVER_HPP
