#ifndef FATHOM_BOTTOMOFOCEAN_HPP
#define FATHOM_BOTTOMOFOCEAN_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "jam-engine/Core/Entity.hpp"

namespace fathom
{

class BottomOfOcean : public je::Entity
{
public:
	BottomOfOcean(je::Level *level, const sf::Vector2f& pos);


private:
	void draw(sf::RenderTarget& target, const sf::RenderStates &states) const override;

	void onUpdate() override;


	sf::Sprite sprite;
	sf::Sprite seaweed;
	int wiggle;
};

} // fathom

#endif // FATHOM_BOTTOMOFOCEAN_HPP
