#include <iostream>

#include "world.h"




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

	std::cout << static_cast<std::string>(world);

	return 0;
}