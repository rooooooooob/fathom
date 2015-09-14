#ifndef FATHOM_HEALTHPICKUP_HPP
#define FATHOM_HEALTHPICKUP_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "jam-engine/Core/Entity.hpp"

namespace fathom
{

class HealthPickup : public je::Entity
{
public:
	enum class Type
	{
		Regular,
		Golden
	};
	HealthPickup(je::Level * level, const sf::Vector2f& pos, Type type);


	Type getType() const;

private:
	void draw(sf::RenderTarget& target, const sf::RenderStates &states) const override;

	void onUpdate() override;


	sf::Sprite sprite;
	Type type;
};

} // fathom

#endif // FATHOM_HEALTHPICKUP_HPP
