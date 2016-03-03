#include "board.h"

BOARD::BOARD(GRAPHICS& in_graphics) : 
	graphics(in_graphics),
	walls(graphics)
{
	for (unsigned i = 0; i < 3; i++)
		for (unsigned j = 0; j < 3; j++)
			for (unsigned k = 0; k < 3; k++)
				set.push_back(new CUBE(
					graphics,
					{i, j, k}, 
					properties, 
					static_cast<CUBE_STATE>(i+j+k)));
}

BOARD::~BOARD() noexcept
{
	for (auto it = set.begin(); it != set.end(); it++)
		delete (*it);
}

void BOARD::Draw() noexcept
{
	for (auto it = set.begin(); it != set.end(); it++)
		(*it)->Draw();

	walls.Draw();
}