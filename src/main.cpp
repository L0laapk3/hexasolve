#include <iostream>

#include "dice.h"
#include "world.h"
#include "solve.h"



int main(int, char**) {

	World world({
		"                            ####   ",
		"                            . .#   ",
		"          . .          .... .#.#   ",
		"####       .... ...##.....####.#   ",
		"#..       . ##.... .#. ....   .    ",
		"#.. . . .#....#... .#..#.   .....  ",
		"#.S. . ..#. .#.... .#...  .#...E..#",
		"#..    #. .. ..#....#. .. . #....  ",
		"####    #   . .  .. ...##..        ",
		"                ....#..   #        ",
		"               #....# . ...        ",
	});

	std::cout << world.toString() << std::endl;

	FaceCounts counts{0};
	counts[(size_t)Face::Blank] = 6;
	counts[(size_t)Face::Dash] = 3;
	auto solution = solve(world, counts);

	std::cout << solution.first << " solves in " << solution.second.size() << ": " << solution.second << std::endl;

	return 0;
}