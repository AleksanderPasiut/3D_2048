#include "board.h"

CUBE** BOARD::PtrsArray(WALL_TYPE wall) const
{
	if (wall == WALL_NONE)
		return 0;

	CUBE** ret = new CUBE* [properties.x_size*properties.y_size*properties.z_size];

	if (!ret)
		return 0;

	for (auto it = set.begin(); it != set.end(); it++)
	{
		CUBE::POS& p = (*it)->pos;
		const unsigned& x_size = properties.x_size;
		const unsigned& y_size = properties.y_size;
		const unsigned& z_size = properties.z_size;

		switch(wall)
		{
			case WALL_FRONT: 
				ret[y_size*z_size*(x_size-1-p.x)+y_size*p.z+p.y] = *it;
				break;
			case WALL_BACK:
				ret[y_size*z_size*p.x+y_size*p.z+p.y] = *it;
				break;
			case WALL_LEFT: 
				ret[x_size*z_size*(y_size-1-p.y)+x_size*p.z+p.x] = *it;
				break;
			case WALL_RIGHT:
				ret[x_size*z_size*p.y+x_size*p.z+p.x] = *it;
				break;
			case WALL_TOP: 
				ret[y_size*x_size*(z_size-1-p.z)+y_size*p.x+p.y] = *it;
				break;
			case WALL_BOTTOM:
				ret[y_size*x_size*p.z+y_size*p.x+p.y] = *it;
				break;

		}
	}

	return ret;
}

bool BOARD::FallCubes(CUBE** cubes, WALL_TYPE direction)
{
	bool ret = false;

	unsigned aocis; // amount of cubes in surface
	unsigned aos; // amount of surfaces

	switch(direction)
	{
		case WALL_NONE:
			return ret;
		case WALL_FRONT:
		case WALL_BACK:
			aocis = properties.y_size*properties.z_size;
			aos = properties.x_size;
			break;
		case WALL_LEFT:
		case WALL_RIGHT:
			aocis = properties.x_size*properties.z_size;
			aos = properties.y_size;
			break;
		case WALL_TOP:
		case WALL_BOTTOM:
			aocis = properties.x_size*properties.y_size;
			aos = properties.z_size;
			break;
	}

	CUBE::POS* position = new CUBE::POS[2*aos];

	if (!position)
		return ret;

	CUBE::POS* assign  = position+aos;

	CUBE_STATE* target = new CUBE_STATE[aos];

	if (!target)
	{
		delete[] position;
		return ret;
	}

	for (unsigned i = 0; i < aocis; i++)
	{
		// spisanie pozycji
		for (unsigned j = 0; j < aos; j++)
			position[j] = cubes[i+j*aocis]->pos;
		
		// przesuwanie i ³¹czenie klocków
		unsigned start = 0;
		unsigned end = 0;
		unsigned j;
		for (j = 0; j < aos; j++)
		{
			// czy dalej s¹ jeszcze kolorowe klocki?
			bool is_there_any = false;
			for (unsigned k = start; k < aos; k++)
				if (cubes[i+k*aocis]->RetState())
				{	
					is_there_any = true;
					break; 
				}

			if (!is_there_any)
				break;
			
			// znalezienie przedzia³u klocków do po³¹czenia
			end = 0;
			bool dubel = false;
			CUBE_STATE ref = CS_INVISIBLE;
			for (unsigned k = start; k < aos; k++)
			{
				CUBE*& cube = cubes[i+k*aocis];
				if (cube->RetState())
				{
					if (!ref)
					{
						ref = cube->RetState();
						end = k;
					}
					else
					{
						if (ref == cube->RetState())
						{
							dubel = true;
							end = k;
						}
						break;
					}
				}
			}

			if (end != j)
				ret = true;

			// ³¹czenie
			for (unsigned k = start; k <= end; k++)
				cubes[i+k*aocis]->Move(position[j], dubel ? static_cast<CUBE_STATE>(ref+1) : ref, k != start);

			start = ++end;
		}

		// wstawienie brakuj¹cych klocków
		for (; j < end; j++)
			set.push_back(new CUBE(graphics, position[j], properties, CS_INVISIBLE));
	}


	for (auto it = set.begin(); it != set.end(); it++)
		if (!(*it)->Showed())
			(*it)->Show();

	delete[] target;
	delete[] position;

	return ret;
}

void BOARD::PlaceNewCube() noexcept
{
	std::vector<CUBE*> invisible_cubes;
	for (auto it = set.begin(); it != set.end(); it++)
		if ((*it)->RetState() == CS_INVISIBLE)
			invisible_cubes.push_back(*it);
	
	if (invisible_cubes.empty())
		return;

	srand(GetTickCount());
	unsigned select = rand()%invisible_cubes.size();

	invisible_cubes[select]->Move(invisible_cubes[select]->pos, CS_RED, false);
}

void BOARD::Move(WALL_TYPE direction) noexcept
{


	if (direction == WALL_NONE)
		return;

	CUBE** cubes = PtrsArray(direction);

	if (FallCubes(cubes, direction))
		PlaceNewCube();

	delete[] cubes;
}