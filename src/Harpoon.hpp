#ifndef FATHOM_HARPOON_HPP
#define FATHOM_HARPOON_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "jam-engine/Core/Entity.hpp"

namespace fathom
{

class Harpoon : public je::Entity
{
public:
	Harpoon(je::Level *level, const sf::Vector2f& pos, const sf::Vector2f& veloc);


private:
	void draw(sf::RenderTarget& target, const sf::RenderStates &states) const override;

	void onUpdate() override;


	sf::Sprite sprite;
	sf::Vector2f veloc;
};

} // fathom

#endif // FATHOM_HARPOON_HPP
