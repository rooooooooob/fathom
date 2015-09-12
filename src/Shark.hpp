#ifndef FATHOM_SHARK_HPP
#define FATHOM_SHARK_HPP

#include "jam-engine/Core/Entity.hpp"
#include "jam-engine/Graphics/Animation.hpp"

namespace fathom
{

class Diver;

class Shark : public je::Entity
{
public:
	Shark(je::Level *level, const sf::Vector2f& pos);

private:
	void draw(sf::RenderTarget& target, const sf::RenderStates &states) const override;

	void onUpdate() override;

	je::Animation attackAnim;
	sf::Vector2f veloc;
	Diver *target;
};

} // fathom

#endif // FATHOM_SHARK_HPP
