#pragma once

#include <SFML/Graphics.hpp>

namespace automa {
struct ServiceProvider;
}

namespace entity {

class Entity {
  public:
	Entity(automa::ServiceProvider& svc){};
	virtual void update(automa::ServiceProvider& svc){};
	virtual void render(automa::ServiceProvider& svc, sf::RenderWindow& win, sf::Vector2<float> cam){};

  protected:
	sf::Vector2<float> sprite_offset{};
	sf::Vector2<float> dimensions{};
	sf::Vector2<float> sprite_dimensions{};
	sf::Vector2<float> spritesheet_dimensions{};
	sf::Sprite sprite{};
	sf::RectangleShape drawbox{}; // for debug
};

} // namespace entity