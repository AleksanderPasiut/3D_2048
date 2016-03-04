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
		bool active;
		POINT click;
		float old_rotationY;
		float old_rotationZ;

		float rotationY_limit;

		ROTATING() : active(false), rotationY_limit(1.57f) {}
	};
	ROTATING rotating;

	struct ZOOM
	{
		float zoom_max;
		float zoom_min;
		float zoom_step;

		ZOOM() : zoom_max(10.0f), zoom_min(3.6f), zoom_step(0.2f) {}
	};
	ZOOM zoom;

public:
	CORE(HWND);
	CORE(const CORE&) = delete;
	CORE& operator= (const CORE&) = delete;
	~CORE() noexcept;

	void RenderScene() noexcept;
	
	void MouseButtonDown(LPARAM) noexcept;
	void MouseMove(WPARAM, LPARAM) noexcept;
	void MouseButtonUp(LPARAM) noexcept;
	void MouseWheel(WPARAM, LPARAM) noexcept;
};