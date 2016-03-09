#include "board.h"

void BOARD::Move(WALL_TYPE direction) noexcept
{
	if (direction == WALL_NONE)
		return;

	float bound = 1.7f;

	CUBE_STATE target_color = static_cast<CUBE_STATE>(direction+1);

	for (auto it = set.begin(); it != set.end(); it++)
	{
		CUBE*& cube = *it;

		switch(direction)
		{
			case WALL_FRONT:
			{
				if (cube->pos.x == properties.x_size-1)
					cube->MoveOut(D3DXVECTOR3(bound, cube->Position().y, cube->Position().z));
				else cube->Move({cube->pos.x+1, cube->pos.y, cube->pos.z}, target_color);
				break;
			}
			case WALL_BACK:
			{
				if (cube->pos.x == 0)
					cube->MoveOut(D3DXVECTOR3(-bound, cube->Position().y, cube->Position().z));
				else cube->Move({cube->pos.x-1, cube->pos.y, cube->pos.z}, target_color);
				break;
			}
			case WALL_LEFT:
			{
				if (cube->pos.y == properties.y_size-1)
					cube->MoveOut(D3DXVECTOR3(cube->Position().x, bound, cube->Position().z));
				else cube->Move({cube->pos.x, cube->pos.y+1, cube->pos.z}, target_color);
				break;
			}
			case WALL_RIGHT:
			{
				if (cube->pos.y == 0)
					cube->MoveOut(D3DXVECTOR3(cube->Position().x, -bound, cube->Position().z));
				else cube->Move({cube->pos.x, cube->pos.y-1, cube->pos.z}, target_color);
				break;
			}
			case WALL_TOP:
			{
				if (cube->pos.z == properties.z_size-1)
					cube->MoveOut(D3DXVECTOR3(cube->Position().x, cube->Position().y, bound));
				else cube->Move({cube->pos.x, cube->pos.y, cube->pos.z+1}, target_color);
				break;
			}
			case WALL_BOTTOM:
			{
				if (cube->pos.z == 0)
					cube->MoveOut(D3DXVECTOR3(cube->Position().x, cube->Position().y, -bound));
				else cube->Move({cube->pos.x, cube->pos.y, cube->pos.z-1}, target_color);
				break;
			}
		}
	}

	switch(direction)
	{
		case WALL_FRONT:
		{
			for (unsigned i = 0; i < properties.y_size; i++)
				for (unsigned j = 0; j < properties.z_size; j++)
				{
					CUBE* nc = new CUBE(graphics, {0, i, j}, properties, target_color);
					set.push_back(nc);
					nc->MoveIn(D3DXVECTOR3(-bound, nc->Position().y, nc->Position().z));
				}
			break;
		}
		case WALL_BACK:
		{
			for (unsigned i = 0; i < properties.y_size; i++)
				for (unsigned j = 0; j < properties.z_size; j++)
				{
					CUBE* nc = new CUBE(graphics, {2, i, j}, properties, target_color);
					set.push_back(nc);
					nc->MoveIn(D3DXVECTOR3(bound, nc->Position().y, nc->Position().z));
				}
			break;
		}
		case WALL_LEFT:
		{
			for (unsigned i = 0; i < properties.x_size; i++)
				for (unsigned j = 0; j < properties.z_size; j++)
				{
					CUBE* nc = new CUBE(graphics, {i, 0, j}, properties, target_color);
					set.push_back(nc);
					nc->MoveIn(D3DXVECTOR3(nc->Position().x, -bound, nc->Position().z));
				}
			break;
		}
		case WALL_RIGHT:
		{
			for (unsigned i = 0; i < properties.x_size; i++)
				for (unsigned j = 0; j < properties.z_size; j++)
				{
					CUBE* nc = new CUBE(graphics, {i, 2, j}, properties, target_color);
					set.push_back(nc);
					nc->MoveIn(D3DXVECTOR3(nc->Position().x, bound, nc->Position().z));
				}
			break;
		}
		case WALL_TOP:
		{
			for (unsigned i = 0; i < properties.x_size; i++)
				for (unsigned j = 0; j < properties.y_size; j++)
				{
					CUBE* nc = new CUBE(graphics, {i, j, 0}, properties, target_color);
					set.push_back(nc);
					nc->MoveIn(D3DXVECTOR3(nc->Position().x, nc->Position().y, -bound));
				}
			break;
		}
		case WALL_BOTTOM:
		{
			for (unsigned i = 0; i < properties.x_size; i++)
				for (unsigned j = 0; j < properties.y_size; j++)
				{
					CUBE* nc = new CUBE(graphics, {i, j, 2}, properties, target_color);
					set.push_back(nc);
					nc->MoveIn(D3DXVECTOR3(nc->Position().x, nc->Position().y, bound));
				}
			break;
		}
	}
}