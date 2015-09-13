#ifndef FATHOM_OCEAN_HPP
#define FATHOM_OCEAN_HPP

#include "jam-engine/Core/Level.hpp"

namespace fathom
{

class Ocean : public je::Level
{
public:
	Ocean(je::Game *game);

private:
	void onUpdate() override;

	void beforeDraw(sf::RenderTarget& target) const override;

	sf::Vertex ocean[5];

	je::Camera *camera;
};

} // fathom

#endif // FATHOM_OCEAN_HPP
