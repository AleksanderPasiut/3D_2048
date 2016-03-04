#include <windowsx.h>

#include "core.h"

CORE::CORE(HWND hwnd)
{
	try
	{
		graphics = new GRAPHICS(hwnd);

		try
		{
			board = new BOARD(*graphics);
		}
		catch(...) { delete graphics; throw; }
	}
	catch(...) { throw; }
}

CORE::~CORE() noexcept
{
	delete board;
	delete graphics;
}

void CORE::RenderScene() noexcept
{
	graphics->BeginScene();
	board->Draw();
	graphics->EndScene();
}

void CORE::MouseButtonDown(LPARAM lParam) noexcept
{
	if (!board->MouseButtonDown(lParam))
	{
		rotating.active = true;
		rotating.click.x = GET_X_LPARAM(lParam);
		rotating.click.y = GET_Y_LPARAM(lParam);
		rotating.old_rotationY = graphics->RotationY();
		rotating.old_rotationZ = graphics->RotationZ();
	}
}

void CORE::MouseMove(WPARAM wParam, LPARAM lParam) noexcept
{
	switch(wParam)
	{
		case MK_LBUTTON:
		{
			board->MouseMove(lParam);

			if (rotating.active)
			{
				graphics->RotationY() = rotating.old_rotationY+(GET_Y_LPARAM(lParam)-rotating.click.y)*0.005f;
				if (graphics->RotationY() > rotating.rotationY_limit)
					graphics->RotationY() = rotating.rotationY_limit;
				if (graphics->RotationY() < -rotating.rotationY_limit)
					graphics->RotationY() = -rotating.rotationY_limit;
				graphics->RotationZ() = rotating.old_rotationZ-(GET_X_LPARAM(lParam)-rotating.click.x)*0.005f;
				graphics->UpdateMatrixWorld();
			}
			break;
		}
	}
}

void CORE::MouseButtonUp(LPARAM lParam) noexcept
{
	rotating.active = false;
}

void CORE::MouseWheel(WPARAM wParam, LPARAM lParam) noexcept
{
	if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
		graphics->CameraPos().x += zoom.zoom_step;
	else graphics->CameraPos().x -= zoom.zoom_step;

	if (graphics->CameraPos().x > zoom.zoom_max)
		graphics->CameraPos().x = zoom.zoom_max;
	if (graphics->CameraPos().x < zoom.zoom_min)
		graphics->CameraPos().x = zoom.zoom_min;

	graphics->UpdateMatrixView();
}