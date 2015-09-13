#ifndef FATHOM_EXPLOSION_HPP
#define FATHOM_EXPLOSION_HPP

#include "jam-engine/Core/Entity.hpp"
#include "jam-engine/Graphics/Animation.hpp"

namespace fathom
{

class Explosion : public je::Entity
{
public:
	Explosion(je::Level *level, const sf::Vector2f& pos);

private:
	void draw(sf::RenderTarget& target, const sf::RenderStates &states) const override;

	void onUpdate() override;


	int maskIndex;
	je::Animation anim;
};

} // fathom

#endif // FATHOM_EXPLOSION_HPP
