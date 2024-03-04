
#pragma once

#include <SFML/Graphics.hpp>
#include "../utils/BitFlags.hpp"

namespace audio {

enum class Menu { select, shift, forward_switch, backward_switch };
enum class Player { jump, step, land, arms_switch, shoot, hurt, dash };
enum class Weapon { bryns_gun, plasmer, nova, clover, tomahawk, tomahawk_catch };

//critters
enum class Frdog {hurt};
enum class Hulmet {hurt};

struct Soundboard {

	util::BitFlags<Menu> menu{};
	util::BitFlags<Player> player{};
	util::BitFlags<Weapon> weapon{};

	util::BitFlags<Frdog> frdog{};
	util::BitFlags<Hulmet> hulmet{};

	void play_sounds();
};

} // namespace audio
