#ifndef FATHOM_BLOOD_HPP
#define FATHOM_BLOOD_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "jam-engine/Core/Entity.hpp"

namespace fathom
{

class Blood : public je::Entity
{
public:
	Blood(je::Level *level, const sf::Vector2f& pos, const sf::Vector2f& veloc);


private:
	void draw(sf::RenderTarget& target, const sf::RenderStates &states) const override;

	void onUpdate() override;


	sf::Sprite sprite;
	sf::Vector2f veloc;
	int cooldown;
};

} // fathom

#endif // FATHOM_BLOOD_HPP
