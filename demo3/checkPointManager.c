#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>


int main(){

    int fd = open("power_pipe", O_RDONLY);
    if (fd == -1) {
        perror("Could not open power pipe");
        return 1;
    }
    printf("================================\n");
    printf("          Check Point Manager      \n");
    printf("================================\n");

    int status = 0;

    read(fd,&status,sizeof(status));

    printf("POWER OFF\n %d",status);


    return 0;
}