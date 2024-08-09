#include "world.h"

#include <stdexcept>


constexpr size_t EDGE_MARGIN = 2;

World::World(std::vector<std::string> strings) : squares((strings.size() + 2 * EDGE_MARGIN) * (strings[0].size() + 2 * EDGE_MARGIN)), width(strings[0].size()), tiles(0) {
	for (size_t y = 0; y < strings.size(); ++y) {
		if (strings[y].size() != width)
			throw std::invalid_argument("All rows must have the same width");

		for (size_t x = 0; x < width; ++x) {
			size_t i = (y + EDGE_MARGIN) * width + (x + EDGE_MARGIN);
			auto& square = squares[i];
			switch (strings[y][x]) {
				case ' ': square = Square::Void;                      break;
				case '.': square = Square::Floor; tiles++;            break;
				case '#': square = Square::Wall;                      break;
				case 'S': square = Square::Start; tiles++; start = i; break;
				case 'E': square = Square::End;   tiles++; end = i;   break;
				default : throw std::invalid_argument("Invalid character in input");
			}
		}
	}

	endX = end % width;
	endY = end / width;
}



std::string toString(Square square) {
	switch (square) {
		case Square::Void : return " ";
		case Square::Floor: return "\033[38;5;202m.";
		case Square::Wall : return "\033[38;5;33m#";
		case Square::Start: return "\033[38;5;34mS";
		case Square::End  : return "\033[38;5;34mE";
	}
	return "";
}


std::string World::toString(long pos) const {
	std::string result;
	for (size_t y = 0; y < squares.size() / width - 2 * EDGE_MARGIN; ++y) {
		for (size_t x = 0; x < width; ++x) {
			int i = (y + EDGE_MARGIN) * width + x + EDGE_MARGIN;
			if (i == pos)
				result += "\033[48;5;202m";
			result += ::toString(squares[i]);
			if (i == pos)
				result += "\033[0m";
		}
		result += '\n';
	}
	return result + "\033[0m";
}