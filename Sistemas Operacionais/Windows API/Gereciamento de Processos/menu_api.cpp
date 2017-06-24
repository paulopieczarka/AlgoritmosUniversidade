#include <stdio.h>
#include <stdlib.h>

#include "menu_api.h"

int currentIndex = 0;
WatchProcess processList[16];

void menu()
{
    system("cls");

    int cmd = 0;
    printProcessList();
    printf(" [1] Novo processo.\t\t [2] Finalizar processo.\n");
    printf(" [2] Informacoes processo.\t [3] Infor. deste processo.\n");
    printf(" [4] Listar processos.\t\t [5] I/O Watcher.\n");
    printf(" [6] Mostrar prioridade.\t [7] Mostrar tempos.\n");
    printf(" [8] NSFW.\t\t\t [9] Matar todos os processos.\n");
    printf("\n [0] As vezes finaliza o processo.\t\t.\n\n Escolha:");

    scanf("%d", &cmd);
    getchar();

    if(cmd == 1){
        menuNewProcess();
    }
    else if(cmd == 2){
        menuProcessInfo();
    }
    else if(cmd == 3){
        menuCurrentProcessInfo();
    }
    else if(cmd == 4)
    {
        system("cls");
        listAllProcess();
        getchar();
    }
    else if(cmd == 5){
        menuProcessIOCounter();
    }
    else if(cmd == 6){
        menuProcessPriority();
    }
    else if(cmd == 7){
        menuProcessTimes();
    }
    else if(cmd == 8)
    {
        printf(" There you go..\n\n");
        printf("\t ( . Y . )\t\n\n");
        getchar();
    }
    else if(cmd == 9)
    {
        killProcessList();
    }

    if(cmd != 0){
        menu();
    }
    else // Exit.
    {
        // Kill all created processes.
        killProcessList();
    }
}

void menuNewProcess()
{
    printf("\n ~ CRIAR UM PROCESSO ~ \n\n");

    char path[64];
    DWORD procId;
    ZeroMemory(&procId, sizeof(DWORD));

    printf(" Caminho do programa (.exe, .bat): ");
    scanf("%s", path);
    
    procId = criarProcesso(path);
    printf(" NOTEPAD ID: %u.\n", procId);

    if(procId != -1){
        addProcessToList(path, procId);
    }

    getchar();
}

void menuKillProcess()
{
    printf("\n ~ MATAR UM PROCESSO ~ \n\n");

    DWORD procId; ZeroMemory(&procId, sizeof(DWORD));
    printf(" Informe a PID do processo: ");
    scanf("%d", &procId);
    getchar();

    matarProcesso(procId);
}

void menuProcessPriority()
{
    printf("\n ~ PRIORIDADE DE UM PROCESSO ~ \n\n");

    DWORD procId; ZeroMemory(&procId, sizeof(DWORD));
    printf(" Informe a PID do processo: ");
    scanf("%d", &procId);
    getchar();

    DWORD pri = getProcessPriority(procId);
    printf("\n PRIORITY: %u.\n", pri);

    getchar();
}

void menuProcessTimes()
{
    printf("\n ~ TEMPOS DE PROCESSO ~ \n\n");

    DWORD procId; ZeroMemory(&procId, sizeof(DWORD));
    printf(" Informe a PID do processo: ");
    scanf("%d", &procId);
    getchar();

    DWORD ct, ut;
    getProcessTimes(procId, &ct, &ut);
    printf("\n Process Times: creation=%u, running=%u.\n", ct, ut);

    getchar();
}

void menuProcessIOCounter()
{
    printf("\n ~ I/O DE PROCESSO ~ \n\n");

    DWORD procId; ZeroMemory(&procId, sizeof(DWORD));
    printf(" Informe a PID do processo: ");
    scanf("%d", &procId);
    getchar();

    IO_COUNTERS ioCounter = getIOCounts(15724);
    printf("\n I/Os: reads=%d, writes=%d.\n", 
            (int)ioCounter.ReadOperationCount,
            (int)ioCounter.WriteOperationCount
        );

    getchar();
}

void menuProcessInfo()
{
    printf("\n ~ INFORMACOES DE PROCESSO ~ \n\n");

    DWORD procId; ZeroMemory(&procId, sizeof(DWORD));
    printf(" Informe a PID do processo: ");
    scanf("%d", &procId);
    getchar();

    printProcess(procId);

    getchar();
}

void menuCurrentProcessInfo()
{
    printf("\n ~ INFORMACOES DESTE PROCESSO ~ \n\n");

    DWORD procId; ZeroMemory(&procId, sizeof(DWORD));
    procId = getCurrentProcess();
    
    printProcess(procId);

    getchar();
}

/* PROCESS LIST */

void addProcessToList(char path[64], DWORD pid)
{
    strncpy(processList[currentIndex].name, path, 64);
    processList[currentIndex].pid = pid;
    currentIndex++;
}

void killProcessList()
{
    printf("\n\n Matando os processos..\n");

    int i = 0;
    for(; i < currentIndex; i++){
        matarProcesso(processList[i].pid);
    }

    currentIndex = 0;
    printf(" Done.\n");
}

void printProcessList()
{
    printf("\n PROCESSOS MONITORADOS: \n");

    if(currentIndex == 0){
        printf("  - Nenhum processo.\n");
    }

    int i = 0;
    for(; i < currentIndex; i++){
        printf("  [%u]\t %s\n", processList[i].pid, processList[i].name);
    }

    printf("\n");
}