#include "XboxController.hpp"

XboxController::XboxController() {
	this->_id = 0;
	this->_dzX = 0.10f;
	this->_dzY = 0.10f;
}

XboxController::~XboxController() {

}

bool XboxController::setState() {
	ZeroMemory(&(this->state), sizeof(XINPUT_STATE));
	
	this->_last_state = XInputGetState(this->_id, &(this->state));
	if (this->_last_state == ERROR_SUCCESS) {
		return true;
	}
	else {
		perror("XInputGetState:");
	}
	return false;
}

DWORD		XboxController::getPort() const {
	return (this->_id + 1);
}

void		XboxController::setId(DWORD id) {
	this->_id = id;
}

XINPUT_GAMEPAD * XboxController::getState() {
	return &state.Gamepad;
}

bool XboxController::checkConnection() {
	int controllerId = -1;
	for (DWORD i = 0; i < XUSER_MAX_COUNT && controllerId == -1; i++) {
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		if (XInputGetState(i, &state) == ERROR_SUCCESS)
			controllerId = i;
	}
	this->_id = controllerId;
	return controllerId != -1;
}

bool XboxController::testButton(WORD button) {
	return (state.Gamepad.wButtons & button) != 0;
}

bool	XboxController::Refresh() {
	if (this->_id == -1)
		checkConnection();
	if (_id != -1) {
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		if (XInputGetState(_id, &state) != ERROR_SUCCESS) {
			_id = -1;
			return false;
		}
		float normLX = fmaxf(-1, (float)state.Gamepad.sThumbLX / 32767);
		float normLY = fmaxf(-1, (float)state.Gamepad.sThumbLY / 32767);

		leftStickX = (abs(normLX) < _dzX ? 0 : (abs(normLX) - _dzX) * (normLX / abs(normLX)));
		leftStickY = (abs(normLY) < _dzY ? 0 : (abs(normLY) - _dzY) * (normLY / abs(normLY)));

		if (_dzX > 0) leftStickX *= 1 / (1 - _dzX);
		if (_dzY > 0) leftStickY *= 1 / (1 - _dzY);

		float normRX = fmaxf(-1, (float)state.Gamepad.sThumbRX / 32767);
		float normRY = fmaxf(-1, (float)state.Gamepad.sThumbRY / 32767);

		rightStickX = (abs(normRX) < _dzX ? 0 : (abs(normRX) - _dzX) * (normRX / abs(normRX)));
		rightStickY = (abs(normRY) < _dzY ? 0 : (abs(normRY) - _dzY) * (normRY / abs(normRY)));

		if (_dzX > 0) rightStickX *= 1 / (1 - _dzX);
		if (_dzY > 0) rightStickY *= 1 / (1 - _dzY);

		leftTrigger = (float)state.Gamepad.bLeftTrigger / 255;
		rightTrigger = (float)state.Gamepad.bRightTrigger / 255;

		return true;
	}
	return false;
}