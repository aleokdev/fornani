
#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include "../utils/BitFlags.hpp"
#include "../utils/Camera.hpp"
#include "../graphics/TextWriter.hpp"

namespace gui {

int const corner_factor{22};
int const edge_factor{4};
float const height_factor{4.0f};

float const pad{32.0f};
float const text_pad{8.0f};
inline const sf::Vector2<float> origin{pad, cam::screen_dimensions.y - pad}; // bottom left corner

enum class ConsoleFlags { active, finished, loaded };

struct Border {
	float left{};
	float right{};
	float top{};
	float bottom{};
};

class Console {

  public:
	Console();

	void begin();
	void update();
	void render(sf::RenderWindow& win);

	void load_and_launch(std::string_view key);
	void write(sf::RenderWindow& win, bool instant = true);
	void end();

	void nine_slice(int corner_dim, int edge_dim);

	sf::Vector2<float> position{};
	sf::Vector2<float> dimensions{};
	sf::Vector2<float> text_origin{};
	util::BitFlags<ConsoleFlags> flags{};

	std::array<sf::Sprite, 9> sprites{};

	text::TextWriter writer{};
	Border border{
		28.f,
		20.f,
		16.f,
		16.f
	};

	int extent{};
	int speed{8};
};

} // namespace gui