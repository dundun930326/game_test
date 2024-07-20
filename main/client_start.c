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
    while(game.gameState != 4 || !game.startPressed)
    {
        game.readInput(&game);
        game.update(&game);
        game.render(&game);
        while(1) {
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
    }
    game.startPressed = false;
}

// run this when client accepts request
void clientStart()
{
    // tells host you have accepted request
    clearBuffer();
    sendRequest();
    game.mode = PVP_SLAVE;

    // game loop to select character
    pickCharacter();
    printf("Client character choosed.\n");
    // tell host you are ready
    sendRequest();

    while(1) {
        bool response = ackInit();
        if (response) {
            printf("Client has prepare to start game!\n");
            break;
        }
    }
    clearBuffer();
    
    startGameAsClient();
    isPvP = false;
}
