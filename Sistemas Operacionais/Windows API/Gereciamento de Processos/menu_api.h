typedef struct _WATCH_PROCESS_
{
    char name[64];
    DWORD pid;
} WatchProcess;

void menu();

void menuNewProcess();
void menuKillProcess();
void menuProcessPriority();
void menuProcessTimes();
void menuProcessIOCounter();
void menuProcessInfo();
void menuCurrentProcessInfo();

void printProcessList();
void killProcessList();
void addProcessToList(char path[64], DWORD pid);