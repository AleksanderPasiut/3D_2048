#pragma once

#include <Windows.h>

#include "graphics\\graphics.h"
#include "board\\board.h"

class CORE
{
protected:
	GRAPHICS* graphics;
	BOARD* board;

	struct ROTATING
	{
		POINT click;
		float old_rotationY;
		float old_rotationZ;

		float rotationY_limit;
	};
	ROTATING rotating;

public:
	CORE(HWND);
	CORE(const CORE&) = delete;
	CORE& operator= (const CORE&) = delete;
	~CORE() noexcept;

	void RenderScene() noexcept;
	
	void MouseButtonDown(LPARAM) noexcept;
	void MouseMove(WPARAM, LPARAM) noexcept;
};