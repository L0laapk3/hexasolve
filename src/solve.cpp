#include "solve.h"
#include "dice.h"

#include <algorithm>
#include <iostream>



struct Node {
	long pos;
	size_t diceStateI;
	size_t gCost;
	const Node* parent;
	char direction;

    size_t hCost(const World& world) const {
		// Taxicab
        return std::abs(static_cast<long>(pos % (world.width + 2 * EDGE_MARGIN)) - world.endX) + std::abs(static_cast<long>(pos / (world.width + 2 * EDGE_MARGIN)) - world.endY);
    }

    size_t fCost(const World& world) const {
        return gCost + hCost(world);
    }
};



std::pair<std::string, std::string> solve(const World& world, FaceCounts counts) {
	std::cout << world.toString() << std::endl;

	size_t dicePerms = 0;
	iterateDice(counts, [&](auto dice) {
		dicePerms++;
	});

	std::vector<Faces> diceOptions;
	std::vector<std::array<size_t, 4>> diceRotations;
	std::vector<Node> openList;
	std::vector<Node> closedList;
	const size_t reserveSize = dicePerms * world.tiles;
	openList  .reserve(reserveSize);
	closedList.reserve(reserveSize);

	{
		size_t diceStateI = 0;
		iterateDice(counts, [&](auto dice) {
			diceOptions.push_back(dice);
			openList.emplace_back(Node{ world.start, diceStateI, 0, nullptr });
			diceStateI++;
		});
	}

	for (size_t i = 0; i < diceOptions.size(); ++i) {
		std::array<size_t, 4> rotations;
		auto& perm = diceOptions[i];
		for (size_t j = 0; j < 4; ++j) {
			Faces newPerm;
			switch (j) {
			case 0: newPerm = { perm[3], perm[0], perm[1], perm[2], perm[4], perm[5] }; break; // -1
			case 1: newPerm = { perm[1], perm[2], perm[3], perm[0], perm[4], perm[5] }; break; // +1
			case 2: newPerm = { perm[5], perm[1], perm[4], perm[3], perm[0], perm[2] }; break; // -width
			case 3: newPerm = { perm[4], perm[1], perm[5], perm[3], perm[2], perm[0] }; break; // +width
			}
			auto it = std::find(diceOptions.begin(), diceOptions.end(), newPerm);
			rotations[j] = std::distance(diceOptions.begin(), it);
		}
		diceRotations.emplace_back(std::move(rotations));
	}

	while (!openList.empty()) {
		auto nodeIt = std::min_element(openList.begin(), openList.end(), [&](const Node& a, const Node& b) {
			return a.fCost(world) < b.fCost(world);
		});

		closedList.push_back(*nodeIt);
		openList.erase(nodeIt);
		// if (closedList.size() > reserveSize)
		// 	throw std::runtime_error("Memory limit exceeded");

		const Node& node = closedList.back();
		const Face face = diceOptions[node.diceStateI][0];

		// std::cout << world.toString(node.pos) << diceOptions[node.diceStateI].toString() << node.fCost(world) << std::endl;

		// std::cout << "LIST POSITIONS" << std::endl;
		// std::cout << world.toString(node.pos) << std::endl;

		for (size_t i = 0; i < 4; ++i) {
			long step = std::array<long, 4>{ -1, 1, -static_cast<long>(world.width), static_cast<long>(world.width) }[i];
			long newPos;

			if (face == Face::Dash) {
				if (world.squares[node.pos + step] == Square::Wall)
					continue;
				newPos = node.pos + 2 * step;
				if (world.squares[newPos] == Square::Wall)
					newPos = node.pos + step;
			} else { // blank
				newPos = node.pos + step;
			}

			if (world.squares[newPos] == Square::Wall || world.squares[newPos] == Square::Void)
				continue;

			auto newRotation = diceRotations[node.diceStateI][i];

			auto openIt = std::find_if(openList.begin(), openList.end(), [&](const Node& n) {
				return n.pos == newPos && n.diceStateI == newRotation;
			});
			auto closedIt = std::find_if(closedList.begin(), closedList.end(), [&](const Node& n) {
				return n.pos == newPos && n.diceStateI == newRotation;
			});

			if (openIt == openList.end() && closedIt == closedList.end()) {
				char direction = "DULR"[i];
				if (world.squares[newPos] == Square::End) {
					const Node* nodeP = &node;
					std::string path = "";
					path += direction;
					while (nodeP->parent) {
						path = nodeP->direction + path;
						nodeP = nodeP->parent;
						// std::cout << world.toString(nodeP->pos) << diceOptions[nodeP->diceStateI].toString() << " " << nodeP->direction << std::endl;
					}

					auto origRot = diceOptions[nodeP->diceStateI].toString();

					std::cout << origRot << " solves in " << path.size() << ": " << path << std::endl;

					return { origRot, path };
				}
				// if (world.squares[newPos] != Square::Floor)
				// 	throw std::runtime_error("Invalid square");
				// if (newRotation >= dicePerms)
				// 	throw std::runtime_error("Invalid rotation");

				openList.emplace_back(Node{ newPos, newRotation, node.gCost + 1, &node, direction });
			} else if (openIt != openList.end()) {
				if (node.gCost + 1 < openIt->gCost) {
					openIt->gCost = node.gCost + 1;
					openIt->parent = &node;
				}
			} else if (closedIt != closedList.end()) {
				if (node.gCost + 1 < closedIt->gCost) {
					closedIt->gCost = node.gCost + 1;
					closedIt->parent = &node;
				}
			}
		}
	}

	return {};
}