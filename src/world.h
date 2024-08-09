#pragma once

#include <array>
#include <vector>
#include <string>

#include "types.h"


enum class Square {
	Void  = ' ',
	Floor = '.',
	Wall  = '#',
	Start = 'S',
	End   = 'E',
};

std::string toString(Square square);


struct World {
	World(std::vector<std::string> strings);

	std::vector<Square> squares;
	size_t width;
	size_t floors;
	std::vector<size_t> starts;

	operator std::string() const;
};