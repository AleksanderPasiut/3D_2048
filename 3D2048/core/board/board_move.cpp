#include "board.h"

CUBE** BOARD::PtrsArray(WALL_TYPE direction) const
{
	CUBE** ret = new CUBE* [properties.x_size*properties.y_size*properties.z_size];

	for (auto it = set.begin(); it != set.end(); it++)
		ret[(*it)->pos.x*properties.y_size*properties.z_size+
			(*it)->pos.y*properties.z_size+
			(*it)->pos.z] = *it;

	return ret;
}

CUBE* BOARD::Cube(CUBE** table, unsigned x, unsigned y, unsigned z) noexcept
{
	return table[x*properties.y_size*properties.z_size+y*properties.z_size+z];
}

void BOARD::Move(WALL_TYPE direction) noexcept
{
	CUBE** cpa;
	try
	{	cpa = PtrsArray(direction);	}
	catch(...) { return; }

	if (direction == WALL_NONE)
		return;

	for (unsigned i = 0; i < properties.y_size; i++)
		for (unsigned j = 0; j < properties.z_size; j++)
		{
			Cube(cpa, 0, i, j)->MoveOut(D3DXVECTOR3(-1.5f, 0.0f, 0.0f));

			for (unsigned k = 1; k < properties.x_size; k++)
				Cube(cpa, k, i, j)->Move({k-1, i, j}, Cube(cpa, k, i, j)->RetState());

			CUBE* nc = new CUBE(graphics, {2, i, j}, properties, CS_RED);
			set.push_back(nc);
			nc->MoveIn(D3DXVECTOR3(1.5f, 0.0f, 0.0f));
		}

	delete[] cpa;
}