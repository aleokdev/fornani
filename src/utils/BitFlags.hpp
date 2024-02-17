
#pragma once

#include <bitset>

namespace util {

template <typename Enum, std::size_t Size = 32u>
struct BitFlags {
	std::bitset<Size> bits{};

	bool test(Enum e) const { return bits[static_cast<std::size_t>(e)]; }
	void set(Enum e) { bits.set(static_cast<std::size_t>(e)); }
	void reset(Enum e) { bits.reset(static_cast<std::size_t>(e)); }

	bool operator==(BitFlags const&) const = default;
};

} // namespace util
