// Struct to holder process times.
typedef struct
{
    FILETIME lpCreationTime;
    FILETIME lpExitTime;
    FILETIME lpKernelTime;
    FILETIME lpUserTime;
} WProcessTimes;

DWORD criarProcesso(LPCTSTR lpAppName);

HANDLE getProcessHandle(DWORD processId);

BOOL matarProcesso(DWORD processId);

void printProcess(DWORD processId);

BOOL listAllProcess();

DWORD getProcessPriority(DWORD processId);

DWORD getCurrentProcess();

IO_COUNTERS getIOCounts(DWORD processId);

void getProcessTimes(DWORD processId, DWORD *creationTime, DWORD *userTime);