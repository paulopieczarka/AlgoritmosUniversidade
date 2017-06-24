#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <psapi.h>

#include "api.h"

DWORD criarProcesso(LPCTSTR lpAppName)
{
    STARTUPINFO lpStartupInfo;
    ZeroMemory(&lpStartupInfo, sizeof(STARTUPINFO));
    lpStartupInfo.cb = sizeof(lpStartupInfo);

    PROCESS_INFORMATION lpProcessInfo;
    ZeroMemory(&lpProcessInfo, sizeof(LPPROCESS_INFORMATION));
    BOOL result = TRUE;

    result = CreateProcess(
        lpAppName,
        NULL,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &lpStartupInfo,
        &lpProcessInfo
    );

    printf(" (3) ");

    if(result == TRUE)
    {
        printf(" Processo criado!\n");
        return lpProcessInfo.dwProcessId;
    }
    else {
        printf(" Processo NAO criado (%d)!\n", GetLastError());  
    }

    return -1;
}

HANDLE getProcessHandle(DWORD processId)
{
    HANDLE hProcess;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

    //Check for errors.
    if(hProcess == NULL){
        printf("\n Cannot Open Process (%d).\n\n", GetLastError());
    }

    return hProcess;
}

BOOL matarProcesso(DWORD processId)
{
    HANDLE hProcess = getProcessHandle(processId);
    return TerminateProcess(hProcess, 0);
}

void printProcess(DWORD processId)
{
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
    HANDLE hProcess = getProcessHandle(processId);

    if(hProcess != NULL)
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if(EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)){
            GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName)/sizeof(TCHAR));
        }
    }

    printf(" [%u\t%s]\n", processId, szProcessName);

    CloseHandle(hProcess);
}

BOOL listAllProcess()
{
    DWORD aProcesses[1024], cbNeeded;
    if(EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded) == FALSE){
        return FALSE;
    }

    // Calculate how many process identifiers were returned.
    DWORD cProcesses;
    cProcesses = cbNeeded / sizeof(DWORD);

    // Print the name and process identifier for each process.
    int i;
    for(i=0; i < cProcesses; i++){
        printProcess(aProcesses[i]);
    }

    return TRUE;
}

DWORD getProcessPriority(DWORD processId)
{
    HANDLE hProcess = getProcessHandle(processId);
    return GetPriorityClass(hProcess);
}

IO_COUNTERS getIOCounts(DWORD processId)
{
    IO_COUNTERS ioCounter;
    ZeroMemory(&ioCounter, sizeof(IO_COUNTERS));

    HANDLE hProcess = getProcessHandle(processId);

    if(GetProcessIoCounters(hProcess, &ioCounter) == FALSE){
        printf("\n Cannot get process I/O counter (%d).\n\n", GetLastError());    
    }

    return ioCounter;
}

DWORD getCurrentProcess()
{
    return GetCurrentProcessId();
}

void getProcessTimes(DWORD processId, DWORD *creationTime, DWORD *userTime)
{
    FILETIME a, b;
    FILETIME cft; // Creation file time.
    FILETIME uft; // User file time..
    HANDLE hProcess = getProcessHandle(processId);

    if(GetProcessTimes(hProcess, &cft, &a, &b, &uft) == FALSE){
        printf("\n Cannot get process times (%d).\n\n", GetLastError());  
    }
    else
    {
        *creationTime = cft.dwLowDateTime;
        *userTime = uft.dwLowDateTime;
    }
}