#ifndef FATHOM_MINE_HPP
#define FATHOM_MINE_HPP

#include "jam-engine/Core/Entity.hpp"
#include "jam-engine/Graphics/Animation.hpp"

namespace fathom
{

class Mine : public je::Entity
{
public:
	Mine(je::Level *level, const sf::Vector2f& pos);

private:
	void draw(sf::RenderTarget& target, const sf::RenderStates &states) const override;

	void onUpdate() override;


	int wiggle;
	float startY;
	je::Animation anim;
};

} // fathom

#endif // FATHOM_MINE_HPP
