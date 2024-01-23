#include "NtProcess.h"
#include <Windows.h>
#include <winternl.h>
#pragma comment(lib, "ntdll.lib")

EXTERN_C NTSTATUS NTAPI RtlAdjustPrivilege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
EXTERN_C NTSTATUS NTAPI NtSetInformationProcess(HANDLE, ULONG, PVOID, ULONG);

bool NtProcess::SetCritical() {

    BOOLEAN bl;
    ULONG BreakOnTermination = 1;
    if (!NT_SUCCESS(RtlAdjustPrivilege(20, TRUE, FALSE, &bl))) return false;
    NtSetInformationProcess((HANDLE)-1, 0x1d, &BreakOnTermination, sizeof(ULONG));
    return true;
}