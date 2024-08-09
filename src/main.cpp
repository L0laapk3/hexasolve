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
	counts[(size_t)Face::Dash] = 6;
	auto solution = solve(world, counts);

	std::cout << solution.size() << " " << solution << std::endl;

	return 0;
}