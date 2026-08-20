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
    mkfifo("power_pipe", 0666);
    int fd = open("power_pipe",O_WRONLY);
    printf("================================\n");
    printf("          Power Mointor      \n");
    printf("================================\n");

    int status = 0;

    while (status == 0){
        printf("Status: POWER ON\n");
        printf("Enter 1 to simulate power failure\n");
        printf("Enter -1 to quit\n");
        printf(">");
    }

    if(status == 1){
        write(fd,&status,sizeof(status));
        
    }
    close(fd);
    return 0 ;
}