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

public:
	BOARD(GRAPHICS&);
	BOARD(const BOARD&) = delete;
	BOARD& operator= (const BOARD&) = delete;
	~BOARD() noexcept;

	void Draw() noexcept;
};
