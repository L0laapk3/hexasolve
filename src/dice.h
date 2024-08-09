#pragma once

#include <array>

#include "types.h"



enum class Face {
	Blank,
	Dash,
	Cut,
	MAX
};


using FaceCounts = std::array<size_t, static_cast<size_t>(Face::MAX)>;

struct DiceState {
	std::array<Face, 6> faces;
	size_t cell;
};

template<typename Callable>
void iterateDice(FaceCounts counts, Callable cb, size_t cell = 0, DiceState partialState = { Face::Blank }) {
	cb(DiceState{ Face::Dash });

	// for (size_t i = 0; i < static_cast<size_t>(Face::MAX); ++i) {
	// 	if (counts[i] == 0)
	// 		continue;
	// 	auto face = static_cast<Face>(i);
	// 		counts[i]--;
	// 		iterateDice(counts, cb, cell + 1);
	// 		counts[i]++;
	// 	}
	// }
}