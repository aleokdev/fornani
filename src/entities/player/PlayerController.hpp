#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include <optional>
#include <unordered_map>
#include "../../utils/BitFlags.hpp"
#include "../../utils/Direction.hpp"

namespace controllers {

constexpr static int jump_time{16};
constexpr static int dash_time{32};

enum class ControllerInput { move_x, jump, shoot, arms_switch, inspect, dash, move_y };
enum class TransponderInput { skip, next, exit };
enum class MovementState { restricted, grounded, walking_autonomously };
enum class Jump {	   // true if jump is pressed and permanently false once released, until player touches the ground again (USED)
	trigger,		   // true for one frame if jump is pressed and the player is grounded (UNUSED)
	can_jump,		   // true if the player is grounded (USED)
	just_jumped,	   // used for updating animation (USED)
	jump_launched,	   // successful jump, set player's y acceleration! (USED)
	jump_held,		   // to prevent deceleration being called after jumping
	jumpsquatting,	   // (USED)
	jumpsquat_trigger, //(USED)
	is_pressed,		   // true if the jump button is pressed, false if not. independent of player's state.
	is_released,	   // true if jump released midair, reset upon landing (USED)
	jumping			   // true if jumpsquat is over, false once player lands (USED)
};

class PlayerController {

  public:
	PlayerController();

	void update();
	void clean();
	void jump();
	void prevent_jump();
	void stop();
	void ground();
	void unground();
	void restrict();
	void unrestrict();

	void stop_dashing();

	void start_jumping();
	void reset_jump();
	void decrement_requests();

	void reset_dash_count();
	void cancel_dash_request();
	void dash();

	void start_jumpsquat();
	void stop_jumpsquatting();
	void reset_jumpsquat_trigger();
	void reset_just_jumped();
	void autonomous_walk();
	void stop_walking_autonomously();

	void set_shot(bool flag);
	float arms_switch();

	void prevent_movement();

	std::optional<float> get_controller_state(ControllerInput key) const;

	bool nothing_pressed();

	bool moving();
	bool moving_left();
	bool moving_right();
	bool facing_left() const;
	bool facing_right() const;
	bool restricted() const;
	bool grounded() const;
	bool walking_autonomously() const;

	float vertical_movement();

	bool jump_requested() const;
	bool dash_requested() const;

	bool jump_released() const;
	bool can_jump() const;
	bool jumping() const;
	bool just_jumped() const;
	bool jump_held() const;

	bool shot();

	bool inspecting();
	bool dashing();
	bool can_dash();

	bool jumpsquatting() const;
	bool jumpsquat_trigger() const;

	bool transponder_skip() const;
	bool transponder_next() const;
	bool transponder_exit() const;

	int get_jump_request() const;
	int get_dash_request() const;
	int get_dash_count() const;
	float dash_value();

	dir::Direction direction{};

  private:
	std::unordered_map<ControllerInput, float> key_map{};
	util::BitFlags<MovementState> flags{}; // unused
	util::BitFlags<Jump> jump_flags{};
	util::BitFlags<TransponderInput> transponder_flags{};

	int jump_request{};
	int dash_request{};
	int dash_count{};
};
} // namespace controllers
