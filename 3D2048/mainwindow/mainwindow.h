#pragma once

#include <Windows.h>

class MAINWINDOW
{
protected:
	WNDCLASSEX wc;
	HWND hwnd;

	inline void InitWindowClass(HINSTANCE, WNDPROC);
	inline void InitHwnd();

public:
	MAINWINDOW(HINSTANCE, WNDPROC);
	MAINWINDOW(const MAINWINDOW&) = delete;
	MAINWINDOW& operator= (const MAINWINDOW&) = delete;
	~MAINWINDOW() noexcept;

	HWND RetHwnd() const noexcept { return hwnd; }
};



