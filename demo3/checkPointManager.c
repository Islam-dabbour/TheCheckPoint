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
    mkfifo("game_pipe", 0666);
    mkfifo("game_response", 0666);
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
    close(fd);

    if(status == 1){
        int fd2 = open("game_pipe", O_WRONLY);
        if (fd2 == -1) {
            perror("Could not open game pipe");
            return 1;
        }
        write(fd2,&status,sizeof(status));
        close(fd2);
    }
    int fd3 = open("game_response", O_RDONLY);
    int response = 0;
    read(fd3, &response,sizeof(response));
    close(fd3);
    if(response == 1){
        printf("The game was saved successfully\n");
    }


    return 0;
}