
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../utils/BitFlags.hpp"

namespace automa {
struct ServiceProvider;
}

namespace audio {

enum class Menu { select, shift, forward_switch, backward_switch };
enum class Console { next, done, shift, select, speech, menu_open };
enum class World { load, save, soft_sparkle, soft_sparkle_high };
enum class Player { jump, step, land, arms_switch, shoot, hurt, dash };
enum class Weapon { bryns_gun, plasmer, nova, clover, tomahawk, tomahawk_catch, hook_probe };

//critters
enum class Frdog {hurt};
enum class Hulmet {hurt};

struct Soundboard {

	util::BitFlags<Menu> menu{};
	util::BitFlags<Console> console{};
	util::BitFlags<World> world{};
	util::BitFlags<Player> player{};
	util::BitFlags<Weapon> weapon{};

	util::BitFlags<Frdog> frdog{};
	util::BitFlags<Hulmet> hulmet{};

	void play_sounds(automa::ServiceProvider& svc);
	void repeat(sf::Sound& sound, int frequency, float random_pitch_offset = 0.f);
	void randomize(sf::Sound& sound, float random_pitch_offset);

	struct {
		float save{};
	} proximities{};
};

} // namespace audio
