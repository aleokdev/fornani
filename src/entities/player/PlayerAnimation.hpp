
#pragma once

#include <iostream>
#include <optional>
#include <unordered_map>
#include "../../utils/StateFunction.hpp"
#include "../../utils/Counter.hpp"
#include "../animation/Animation.hpp"
#define PA_BIND(f) std::bind(&PlayerAnimation::f, this)

namespace player {

class Player;

enum class AnimState { idle, turn, sharp_turn, run, sprint, shield, between_push, push, rise, suspend, fall, stop, inspect, sit, land, hurt, dash, wallslide, die, backflip };
enum class AnimTriggers { flip, end_death };
int const rate{4};
// { lookup, duration, framerate, num_loops (-1 for infinite), repeat_last_frame, interruptible }
inline anim::Parameters idle{20, 8, 7 * rate, -1, false, true};
inline anim::Parameters turn{33, 3, 4 * rate, 0};
inline anim::Parameters sharp_turn{16, 2, 5 * rate, 0};
inline anim::Parameters run{44, 4, 6 * rate, -1};
inline anim::Parameters sprint{10, 6, 4 * rate, -1};
inline anim::Parameters shield{80, 3, 4 * rate, -1, true};
inline anim::Parameters between_push{85, 1, 4 * rate, 0};
inline anim::Parameters push{86, 4, 7 * rate, -1};
inline anim::Parameters rise{40, 4, 6 * rate, 0};
inline anim::Parameters suspend{30, 3, 7 * rate, -1};
inline anim::Parameters fall{62, 4, 5 * rate, -1};
inline anim::Parameters stop{74, 2, 4 * rate, 0};
inline anim::Parameters land{56, 2, 4 * rate, 0};
inline anim::Parameters inspect{37, 2, 7 * rate, -1, true};
inline anim::Parameters sit{50, 4, 6 * rate, -1, true};
inline anim::Parameters hurt{76, 2, 7 * rate, 0};
inline anim::Parameters dash{40, 4, 5 * rate, 0};
inline anim::Parameters wallslide{66, 4, 7 * rate, -1};
inline anim::Parameters die{76, 4, 8 * rate, -1, true};
inline anim::Parameters backflip{90, 6, 5 * rate, 0};

class PlayerAnimation {

  public:
	PlayerAnimation(player::Player& plr);

	anim::Animation animation{};
	AnimState state{};
	util::BitFlags<AnimTriggers> triggers{};
	util::Counter idle_timer{};
	util::Cooldown post_death{400};

	void update();
	void start();
	[[nodiscard]] auto death_over() -> bool { return triggers.consume(AnimTriggers::end_death); }
	[[nodiscard]] auto not_jumping() -> bool { return state != AnimState::rise; }
	[[nodiscard]] auto get_frame() const -> int { return animation.get_frame(); }

	fsm::StateFunction state_function = std::bind(&PlayerAnimation::update_idle, this);

	fsm::StateFunction update_idle();
	fsm::StateFunction update_turn();
	fsm::StateFunction update_sharp_turn();
	fsm::StateFunction update_sprint();
	fsm::StateFunction update_shield();
	fsm::StateFunction update_between_push();
	fsm::StateFunction update_push();
	fsm::StateFunction update_run();
	fsm::StateFunction update_rise();
	fsm::StateFunction update_suspend();
	fsm::StateFunction update_fall();
	fsm::StateFunction update_stop();
	fsm::StateFunction update_inspect();
	fsm::StateFunction update_sit();
	fsm::StateFunction update_land();
	fsm::StateFunction update_hurt();
	fsm::StateFunction update_dash();
	fsm::StateFunction update_wallslide();
	fsm::StateFunction update_die();
	fsm::StateFunction update_backflip();

	bool change_state(AnimState next, anim::Parameters params, bool hard = false);

	Player* m_player;

	struct {
		int sit{2400};
	} timers{};
};

} // namespace player
