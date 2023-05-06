#include <string.h>
#include <stdbool.h>

char* appendNewLine(char *str);

struct pcb{
	char pid;
	FILE *fd;
	char *pgtable;
    // exit된 프로세스인지 판단
    bool isExit = false;
};

// pcb 배열
struct pcb* pcbs;
// 프로세스 개수
int processLength;
// mcku.c에서 사용하는 변수 가져오기 위한 선언
extern struct pcb *current = 0;

// pid 1씩 올려서 current에 넣는 방식
void ku_scheduler(char pid){
    // 무한루프 막기위해서 count 변수 선언
    int count = 0;

    do {
        current = &pcbs[++pid % processLength];
    }while(current->isExit && count++ < processLength);

    // 만약 모든 프로세스가 exit됐다면 current null
    if(count == processLength)
        current = NULL;
}


void ku_pgfault_handler(char pid){
}


void ku_proc_exit(char pid){
    pcbs[pid].isExit = true;
}


void ku_proc_init(int nprocs, char *flist){
    // 프로세스 개수 기억
    processLength = nprocs;
    // 프로세스 파일 리스트 들어있는 파일 불러오기
    FILE *fileList = fopen(flist, "r");
    // 프로세스 개수만큼 pcb 동적할당
    pcbs = malloc(sizeof *pcbs * nprocs);
    // 파일 줄단위로 읽을 때 필요함 - 하지만 안씀
    size_t len = 0;

    for(int i = 0; i < nprocs; i++) {
        // 프로세스 파일명 읽어오기
        char* processFileName = NULL;
        getline(&processFileName, &len, fileList);
        // 마지막 줄은 개행문자가 없어서 추가해주는 과정
        if(i == nprocs - 1) processFileName = appendNewLine(processFileName);

        pcbs[i].fd = fopen(processFileName, "r");
        pcbs[i].pid = i;
        pcbs[i].pgtable = malloc(sizeof *pcbs->pgtable * 16);
    }
}

char* appendNewLine(char *str) {
    char *newstr = malloc(strlen(str) + 2);
    strcpy(newstr, str);
    strcat(newstr, "\n");

    return newstr;
}
