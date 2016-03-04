#include "..\\core\\core.h"

#include "event_proc.h"

extern CORE* Core;

inline void KeyUp(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
		case 0x51:
		{
			PostQuitMessage(0);
			return;
		}
	}
}

LRESULT CALLBACK EventProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_KEYUP:
		{
			KeyUp(wParam, lParam);
			break;
		}
		case WM_LBUTTONDOWN:
		{
			SetCapture(hwnd);
			Core->MouseButtonDown(lParam);
			break;
		}
		case WM_MOUSEMOVE:
		{
			Core->MouseMove(wParam, lParam);
			break;
		}
		case WM_LBUTTONUP:
		{
			ReleaseCapture();
			Core->MouseButtonUp(lParam);
			break;
		}
		case WM_MOUSEWHEEL:
		{
			Core->MouseWheel(wParam, lParam);
			break;
		}
		case WM_PAINT:
		{
			Core->RenderScene();
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}