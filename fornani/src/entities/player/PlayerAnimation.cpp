#include "PlayerAnimation.hpp"

namespace player {

void PlayerAnimation::update() {
	animation.update();
	state_function = state_function();
}

void PlayerAnimation::start() { animation.start(); }

int PlayerAnimation::get_frame() const { return animation.get_frame(); }

bool PlayerAnimation::not_jumping() { return !(state.test(AnimState::jumpsquat) || state.test(AnimState::rise)); }

fsm::StateFunction PlayerAnimation::update_idle() {
	animation.label = "idle";
	if (state.test(AnimState::turn)) {
		state.reset(AnimState::idle);
		animation.set_params(turn);
		return BIND(update_turn);
	}
	if (state.test(AnimState::jumpsquat)) {
		state.reset(AnimState::idle);
		animation.set_params(jumpsquat);
		return BIND(update_jumpsquat);
	}
	if (state.test(AnimState::run)) {
		state.reset(AnimState::idle);
		animation.set_params(run);
		return BIND(update_run);
	}
	if (state.test(AnimState::suspend)) {
		state.reset(AnimState::idle);
		animation.set_params(suspend);
		return BIND(update_suspend);
	}
	if (state.test(AnimState::fall)) {
		state.reset(AnimState::idle);
		animation.set_params(fall);
		return BIND(update_fall);
	}
	if (state.test(AnimState::inspect)) {
		state.reset(AnimState::idle);
		animation.set_params(inspect);
		return BIND(update_inspect);
	}
	state = {};
	state.set(AnimState::idle);
	return std::move(state_function);
}

fsm::StateFunction PlayerAnimation::update_run() {
	animation.label = "run";
	if (state.test(AnimState::turn)) {
		state.reset(AnimState::run);
		animation.set_params(turn);
		return BIND(update_turn);
	}
	if (state.test(AnimState::stop) && animation.keyframe_over()) {
		state.reset(AnimState::run);
		animation.set_params(stop);
		return BIND(update_stop);
	}
	if (state.test(AnimState::suspend) && animation.keyframe_over()) {
		state.reset(AnimState::run);
		animation.set_params(suspend);
		return BIND(update_suspend);
	}
	if (state.test(AnimState::fall) && animation.keyframe_over()) {
		state.reset(AnimState::run);
		animation.set_params(fall);
		return BIND(update_fall);
	}
	if (state.test(AnimState::jumpsquat)) {
		state.reset(AnimState::run);
		animation.set_params(jumpsquat);
		return BIND(update_jumpsquat);
	}
	if (state.test(AnimState::idle) && animation.keyframe_over()) {
		state.reset(AnimState::run);
		animation.set_params(idle);
		return BIND(update_idle);
	}
	if (state.test(AnimState::inspect) && animation.keyframe_over()) {
		state.reset(AnimState::run);
		animation.set_params(inspect);
		return BIND(update_inspect);
	}
	state = {};
	state.set(AnimState::run);
	return std::move(state_function);
}

fsm::StateFunction PlayerAnimation::update_jumpsquat() {
	animation.label = "jumpsquat";
	if (animation.complete()) {
		if (state.test(AnimState::dash)) {
			state.reset(AnimState::jumpsquat);
			animation.set_params(dash);
			return BIND(update_dash);
		}
		state = {};
		state.set(AnimState::rise);
		animation.set_params(rise);
		return BIND(update_rise);
	}
	state = {};
	state.set(AnimState::jumpsquat);
	return BIND(update_jumpsquat);
}

fsm::StateFunction PlayerAnimation::update_turn() {
	animation.label = "turn";
	if (animation.complete()) {
		if (state.test(AnimState::suspend)) {
			state.reset(AnimState::turn);
			animation.set_params(suspend);
			return BIND(update_suspend);
		}
		if (state.test(AnimState::run)) {
			state.reset(AnimState::turn);
			animation.set_params(run);
			return BIND(update_run);
		}
		if (state.test(AnimState::rise)) {
			state.reset(AnimState::turn);
			animation.set_params(rise);
			return BIND(update_rise);
		}
		if (state.test(AnimState::inspect)) {
			state.reset(AnimState::turn);
			animation.set_params(inspect);
			return BIND(update_inspect);
		}
		state = {};
		state.set(AnimState::idle);
		animation.set_params(idle);
		return BIND(update_idle);
	}
	state = {};
	state.set(AnimState::turn);
	return BIND(update_turn);
}

fsm::StateFunction PlayerAnimation::update_rise() {
	animation.label = "rise";
	if (state.test(AnimState::suspend)) {
		state.reset(AnimState::rise);
		animation.set_params(suspend);
		return BIND(update_suspend);
	}
	if (state.test(AnimState::idle)) {
		state.reset(AnimState::rise);
		animation.set_params(idle);
		return BIND(update_idle);
	}
	if (state.test(AnimState::dash)) {
		state.reset(AnimState::rise);
		animation.set_params(dash);
		return BIND(update_dash);
	}
	state = {};
	state.set(AnimState::rise);
	return std::move(state_function);
}

fsm::StateFunction PlayerAnimation::update_suspend() {
	animation.label = "suspend";
	if (state.test(AnimState::fall) && animation.keyframe_over()) {
		state.reset(AnimState::suspend);
		animation.set_params(fall);
		return BIND(update_fall);
	}
	if (state.test(AnimState::land)) {
		state.reset(AnimState::suspend);
		animation.set_params(land);
		return BIND(update_land);
	}
	if (state.test(AnimState::run)) {
		state.reset(AnimState::suspend);
		animation.set_params(run);
		return BIND(update_run);
	}
	if (state.test(AnimState::idle)) {
		state.reset(AnimState::suspend);
		animation.set_params(idle);
		return BIND(update_idle);
	}
	if (state.test(AnimState::dash)) {
		state.reset(AnimState::suspend);
		animation.set_params(dash);
		return BIND(update_dash);
	}
	state = {};
	state.set(AnimState::suspend);
	return std::move(state_function);
}

fsm::StateFunction PlayerAnimation::update_fall() {
	animation.label = "fall";
	if (state.test(AnimState::land)) {
		state.reset(AnimState::fall);
		animation.set_params(land);
		return BIND(update_land);
	}
	if (state.test(AnimState::jumpsquat)) {
		state.reset(AnimState::fall);
		animation.set_params(jumpsquat);
		return BIND(update_jumpsquat);
	}
	if (state.test(AnimState::run)) {
		state.reset(AnimState::fall);
		animation.set_params(run);
		return BIND(update_run);
	}
	if (state.test(AnimState::rise)) {
		state.reset(AnimState::fall);
		animation.set_params(rise);
		return BIND(update_rise);
	}
	if (state.test(AnimState::dash)) {
		state.reset(AnimState::fall);
		animation.set_params(dash);
		return BIND(update_dash);
	}
	state = {};
	state.set(AnimState::fall);
	return std::move(state_function);
}

fsm::StateFunction PlayerAnimation::update_stop() {
	animation.label = "stop";
	if (animation.complete()) {
		if (state.test(AnimState::run)) {
			state.reset(AnimState::stop);
			animation.set_params(run);
			return BIND(update_run);
		}
		if (state.test(AnimState::turn)) {
			state.reset(AnimState::stop);
			animation.set_params(turn);
			return BIND(update_turn);
		}
		if (state.test(AnimState::suspend)) {
			state.reset(AnimState::stop);
			animation.set_params(suspend);
			return BIND(update_suspend);
		}
		if (state.test(AnimState::inspect)) {
			state.reset(AnimState::stop);
			animation.set_params(inspect);
			return BIND(update_inspect);
		}
		state = {};
		state.set(AnimState::idle);
		animation.set_params(idle);
		return BIND(update_idle);
	}
	state = {};
	state.set(AnimState::stop);
	return BIND(update_stop);
}

fsm::StateFunction PlayerAnimation::update_inspect() {
	animation.label = "inspect";
	if (animation.complete()) {
		if (state.test(AnimState::run)) {
			state.reset(AnimState::inspect);
			animation.set_params(run);
			animation.end();
			return BIND(update_run);
		}
		if (state.test(AnimState::jumpsquat)) {
			state.reset(AnimState::inspect);
			animation.set_params(jumpsquat);
			animation.end();
			return BIND(update_jumpsquat);
		}
	}
	state = {};
	state.set(AnimState::inspect);
	return std::move(state_function);
}

fsm::StateFunction PlayerAnimation::update_land() {
	animation.label = "land";

	if (animation.complete()) {
		if (state.test(AnimState::run)) {
			state.reset(AnimState::land);
			animation.set_params(run);
			return BIND(update_run);
		}
		if (state.test(AnimState::jumpsquat)) {
			state.reset(AnimState::land);
			animation.set_params(jumpsquat);
			return BIND(update_jumpsquat);
		}
		if (state.test(AnimState::rise)) {
			state.reset(AnimState::land);
			animation.set_params(rise);
			return BIND(update_rise);
		}
		if (state.test(AnimState::inspect)) {
			state.reset(AnimState::land);
			animation.set_params(inspect);
			return BIND(update_inspect);
		}
		state = {};
		state.set(AnimState::idle);
		animation.set_params(idle);
		return BIND(update_idle);
	}
	state = {};
	state.set(AnimState::land);
	return BIND(update_land);
}

fsm::StateFunction PlayerAnimation::update_hurt() {
	animation.label = "hurt";
	state = {};
	state.set(AnimState::hurt);
	return std::move(state_function);
}

fsm::StateFunction PlayerAnimation::update_dash() {
	animation.label = "dash";
	if (animation.complete()) {
		if (state.test(AnimState::run)) {
			state.reset(AnimState::dash);
			animation.set_params(run);
			return BIND(update_run);
		}
		if (state.test(AnimState::jumpsquat)) {
			state.reset(AnimState::dash);
			animation.set_params(jumpsquat);
			return BIND(update_jumpsquat);
		}
		if (state.test(AnimState::fall)) {
			state.reset(AnimState::dash);
			animation.set_params(fall);
			return BIND(update_fall);
		}
		if (state.test(AnimState::suspend)) {
			state.reset(AnimState::dash);
			animation.set_params(suspend);
			return BIND(update_suspend);
		}
		if (state.test(AnimState::land)) {
			state.reset(AnimState::dash);
			animation.set_params(land);
			return BIND(update_land);
		}
		state = {};
		state.set(AnimState::idle);
		animation.set_params(idle);
		return BIND(update_idle);
	}
	state = {};
	state.set(AnimState::dash);
	return std::move(state_function);
}

// change_state(AnimState::run, run, update_run());
//
// this is bugged but I really want it to work
//
// fsm::StateFunction PlayerAnimation::change_state(AnimState next, anim::Parameters params, fsm::StateFunction fn) {
//	if (state.test(next)) {
//		animation.set_params(params);
//		return std::move(fn);
//	}
// }

} // namespace player