#include <windowsx.h>

#include "core.h"

CORE::CORE(HWND hwnd)
{
	rotating.rotationY_limit = 1.57f;

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
	rotating.click.x = GET_X_LPARAM(lParam);
	rotating.click.y = GET_Y_LPARAM(lParam);
	rotating.old_rotationY = graphics->RotationY();
	rotating.old_rotationZ = graphics->RotationZ();
}

void CORE::MouseMove(WPARAM wParam, LPARAM lParam) noexcept
{
	switch(wParam)
	{
		case MK_LBUTTON:
		{
			graphics->RotationY() = rotating.old_rotationY+(GET_Y_LPARAM(lParam)-rotating.click.y)*0.005f;
			if (graphics->RotationY() > rotating.rotationY_limit)
				graphics->RotationY() = rotating.rotationY_limit;
			if (graphics->RotationY() < -rotating.rotationY_limit)
				graphics->RotationY() = -rotating.rotationY_limit;
			graphics->RotationZ() = rotating.old_rotationZ-(GET_X_LPARAM(lParam)-rotating.click.x)*0.005f;
			graphics->UpdateMatrixWorld();
			break;
		}
	}
}