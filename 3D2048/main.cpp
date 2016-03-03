#include <Windows.h>

#include "mainwindow\\mainwindow.h"
#include "core\\core.h"

CORE* Core = 0;

#include "event_proc\\event_proc.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	MAINWINDOW* Mainwindow = 0;
	try
	{
		Mainwindow = new MAINWINDOW(hInstance, EventProc);

		try
		{
			Core = new CORE(Mainwindow->RetHwnd());
		}
		catch(...) { delete Mainwindow; throw; }
	}
	catch(...) { return 0; }

	ShowWindow(Mainwindow->RetHwnd(), SW_MAXIMIZE);

	MSG msg = {0};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Core->RenderScene();
	}

	delete Core;
	delete Mainwindow;
	return static_cast<int>(msg.wParam);
}