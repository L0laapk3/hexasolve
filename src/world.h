#pragma once

#include <array>
#include <vector>
#include <string>

#include "types.h"



constexpr size_t EDGE_MARGIN = 2;

enum class Square {
	Void  = 0,
	Floor,
	Wall ,
	Start,
	End  ,
};

std::string toString(Square square);


struct World {
	World(std::vector<std::string> strings);

	std::vector<Square> squares;
	size_t width;
	size_t tiles;
	long end;
	long start;
	S64 endX, endY;

	std::string toString(long pos = -1) const;
};