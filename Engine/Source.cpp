
#include <Windows.h>
#include <iostream>
#include <string.h>

int main() {
	RECT desktop;
	HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	int width = desktop.right;
	int height = desktop.left;
	char s[256];

	int x = 4;
	sprintf(s, "There is %d numbers", x);
	OutputDebugString((LPCWSTR)s);
}