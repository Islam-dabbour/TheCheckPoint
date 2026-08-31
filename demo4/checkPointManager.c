#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>
#include <errno.h>
#include <poll.h>

#define WORKER_COUNT 3

// struct applicationState{
//     int counter;
//     int x;
//     int y;
// };
int main(){
    // mkfifo("game_pipe", 0666);
    // mkfifo("game_response", 0666);
    //printf("111\n");

    // printf("================================\n");
    // printf("          Check Point Manager      \n");
    // printf("================================\n");

    

    // if(status == 1){
    //     int fd2 = open("game_pipe", O_WRONLY);
    //     if (fd2 == -1) {
    //         perror("Could not open game pipe");
    //         return 1;
    //     }
    //     write(fd2,&status,sizeof(status));
    //     close(fd2);
    // }
    // int fd3 = open("game_response", O_RDONLY);
    // int response = 0;
    // read(fd3, &response,sizeof(response));
    // close(fd3);
    // if(response == 1){
    //     printf("The game was saved successfully\n");
    // }
    printf(">> [MANAGER] Starting...\n");
    printf("================================\n");
    printf("       Check Point Manager      \n");
    printf("================================\n");

    pid_t processes[WORKER_COUNT];
    for (int i = 0;i < WORKER_COUNT; i++){
        char pipe_name[64];
        snprintf(pipe_name, sizeof(pipe_name), "game%d_pipe", i + 1);
        mkfifo(pipe_name, 0666);
    }

    for (int i = 0;i < WORKER_COUNT; i++){
        char pipe_name[64];
        snprintf(pipe_name, sizeof(pipe_name), "game%d_response", i + 1);
        mkfifo(pipe_name, 0666);
    }
    for(int i = 0; i < WORKER_COUNT; i++){
        processes[i] = fork();
        if(processes[i] == 0){
            //execlp("gnome-terminal", "gnome-terminal", "--", "bash", "-c", "echo 'Hello from child process!'; exec bash", (char *)NULL);
            printf("[WORKER %d] Started. PID = %d\n",i + 1, getpid());
            //struct applicationState currentState = {.counter = getpid() * 3, .x = getgid() + 3, .y = getegid()};
            char executable[64];
            char gameID[16];
            snprintf(executable, sizeof(executable), "./game%d", i + 1);
            snprintf(gameID, sizeof(gameID), "%d", i + 1);
            execlp("xterm", "xterm", "-fa", "Monospace", "-fs", "12", "-e", executable, gameID, (char *)NULL);

            perror("Could not start game");
            _exit(EXIT_FAILURE);
        }
    }

    printf("\n[MANAGER] All workers created.\n");
    fflush(stdout);

    // for (int i = 0; i < WORKER_COUNT; i++) {
    //     waitpid(processes[i], NULL, 0);
    // }



    int status = 0;
    int fd = open("power_pipe", O_RDONLY);
    if (fd == -1) {
        perror("Could not open power pipe");
        return 1;
    }
    read(fd,&status,sizeof(status));
    close(fd);

    if (status == 1){
        int game_running[WORKER_COUNT] = {0};

        for (int i = 0;i <WORKER_COUNT; i++){
            char pipe_name[64];
            snprintf(pipe_name, sizeof(pipe_name), "game%d_pipe", i + 1);

            int fd2 = open(pipe_name, O_WRONLY | O_NONBLOCK);
            if (fd2 == -1) {
                if (errno == ENXIO) {
                    printf("Game %d is not running.\n", i + 1);
                } else {
                    perror("Could not open game pipe");
                }
                continue;
            }
            write(fd2,&status,sizeof(status));
            close(fd2);
            game_running[i] = 1;
        }

        for (int i = 0;i < WORKER_COUNT; i++){
            if (!game_running[i]) {
                continue;
            }
            
            char pipe_name[64];
            snprintf(pipe_name, sizeof(pipe_name), "game%d_response", i + 1);
            
            int fd3 = open(pipe_name, O_RDONLY | O_NONBLOCK);
            if (fd3 == -1) {
                perror("Could not open response pipe");
                continue;
            }
        
            

            struct pollfd response_pipe = {
                .fd = fd3,
                .events = POLLIN
            };
            int ready = poll(&response_pipe, 1, 5000);
            int response = 0;
            if (ready > 0 && (response_pipe.revents & POLLIN)) {
                read(fd3, &response, sizeof(response));
            } else if (ready == 0) {
                printf("Game %d did not respond.\n", i + 1);
            }
            close(fd3);
            if(response == 1){
                printf("Game %d was saved successfully\n",i + 1);
            }
        }
    }

    return 0;
}