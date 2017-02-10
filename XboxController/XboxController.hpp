#ifndef XBOX_CONTROLLER_HPP
#define XBOX_CONTROLLER_HPP

#include <windows.h>
#include <Xinput.h>
#pragma comment(lib, "Xinput.lib")
#include "stdafx.h"
#include <iostream>


class XboxController {
public:
	XboxController();
	XboxController(float dzX, float dzY) : _dzX(dzX), _dzY(dzY) {}
	~XboxController();

	bool	setState();

	DWORD getPort() const;
	void setId(DWORD id);

	XINPUT_GAMEPAD *getState();

	bool	checkConnection();
	bool	Refresh();
	bool	testButton(WORD button);
	
	float leftStickX;
	float leftStickY;
	float rightStickX;
	float rightStickY;
	float leftTrigger;
	float rightTrigger;

private:
	DWORD _id;
	DWORD _last_state;
	XINPUT_STATE state;
	float _dzX;
	float _dzY;
};


#endif