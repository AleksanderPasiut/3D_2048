#pragma once

#include "..\\graphics\\graphics.h"
#include <vector>
#include "cube\\cube.h"
#include "walls\\walls.h"
#include "properties.h"

class BOARD
{
protected:
	GRAPHICS& graphics;
	PROPERTIES properties;
	std::vector<CUBE*> set;
	WALLS walls;

	inline CUBE** PtrsArray(WALL_TYPE) const;
	inline bool FallCubes(CUBE**, WALL_TYPE);
	inline void PlaceFirstCubes() noexcept;
	inline void PlaceNewCube() noexcept;
	void Move(WALL_TYPE) noexcept;

public:
	BOARD(GRAPHICS&);
	BOARD(const BOARD&) = delete;
	BOARD& operator= (const BOARD&) = delete;
	~BOARD() noexcept;

	void Draw() noexcept;

	bool MouseButtonDown(LPARAM) noexcept;
	void MouseMove(LPARAM) noexcept;
	void MouseButtonUp(LPARAM) noexcept;
};
