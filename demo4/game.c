#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <pthread.h>


struct GameState {
    int level;
    int score;
    int health;
    int x;
    int y;
    time_t checkpointTime;
};

struct GameState currentGameState;
int gameRunning = 1;

void startGame(){
    currentGameState.level = 1;
    currentGameState.health = 100;
    currentGameState.score = 0;
    currentGameState.x = 10;
    currentGameState.y = 10;
    currentGameState.checkpointTime = time(NULL);
}

void fightAnEnemy(){
    currentGameState.score++;
    currentGameState.health--;
}

void heal(){

}

void load_checkPoint(){
    int file = open("checkpoint.bin", O_RDONLY, 0644);
    read(file, &currentGameState, sizeof(currentGameState));
    close(file);
}

void save_checkPoint() {

    currentGameState.checkpointTime = time(NULL);

    int file = open("checkpoint.bin",
                    O_WRONLY | O_CREAT | O_TRUNC,
                    0644);

    if (file == -1) {
        printf("Could not save checkpoint.\n");
        return;
    }

    write(file, &currentGameState, sizeof(currentGameState));

    close(file);

    //printf("Checkpoint saved!\n");
}

void* saveTimer(void* arg){

    while(gameRunning){

        save_checkPoint();

        for(int i = 0; i < 30 && gameRunning; i++){
            sleep(1);
        }
    }

    return NULL;
}

void* urgentSave(void* arg){
    while(gameRunning){
        int fd = open("game_pipe", O_RDONLY);
        int urgentSave = 0;
        read(fd,&urgentSave,sizeof(urgentSave));
        close(fd);
        if(urgentSave == 1){
            
            save_checkPoint();

            int response = 1;
            int fd2 = open("game_response",O_WRONLY);
            write(fd2,&response,sizeof(response));
            close(fd2);

            if (response == 1) {

                printf("Urgent checkpoint saved. Stopping game...\n");
                gameRunning = 0;

                }
        }
    }   
}

int main(){
    pthread_t tid2;
    pthread_create(&tid2,NULL, urgentSave,NULL);
    printf("== WELCOME TO DEMO 1 ==\n");
    printf("-- do you want to start from a new save ? YES/1 - NO/0\n");

    int saveChoice = -1;
    scanf("%d",&saveChoice);

    if(saveChoice == 1){
        printf("Starting new game...\n");
        startGame();
    }else{
        int file = open("checkpoint.bin", O_RDONLY);
        if(file == -1){
            printf("Couldnt find a check point to load from...\n");
            printf("Starting new game..\n");
            startGame();
        }else{
            close(file);
            load_checkPoint();
            printf("Checkpoint found.\n");

            printf("Last checkpoint: %s",ctime(&currentGameState.checkpointTime));
        }
    }
    

    int option = 0;
    pthread_t tid;
    pthread_create(&tid, NULL, saveTimer, NULL);

    while(option != -1 && gameRunning){
        
        printf("========== DEMO 1 ==========\n");
        printf("\n");
        printf("Level: %d \n",currentGameState.level);
        printf("Score: %d \n",currentGameState.score);
        printf("Health: %d \n",currentGameState.health);
        printf("============================\n");
        printf("-- Enter 1 to move to the right --\n");
        printf("-- Enter 2 to move to the left --\n");
        printf("-- Enter 3 to attack an enemy --\n");
        printf("-- Enter 4 to heal --\n");
        printf("============================\n");
        printf("-- ENTER -1 TO LEAVE THE GAME --\n");

        scanf("%d",&option);

        switch (option)
        {
        case 3:
            fightAnEnemy();
            break;
        case -1:
            gameRunning = 0;
            break;
            
        default:
            break;
        }

        
    }

    // printf("-- Do you which to save the game ? YES/1 - NO/0\n");
    // int save = -1;
    // scanf("%d",&save);

    // if(save == 1){
    //     save_checkPoint();
    // }
    gameRunning = 0;
    pthread_join(tid,NULL);
    pthread_join(tid2,NULL);
    return 0;
}