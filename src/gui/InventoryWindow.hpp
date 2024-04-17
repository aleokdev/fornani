
#pragma once
#include "Console.hpp"
#include "Selector.hpp"

namespace player {
class Player;
}

namespace gui {

class InventoryWindow : public Console {
  public:
	InventoryWindow() = default;
	InventoryWindow(automa::ServiceProvider& svc);
	void update(automa::ServiceProvider& svc, player::Player& player);
	void render(automa::ServiceProvider& svc, player::Player& player, sf::RenderWindow& win);
	void open();
	void close();

	Selector selector;

  private:
	struct {
		float corner_pad{120.f};
		float inner_corner{16.f};
		int title_size{16};
		int desc_size{16};
		int items_per_row{12};
		sf::Vector2<float> title_offset{(float)corner_factor, 16.f};
		sf::Vector2<float> item_label_offset{(float)corner_factor, 230.f};
		sf::Vector2<float> item_description_offset{(float)corner_factor, 290.f};
		sf::Vector2<float> info_offset{inner_corner, 260.f};
	} ui{};

	sf::Text title{};
	sf::Font title_font{};

	sf::Text item_label{};
	sf::Font item_font{};

	Console info;
};

} // namespace gui
