#pragma once

#include <SFML/Graphics.hpp>
#include "../utils/Direction.hpp"
#include "../utils/BitFlags.hpp"

namespace automa {
struct ServiceProvider;
}

namespace world {
class Map;
}

namespace entity {

enum class State { flip };

class Entity {
  public:
	Entity() = default;
	Entity(automa::ServiceProvider& svc){};
	virtual void update(automa::ServiceProvider& svc, world::Map& map);
	virtual void render(automa::ServiceProvider& svc, sf::RenderWindow& win, sf::Vector2<float> cam) = 0;
	void sprite_flip();
	[[nodiscard]] auto get_direction() const -> dir::Direction { return direction; }
	sf::RectangleShape drawbox{}; // for debug

  protected:
	sf::Vector2<float> dimensions{};
	sf::Vector2<float> sprite_offset{};
	sf::Vector2<int> sprite_dimensions{};
	sf::Vector2<int> spritesheet_dimensions{};
	sf::Sprite sprite{};
	dir::Direction direction{};
	util::BitFlags<State> ent_state{};
};

} // namespace entity