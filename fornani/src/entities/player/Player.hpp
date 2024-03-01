
#pragma once

#include <array>
#include <memory>
#include "../../components/BehaviorComponent.hpp"
#include "../../components/PhysicsComponent.hpp"
#include "../../particle/Attractor.hpp"
#include "../../utils/BitFlags.hpp"
#include "../../utils/Collider.hpp"
#include "../../weapon/Arsenal.hpp"
#include "PlayerController.hpp"
#include "PlayerAnimation.hpp"
#include "Transponder.hpp"

namespace player {

float const PLAYER_WIDTH = 18.0f;
float const PLAYER_HEIGHT = 24.0f;
float const head_height{8.f};
float const PLAYER_START_X = 100.0f;
float const PLAYER_START_Y = 100.0f;
float const JUMPBOX_HEIGHT = 8.0f;
float const DETECTOR_WIDTH = 8.0f;
float const DETECTOR_HEIGHT = 22.0f;
float const WALL_SLIDE_DETECTOR_OFFSET = 20.0f;
float const DETECTOR_BUFFER = (PLAYER_HEIGHT - DETECTOR_HEIGHT) / 2;
int const JUMP_BUFFER_TIME = 12;
int const INVINCIBILITY_TIME = 200;
int const ANCHOR_BUFFER = 50;
int const num_sprites{220};
float const stopped_threshold{0.2f};

constexpr inline float antenna_force{0.4f};
constexpr inline float antenna_speed{16.f};

struct PlayerStats {
	int health{};
	int max_health{};
	int orbs{};
	int max_orbs{};
};

struct PlayerInventoryStats {

	uint32_t gem_spinel{};
	uint32_t gem_topaz{};
	uint32_t gem_tourmaline{};
	uint32_t gem_peridot{};

	uint32_t flower_lavender{};
	uint32_t flower_daffodil{};
	uint32_t flower_hibiscus{};
	uint32_t flower_orchid{};
};

struct PhysicsStats {
	float grav{};
	float ground_fric{};
	float air_fric{};
	float x_acc{};
	float air_multiplier{};
	float jump_velocity{};
	float jump_release_multiplier{};
	float hurt_acc{};
	sf::Vector2<float> maximum_velocity{};
	float mass{};
	float dash_multiplier{};
	float dash_speed{};
};

struct Counters {
	int invincibility{};
};

enum class State { alive };

struct PlayerFlags {
	util::BitFlags<State> state{};
};

class Player {
  public:

	Player();

	// init (violates RAII but must happen after resource path is set)
	void init();
	// member functions
	void update();
	void render(sf::RenderWindow& win, sf::Vector2<float>& campos);
	void assign_texture(sf::Texture& tex);
	void update_animation();
	void update_sprite();
	void update_transponder();
	void flash_sprite();
	void calculate_sprite_offset();

	void set_position(sf::Vector2<float> new_pos);
	void update_direction();
	void update_weapon();
	void walk();
	void hurt(int amount);
	void update_antennae();

	bool grounded() const;
	bool fire_weapon();

	// level events
	void make_invincible();
	void update_invincibility();
	bool is_invincible() const;
	void kill();
	void start_over();

	void reset_flags();
	void total_reset();

	arms::Weapon& equipped_weapon();

	// map helpers
	dir::LR entered_from();

	// for debug mode
	std::string print_direction(bool lr);

	//components
	controllers::PlayerController controller{};
	Transponder transponder{};
	shape::Collider collider{};
	PlayerAnimation animation{};
	behavior::DIR last_dir{};

	//weapons
	arms::Arsenal arsenal{};
	int current_weapon{};

	sf::Vector2<float> apparent_position{};
	sf::Vector2<float> anchor_point{};
	sf::Vector2<float> hand_position{};
	sf::Vector2<float> sprite_offset{};
	sf::Vector2<float> sprite_dimensions{};
	sf::Vector2<float> sprite_position{};

	std::vector<vfx::Attractor> antennae{};
	sf::Vector2<float> antenna_offset{4.f, -13.f};

	PlayerStats player_stats{3, 3, 0, 99999};
	PlayerInventoryStats player_inv_stats{};
	PhysicsStats physics_stats{};
	PlayerFlags flags{};

	Counters counters{};

	// sprites
	sf::Sprite sprite{};

	bool grav = true;

	int jump_request{};

	bool just_hurt{};
	bool start_cooldown{};
	bool sprite_flip{};
};

} // namespace player