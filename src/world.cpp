#include "world.h"

#include <stdexcept>


constexpr size_t EDGE_MARGIN = 2;

World::World(std::vector<std::string> strings) : squares((strings.size() + 2 * EDGE_MARGIN) * (strings[0].size() + 2 * EDGE_MARGIN)), width(strings[0].size()), floors(0) {
	for (size_t y = 0; y < strings.size(); ++y) {
		if (strings[y].size() != width)
			throw std::invalid_argument("All rows must have the same width");

		for (size_t x = 0; x < width; ++x) {
			size_t i = (y + EDGE_MARGIN) * width + (x + EDGE_MARGIN);
			auto& square = squares[i];
			switch (strings[y][x]) {
				case static_cast<char>(Square::Void) : square = Square::Void;                                    break;
				case static_cast<char>(Square::Floor): square = Square::Floor; floors++;                         break;
				case static_cast<char>(Square::Wall) : square = Square::Wall;                                    break;
				case static_cast<char>(Square::Start): square = Square::Start; floors++; starts.emplace_back(i); break;
				case static_cast<char>(Square::End)  : square = Square::End;   floors++;                         break;
				default: throw std::invalid_argument("Invalid character in input");
			}
		}
	}
}



std::string toString(Square square) {
	switch (square) {
		case Square::Void : return " ";
		case Square::Floor: return "\033[38;5;202m.";
		case Square::Wall : return "\033[38;5;33m#";
		case Square::Start: return "\033[0mS";
		case Square::End  : return "\033[0mE";
	}
	return "";
}


World::operator std::string() const {
	std::string result;
	for (size_t y = 0; y < squares.size() / width - 2 * EDGE_MARGIN; ++y) {
		for (size_t x = 0; x < width; ++x)
			result += toString(squares[(y + EDGE_MARGIN) * width + x + EDGE_MARGIN]);
		result += '\n';
	}
	return result + "\033[0m";
}