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
#include "uartFunction.h"
#include "Game.h"

extern Game game;
extern bool isPvP;
extern bool backToTitle;
extern double startTime;
extern double timer_val_1;
extern void timerSetup(int);
extern void getTime(int, double*);

void pickCharacter()
{
    printf("Picking character...\n");
    gameSelect(&game);
    while(!game.startPressed)
    {
        game.readInput(&game);
        game.update(&game);
        game.render(&game);
        vTaskDelay((2000/60)/portTICK_PERIOD_MS);
    }
    game.startPressed = false;
}

void startGameAsClient()
{
    printf("Starting game as client...\n");
    sendUint8(game.player1_character_type);
    gameStart(&game);
    while(1)
    {
        game.readInput(&game);
        game.update(&game);
        game.render(&game);
        while(receiveAvaliable() < 1) {
            bool response = ackSync();
            if (response) {
                //printf("Host asked to sync\n");
                break;
            }
        }
        sendSync();  
        gameSendData(&game);
        gameGetData(&game); 
        //vTaskDelay((2000/60)/portTICK_PERIOD_MS);
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

// run this when client accepts request
void clientStart()
{
    // game loop to select character
    //clearBuffer();
    pickCharacter();
    printf("Client character choosed.\n");
    
    sendRequest(); //Request 3: tell host you are ready

    timerSetup(1);
    getTime(1, &timer_val_1);
    startTime = timer_val_1;
    while(1) { //Ack init before game starts.
        bool response = ackInit();
        if (response) {
            printf("Client has prepare to start game!\n");
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
        startGameAsClient();
    }
    else
    {
        gameReset(&game);
    }
    isPvP = false;
}
