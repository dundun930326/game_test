#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_system.h"
#include "driver/timer.h"
#include "hal/timer_types.h"
#include "hal/timer_hal.h"
#include "client_start.c"
#include "uartFunction.h"
#include "Game.h"

extern Game game;
extern bool isPvP;
extern double startTime;
extern double timer_val_1;
extern void timerSetup(int);
extern void getTime(int, double*);

void startGameAsHost()
{
    printf("starting game as host...\n");
    sendUint8(game.player1_character_type);
    gameStart(&game);

    //timerSetup(3);
    while(1)
    {
        game.readInput(&game);
        game.update(&game);
        game.render(&game);
        
        sendSync();
        while(receiveAvaliable() < 1) {
            bool response = ackSync();
            if (response) {
                //printf("Client responded to sync\n");
                break;
            }
        } 
        gameSendData(&game);
        gameGetData(&game);
        if(game.gameState == 4) break;
    }
    game.startPressed = false;
    while(1)
    {
        game.readInput(&game);
        game.update(&game);
        game.render(&game);
        if(game.gameState == 0) break;
    }
    game.startPressed = false;
}

void hostStart()
{
    // game loop to select character
    //clearBuffer();
    pickCharacter();
    printf("Host character choosed.\n");

    timerSetup(1);
    getTime(1, &timer_val_1);
    startTime = timer_val_1;
    
    while(1){ //Respond of Request 3.
        bool response = acceptRequest();
        if (response) {
            printf("Client has chosen his character\n");
            break;
        }
        getTime(1, &timer_val_1);
        if(timer_val_1 - startTime >= 10)
        {
            isPvP = false;
            backToTitle = true;
            printf("Opponent didn't respond!\n");
            break;
        }
    }
    if(!backToTitle)
    {
        sendInit(); //Send init before game starts.
        startGameAsHost();
    }
    else
    {
        gameReset(&game);
    }
    //clearBuffer();
    isPvP = false;
}
