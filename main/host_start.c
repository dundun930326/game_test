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

void startGameAsHost()
{
    printf("starting game as host...\n");
    sendUint8(game.player1_character_type);
    gameStart(&game);

    //timerSetup(3);
    while(game.gameState != 4 || !game.startPressed)
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
    }
    game.startPressed = false;
}

void hostStart()
{
    //clearBuffer();
    sendRequest();
    game.mode = PVP_MASTER;

    // wait for client to accept request
    while(1) {
        printf("Waiting...\n");
        bool response = acceptRequest();
        if (response) {
            printf("Client responded to request\n");
            break;
        }
    }

    // game loop to select character
    //clearBuffer();
    pickCharacter();
    printf("Host character choosed.\n");

    // wait for client to select character
    while(1)   {
        bool response = acceptRequest();
        if (response) {
            printf("Client has chosen his character\n");
            break;
        }
    }
    //clearBuffer();

    sendInit();
    startGameAsHost();
    isPvP = false;
}
