
#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <cmath>
#include <random>
#include <vector>
#include <deque>
#include "../utils/BitFlags.hpp"
#include "../utils/Direction.hpp"

namespace components {

const sf::Vector2<float> FRICTION_DEFAULT = {0.9f, 0.9f};
float const MASS_DEFAULT = 1.0f;
float const UNIVERSAL_MAX_SPEED = 64.0f;
float const TERMINAL_VELOCITY = 1.8f;

enum class State { grounded };

class PhysicsComponent {
  public:
	using Clock = std::chrono::steady_clock;
	using Time = std::chrono::duration<float>;

	PhysicsComponent() : ground_friction(FRICTION_DEFAULT), air_friction(FRICTION_DEFAULT), mass(MASS_DEFAULT){};
	PhysicsComponent(sf::Vector2<float> fric, float ma, sf::Vector2<float> max_vel = sf::Vector2<float>{UNIVERSAL_MAX_SPEED, UNIVERSAL_MAX_SPEED}, float grav = 0.0f)
		: ground_friction(fric), air_friction(fric), mass(ma), maximum_velocity(max_vel), gravity(grav) {}

	// basic physics variables
	sf::Vector2<float> jerk{};
	sf::Vector2<float> acceleration{};
	sf::Vector2<float> velocity{};
	sf::Vector2<float> position{};
	sf::Vector2<float> ground_friction{};
	sf::Vector2<float> air_friction{};
	sf::Vector2<float> mtv{};

	sf::Vector2<float> previous_acceleration{};
	sf::Vector2<float> previous_velocity{};
	sf::Vector2<float> previous_position{};

	// properties
	float mass{1.0f};
	float gravity{};
	sf::Vector2<float> maximum_velocity{UNIVERSAL_MAX_SPEED, UNIVERSAL_MAX_SPEED};

	void apply_force(sf::Vector2<float> force);
	void apply_force_at_angle(float magnitude, float angle);
	void update_euler();
	void integrate();
	void update();
	void update_dampen();
	void calculate_maximum_acceleration();
	void calculate_jerk();
	void zero();
	void hitstun();
	void set_constant_friction(sf::Vector2<float> fric);

	// fixed physics time step variables
	Time dt{0.001f};
	Clock::time_point current_time = Clock::now();
	Time accumulator{};

	util::BitFlags<State> flags{};
	dir::Direction direction{};

	std::deque<float> x_acc_history{};
	std::deque<float> y_acc_history{};
	int acceleration_sample_size{2560};
};

} // namespace components