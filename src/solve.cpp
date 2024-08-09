#include "solve.h"
#include "dice.h"

#include <algorithm>
#include <iostream>



struct Node {
	long pos;
	size_t diceStateI;
	size_t gCost;
	Node* parent;
	char direction;

    size_t hCost(const World& world) const {
		// Taxicab
        return std::abs(static_cast<long>(pos % world.width) - world.endX) + std::abs(static_cast<long>(pos / world.width) - world.endY);
    }

    size_t fCost(const World& world) const {
        return gCost + hCost(world);
    }
};



std::string solve(World& world, FaceCounts counts) {
	size_t dicePerms = 0;
	iterateDice(counts, [&](DiceState dice) {
		dicePerms++;
	});

	std::vector<DiceState> diceStates;
	std::vector<Node> openList;
	std::vector<Node> closedList;
	openList  .reserve(dicePerms * world.tiles);
	closedList.reserve(dicePerms * world.tiles);

	{
		size_t diceStateI = 0;
		iterateDice(counts, [&](DiceState dice) {
			diceStates.push_back(dice);
			openList.emplace_back(Node{ world.start, diceStateI, 0, nullptr });
			diceStateI++;
		});
	}

	while (!openList.empty()) {
		auto nodeIt = std::min_element(openList.begin(), openList.end(), [&](const Node& a, const Node& b) {
			return a.fCost(world) < b.fCost(world);
		});

		closedList.push_back(*nodeIt);
		openList.erase(nodeIt);

		Node& node = closedList.back();
		// std::cout << world.toString(node.pos) << std::endl;

		// std::cout << "LIST POSITIONS" << std::endl;
		// std::cout << world.toString(node.pos) << std::endl;

		for (long step : std::array<long, 4>{ -1, 1, -static_cast<long>(world.width), static_cast<long>(world.width) }) {
			long newPos;

			Face face = diceStates[node.diceStateI].faces[0];

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

			auto openIt = std::find_if(openList.begin(), openList.end(), [&](const Node& n) {
				return n.pos == newPos;
			});
			auto closedIt = std::find_if(closedList.begin(), closedList.end(), [&](const Node& n) {
				return n.pos == newPos;
			});

			if (openIt == openList.end() && closedIt == closedList.end()) {
				char direction;
				if (step == -1) {
					direction = 'D';
				} else if (step == 1) {
					direction = 'U';
				} else if (step == -static_cast<long>(world.width)) {
					direction = 'L';
				} else if (step == static_cast<long>(world.width)) {
					direction = 'R';
				} else
					direction = '?';
				if (world.squares[newPos] == Square::End) {
					Node* nodeP = &node;
					std::string path = "";
					path += direction;
					while (nodeP->parent) {
						path = nodeP->direction + path;
						nodeP = nodeP->parent;
					}

					return path;
				}
				openList.emplace_back(Node{ newPos, node.diceStateI, node.gCost + 1, &node, direction });
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