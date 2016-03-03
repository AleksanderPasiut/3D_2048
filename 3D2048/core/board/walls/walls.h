#pragma once

#include "..\\..\\graphics\\graphics.h"

class WALLS
{
protected:
	GRAPHICS& graphics;
	D3DXMATRIX matrix_front_back;
	D3DXMATRIX matrix_left_right;
	D3DXMATRIX matrix_top_bottom;

	void InitMatrices() noexcept;

public:
	WALLS(GRAPHICS&);
	WALLS(const WALLS&) = delete;
	WALLS& operator= (const WALLS&) = delete;
	~WALLS() noexcept;

	void Draw() noexcept;
};