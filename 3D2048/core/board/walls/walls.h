#pragma once

#include "..\\..\\graphics\\graphics.h"
#include "selecting\\selecting.h"

class WALLS
{
protected:
	GRAPHICS& graphics;
	D3DXMATRIX matrix_front_back;
	D3DXMATRIX matrix_left_right;
	D3DXMATRIX matrix_top_bottom;

	SELECTING selecting;

	inline void InitMatrices() noexcept;
	inline unsigned DM(WALL_TYPE) noexcept;

public:
	WALLS(GRAPHICS&);
	WALLS(const WALLS&) = delete;
	WALLS& operator= (const WALLS&) = delete;
	~WALLS() noexcept;

	void Draw() noexcept;

	bool MouseButtonDown(LPARAM) noexcept;
	void MouseMove(LPARAM) noexcept;
	void MouseButtonUp(LPARAM) noexcept;
};