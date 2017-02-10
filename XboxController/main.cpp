// main.cpp : définit le point d'entrée pour l'application console.
//

#include "XboxController.hpp"
#include "CursorController.hpp"
#include <chrono>
#include <thread>


int				main() {
	XboxController xb;
	CursorController cursor;

	if (xb.setState() == true) {
		std::cout << "XB true" << std::endl;
	}
	else {
		std::cout << "XB false" << std::endl;
		return 0;
	}
	bool _end = true;
	bool _abutton = false;
	while (_end == true) {
		if (xb.Refresh() == true && cursor.update()) {
			cursor.setCursor(cursor.getCursorX() + xb.leftStickX, cursor.getCursorY() - xb.leftStickY);
			if (xb.testButton(XINPUT_GAMEPAD_START) == true)
				break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
    return 0;
}

