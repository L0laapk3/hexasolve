#include <iostream>

#include "dice.h"
#include "world.h"
#include "solve.h"



int main(int, char**) {

	if constexpr (1) { // world 6
		auto solution = solve(World({
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
		}), { 6, 6 });
	}
	

	return 0;
}