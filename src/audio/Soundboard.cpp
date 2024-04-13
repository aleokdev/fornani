
#pragma once

#include "Soundboard.hpp"
#include <algorithm>
#include "../service/ServiceProvider.hpp"

namespace audio {

void Soundboard::play_sounds(automa::ServiceProvider& svc) {

	// menu
	if (flags.menu.test(Menu::forward_switch)) { svc.assets.menu_next.play(); }
	if (flags.menu.test(Menu::backward_switch)) { svc.assets.menu_back.play(); }
	if (flags.menu.test(Menu::select)) { svc.assets.click.play(); }
	if (flags.menu.test(Menu::shift)) { svc.assets.menu_shift.play(); }

	// console
	if (flags.console.test(Console::select)) { svc.assets.click.play(); }
	if (flags.console.test(Console::done)) { svc.assets.menu_back.play(); }
	if (flags.console.test(Console::next)) { svc.assets.menu_next.play(); }
	if (flags.console.test(Console::shift)) { svc.assets.menu_shift.play(); }
	if (flags.console.test(Console::speech)) { repeat(svc, svc.assets.menu_shift, 16, 0.2f); }

	// world
	if (flags.world.test(World::load)) { svc.assets.load.play(); }
	if (flags.world.test(World::save)) { svc.assets.save.play(); }
	if (flags.world.test(World::soft_sparkle)) { svc.assets.soft_sparkle.play(); }
	if (flags.world.test(World::chest)) { svc.assets.chest.play(); }
	if (flags.world.test(World::breakable_shatter)) { svc.assets.shatter.play(); }

	//frdog
	if (flags.frdog.test(Frdog::death)) { svc.assets.enem_death_1.play(); }

	//item
	if (flags.item.test(Item::heal)) { svc.assets.heal.play(); }
	if (flags.item.test(Item::orb_1)) { svc.assets.orb_1.play(); }
	if (flags.item.test(Item::orb_5)) { svc.assets.orb_5.play(); }

	// player
	if (flags.player.test(Player::land)) { svc.assets.landed.play(); }
	if (flags.player.test(Player::jump)) { svc.assets.jump.play(); }
	if (flags.player.test(Player::step)) { randomize(svc, svc.assets.step, 0.1f); }
	if (flags.player.test(Player::arms_switch)) { svc.assets.arms_switch.play(); }
	if (flags.player.test(Player::hurt)) { svc.assets.hurt.play(); }
	if (flags.player.test(Player::death)) { svc.assets.player_death.play(); }

	// gun
	if (flags.weapon.test(Weapon::bryns_gun)) { svc.assets.bg_shot.play(); }
	if (flags.weapon.test(Weapon::plasmer)) { svc.assets.plasmer_shot.play(); }
	if (flags.weapon.test(Weapon::clover)) { repeat(svc, svc.assets.pop_mid, 2, 0.3f);
	}
	if (flags.weapon.test(Weapon::nova)) { svc.assets.pop_mid.play(); }
	if (flags.weapon.test(Weapon::tomahawk)) { repeat(svc, svc.assets.tomahawk_flight, 30, 0.4f);
	}
	if (flags.weapon.test(Weapon::tomahawk_catch)) { svc.assets.tomahawk_catch.play(); }
	if (flags.weapon.test(Weapon::hook_probe)) { svc.assets.sharp_click.play(); }

	// reset flags
	flags = {};

	// reset proximities
	proximities = {};
}

void Soundboard::repeat(automa::ServiceProvider& svc, sf::Sound& sound, int frequency, float random_pitch_offset) {
	if (svc.ticker.every_x_ticks(frequency)) { randomize(svc, sound, random_pitch_offset); }
}

void Soundboard::randomize(automa::ServiceProvider& svc, sf::Sound& sound, float random_pitch_offset) {
	float random_pitch = svc.random.random_range_float(-random_pitch_offset, random_pitch_offset);
	sound.setPitch(1.f + random_pitch);
	sound.play();
}

} // namespace audio