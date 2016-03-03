#include "mainwindow.h"

void MAINWINDOW::InitWindowClass(HINSTANCE hInstance, WNDPROC wndproc)
{
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = wndproc;
	wc.lpszClassName = L"3D2048AppWindowClass";
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));

	if (!RegisterClassEx(&wc))
		throw 0;
}

void MAINWINDOW::InitHwnd()
{
	hwnd = CreateWindowEx(
		0,
		wc.lpszClassName,
		L"3D2048",
		WS_POPUP,
		0,
		0,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		0,
		0,
		wc.hInstance,
		0);

	if (!hwnd)
		throw 0;
}

MAINWINDOW::MAINWINDOW(HINSTANCE hInstance, WNDPROC wndproc)
{
	try
	{
		InitWindowClass(hInstance, wndproc);

		try
		{
			InitHwnd();
		}
		catch(...) { UnregisterClass(wc.lpszClassName, wc.hInstance); throw; }
	}
	catch(...) { throw; }
}

MAINWINDOW::~MAINWINDOW() noexcept
{
	DestroyWindow(hwnd);
	UnregisterClass(wc.lpszClassName, wc.hInstance);
}