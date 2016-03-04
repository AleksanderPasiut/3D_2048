#pragma once

#include "..\\..\\..\\graphics\\graphics.h"

enum WALL_TYPE
{
	WALL_NONE = -1,
	WALL_FRONT = 0,
	WALL_BACK = 1,
	WALL_LEFT = 2,
	WALL_RIGHT = 3,
	WALL_TOP = 4,
	WALL_BOTTOM = 5
};

class SELECTING
{
protected:
	struct RAY
	{
		D3DXVECTOR3 origin;
		D3DXVECTOR3 direction;
	};
	struct WALL_CORDS
	{
		D3DXVECTOR3 p0;
		D3DXVECTOR3 p1;
		D3DXVECTOR3 p2;
		D3DXVECTOR3 p3;
	};
	
	WALL_CORDS cords[6];
	WALL_TYPE selected;
	bool clicked;

	inline void CreateRay(GRAPHICS&, RAY*, LPARAM) const noexcept;

public:
	SELECTING();

	void PerformSelecting(GRAPHICS&, LPARAM) noexcept;
	void PerformClicking(UINT uMsg) noexcept;

	WALL_TYPE Selected() const noexcept { return selected; }
	bool Clicked() const noexcept { return clicked; }
};