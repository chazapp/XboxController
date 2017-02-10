#ifndef CURSORCONTROLLER_HPP_
#define CURSORCONTROLLER_HPP_

#pragma comment(lib, "User32.lib")
#include <windows.h>


class CursorController {
private:
	POINT lpPoint;

public:
	CursorController();
	~CursorController();

	int			getCursorX();
	int			getCursorY();

	bool		update();
	bool		setCursor(int x, int y);
	bool		click();

};

#endif