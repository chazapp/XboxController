#include "CursorController.hpp"



CursorController::CursorController() {
	GetCursorPos(&lpPoint);
}


CursorController::~CursorController() {
}

int CursorController::getCursorX() {
	return lpPoint.x;
}

int CursorController::getCursorY() {
	return lpPoint.y;
}

bool CursorController::update() {
	GetCursorPos(&lpPoint);
	return true;
}

bool CursorController::setCursor(int x, int y) {
	SetCursorPos(x, y);
	return (true);
}

bool CursorController::click() {
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1, &input, sizeof(INPUT));
	return (true);
}
