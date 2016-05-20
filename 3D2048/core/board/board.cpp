#include "board.h"

void BOARD::PlaceFirstCubes() noexcept
{
	srand(GetTickCount());

	unsigned k1 = rand()%set.size();
	unsigned k2 = rand()%(set.size()-1);
	if (k2 == k1)
		k2 = set.size()-1;

	set[k1]->state = CS_RED;
	set[k2]->state = CS_RED;
}

BOARD::BOARD(GRAPHICS& in_graphics) : 
	graphics(in_graphics),
	walls(graphics)
{
	for (unsigned i = 0; i < properties.x_size; i++)
		for (unsigned j = 0; j < properties.y_size; j++)
			for (unsigned k = 0; k < properties.z_size; k++)
				set.push_back(new CUBE(
					graphics,
					{i, j, k}, 
					properties, 
					CS_INVISIBLE));

	PlaceFirstCubes();

	for (auto it = set.begin(); it != set.end(); it++)
		(*it)->Show();
}

BOARD::~BOARD() noexcept
{
	for (auto it = set.begin(); it != set.end(); it++)
		delete (*it);
}

void BOARD::Draw() noexcept
{
	for (auto it = set.begin(); it != set.end(); it++)
	{
		if ((*it)->ToBeDestroyed())
		{
			delete *it;
			it = set.erase(it);
		}
		else (*it)->Draw();
	}

	walls.Draw();
}

bool BOARD::MouseButtonDown(LPARAM lParam) noexcept
{
	return walls.MouseButtonDown(lParam);
}
void BOARD::MouseMove(LPARAM lParam) noexcept
{
	walls.MouseMove(lParam);
}
void BOARD::MouseButtonUp(LPARAM lParam) noexcept
{
	Move(walls.MouseButtonUp(lParam));
}
