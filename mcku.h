#include <string.h>
char* appendNewLine(char *str);

struct pcb{
	char pid;
	FILE *fd;
	char *pgtable;
};

struct pcb* pcbs;

void ku_scheduler(char pid){

	/* Your code here */

}


void ku_pgfault_handler(char pid){

	/* Your code here */

}


void ku_proc_exit(char pid){

	/* Your code here */

}


void ku_proc_init(int nprocs, char *flist){
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
