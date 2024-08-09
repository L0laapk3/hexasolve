#pragma once

#include <array>
#include <string>

#include "types.h"



enum class Face {
	Blank,
	Dash,
	Cut,
	MAX
};

inline char toChar(Face face) {
	switch (face) {
	case Face::Blank:
		return 'B';
	case Face::Dash:
		return 'D';
	case Face::Cut:
		return 'C';
	default:
		return '?';
	}
}


using FaceCounts = std::array<size_t, static_cast<size_t>(Face::MAX)>;

struct Faces : public std::array<Face, 6> {
	inline std::string toString() const {
		std::string str;
		str += ::toChar((*this)[4]);
		str += " ";
		str += ::toChar((*this)[0]);
		str += ::toChar((*this)[1]);
		str += ::toChar((*this)[2]);
		str += ::toChar((*this)[3]);
		str += " ";
		str += ::toChar((*this)[5]);
		return str;
	}
};

struct DiceState {
	Faces faces;
	size_t cell;
};

template<typename Callable>
void iterateDice(FaceCounts counts, Callable cb, size_t cell = 0, Faces partialState = { Face::Blank }) {
	for (size_t i = 0; i < static_cast<size_t>(Face::MAX); ++i) {
		if (counts[i] == 0)
			continue;
		auto face = static_cast<Face>(i);
		partialState[cell] = face;
		if (cell == 5) {
			cb(partialState);
		} else {
			counts[i]--;
			iterateDice(counts, cb, cell + 1, partialState);
			counts[i]++;
		}
	}
}