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


	/**
	 * @param amount amount to hurt
	 * @return True if the Diver dies, False if he's still alive
	 */
	bool damage(int amount);

	const sf::Color& getColor() const;

	enum class State
	{
		Swimming,
		Firing,
		Dead
	};
	State getState() const;

private:
	void draw(sf::RenderTarget& target, const sf::RenderStates &states) const override;

	void onUpdate() override;



	State state;
	const int playerID;
	int cooldown;
	je::Controller controls;
	je::AxesSet movement;
	je::Animation swim;
	je::Animation shoot;
	sf::Sprite deadSprite;
	sf::Vector2f veloc;
	int maxhp;
	int hp;
	sf::Text hpText;
	sf::Font hpFont;
};

} // fathom

#endif // FATHOM_DIVER_HPP
