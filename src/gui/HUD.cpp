#include "HUD.hpp"
#include "../service/ServiceProvider.hpp"
#include "../entities/player/Player.hpp"

namespace gui {

HUD::HUD(automa::ServiceProvider& svc, player::Player& player, sf::Vector2<int> pos) : position(pos) {
	HP_origin = {distance_from_edge, (int)svc.constants.screen_dimensions.y - distance_from_edge - heart_dimensions.y};
	ORB_origin = {distance_from_edge, HP_origin.y - PAD - orb_text_dimensions.y};
	GUN_origin = {distance_from_edge, ORB_origin.y - PAD - pointer_dimensions.y - pointer_pad * 2};
	update(player);
	for (int i = 0; i < num_heart_sprites; ++i) {
		sp_hearts.at(i).setTexture(svc.assets.t_hud_hearts);
		sp_hearts.at(i).setTextureRect(sf::IntRect({heart_dimensions.x * i, 0}, heart_dimensions));
	}
	for (int i = 0; i < num_orb_chars; ++i) {
		sp_orb_text.at(i).setTexture(svc.assets.t_hud_orb_font);
		if (i < 10) {
			sp_orb_text.at(i).setTextureRect(sf::IntRect({orb_text_dimensions.x * i, 0}, orb_text_dimensions));
		} else {
			sp_orb_text.at(i).setTextureRect(sf::IntRect({orb_text_dimensions.x * i, 0}, {orb_label_width, orb_text_dimensions.y}));
		}
	}
	for (int i = 0; i < num_guns; ++i) {
		sp_guns.at(i).setTexture(svc.assets.t_hud_gun_color);
		sp_guns.at(i).setTextureRect(sf::IntRect({0, i * gun_dimensions.y}, gun_dimensions));
		sp_guns_shadow.at(i).setTexture(svc.assets.t_hud_gun_shadow);
		sp_guns_shadow.at(i).setTextureRect(sf::IntRect({0, i * gun_dimensions.y}, gun_dimensions));
	}
	for (int i = 0; i < num_colors; ++i) {
		sp_pointer.at(i).setTexture(svc.assets.t_hud_pointer);
		sp_pointer.at(i).setTextureRect(sf::IntRect({0, i * pointer_dimensions.y}, pointer_dimensions));
	}
}

void HUD::update(player::Player& player) {
	filled_hp_cells = ceil(player.health.get_hp());
	num_orbs = player.player_stats.orbs;
	total_hp_cells = player.health.get_max();
	max_orbs = player.player_stats.max_orbs;
	if (!player.arsenal.loadout.empty()) { gun_name = player.equipped_weapon().label; }
	constrain();
}

void HUD::constrain() {
	if (filled_hp_cells > total_hp_cells) { filled_hp_cells = total_hp_cells; }
	if (filled_hp_cells < 0) { filled_hp_cells = 0; }
	if (num_orbs > max_orbs) { num_orbs = max_orbs; }
	if (num_orbs < 0) { num_orbs = 0; }
}

void HUD::render(player::Player& player, sf::RenderWindow& win) {

	// HP
	for (int i = 0; i < total_hp_cells; ++i) {
		if (i < filled_hp_cells) {
			if (i == 0) {
				sp_hearts.at(HP_FILLED).setPosition(corner_pad.x + HP_origin.x + i * heart_dimensions.x, corner_pad.y + HP_origin.y);
			} else {
				sp_hearts.at(HP_FILLED).setPosition(corner_pad.x + HP_origin.x + i * heart_dimensions.x + i * HP_pad, corner_pad.y + HP_origin.y);
			}
			win.draw(sp_hearts.at(HP_FILLED));

		} else {
			sp_hearts.at(HP_GONE).setPosition(corner_pad.x + HP_origin.x + i * heart_dimensions.x + i * HP_pad, corner_pad.y + HP_origin.y);
			win.draw(sp_hearts.at(HP_GONE));
		}
	}

	// ORB
	sp_orb_text.at(orb_label_index).setPosition(corner_pad.x + ORB_origin.x, corner_pad.y + ORB_origin.y);
	win.draw(sp_orb_text.at(orb_label_index));

	digits = std::to_string(num_orbs);
	int ctr{0};
	for (auto& digit : digits) {

		if (digit - '0' >= 0 && digit - '0' < 10) {
			sp_orb_text.at(digit - '0').setPosition(corner_pad.x + ORB_origin.x + orb_label_width + orb_pad + (orb_text_dimensions.x * ctr), corner_pad.y + ORB_origin.y);
			win.draw(sp_orb_text.at(digit - '0'));
		}

		ctr++;
	}

	// GUN
	if (!player.arsenal.loadout.empty()) {
		int pointer_index{0};
		int loadout_size = player.arsenal.loadout.size();
		for (int i = 0; i < loadout_size; ++i) {
			int gun_index = player.arsenal.loadout.at(i)->get_id();
			sp_guns.at(gun_index).setPosition(corner_pad.x + GUN_origin.x + pointer_dimensions.x + gun_pad_horiz, corner_pad.y + GUN_origin.y - i * gun_dimensions.y - i * gun_pad_vert);
			sp_guns_shadow.at(gun_index).setPosition(corner_pad.x + GUN_origin.x + pointer_dimensions.x + gun_pad_horiz + 2, corner_pad.y + GUN_origin.y - i * gun_dimensions.y - i * gun_pad_vert);
			if (i == player.arsenal.get_index()) {
				win.draw(sp_guns_shadow.at(gun_index));

				win.draw(sp_guns.at(gun_index));

				pointer_index = i;
			} else {
				win.draw(sp_guns_shadow.at(gun_index));
			}
		}
		arms::WEAPON_TYPE curr_type = player.equipped_weapon().type;
		sp_pointer.at(player.equipped_weapon().attributes.ui_color).setPosition(corner_pad.x + GUN_origin.x, corner_pad.y + GUN_origin.y + pointer_pad - pointer_index * (gun_dimensions.y + gun_pad_vert));
		win.draw(sp_pointer.at(player.equipped_weapon().attributes.ui_color));
	}
}

void HUD::set_corner_pad(automa::ServiceProvider& svc, bool file_preview) { file_preview ? corner_pad = {((float)svc.constants.screen_dimensions.x / 2.f) - 140.f, -60.f} : corner_pad = {0.f, 0.f}; }

} // namespace gui