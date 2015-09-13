#ifndef FATHOM_COIN_HPP
#define FATHOM_COIN_HPP

#include "jam-engine/Core/Entity.hpp"
#include "jam-engine/Graphics/Animation.hpp"

namespace fathom
{

class Coin : public je::Entity
{
public:
	Coin(je::Level *level, const sf::Vector2f& pos);


private:
	void draw(sf::RenderTarget& target, const sf::RenderStates &states) const override;

	void onUpdate() override;


	je::Animation spin;
	int cooldown;
	sf::Vector2f veloc;
};

} // fathom

#endif // FATHOM_COIN_HPP
