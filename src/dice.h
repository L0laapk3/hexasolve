#pragma once

#include <array>

#include "types.h"



enum class Face {
	Blank,
	Dash,
	Cut,
	MAX
};

struct Dice {
	Dice(std::array<size_t, static_cast<size_t>(Face::MAX)> const& availableFaces);
};