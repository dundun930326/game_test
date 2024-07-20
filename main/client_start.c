#include <stdio.h>
#include <inttypes.h>
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
    gameStart(&game);
    while(!game.startPressed)
    {
        game.readInput(&game);
        game.update(&game);
        game.render(&game);
        vTaskDelay((2000/60)/portTICK_PERIOD_MS);
    }
    game.startPressed = false;
}

// run this when client accepts request
void clientStart()
{
    // tells host you have accepted request
    sendRequest();
    game.mode = PVP_SLAVE;
    //clearBuffer();
    // game loop to pick character
    pickCharacter();
    printf("Client character choosed.\n");
    // tell host you are ready
    sendRequest();
    //clearBuffer();

    while(1) {
        bool response = ackInit();
        if (response) {
            printf("Client has prepare to start game!\n");
            break;
        }
    }
    clearBuffer();
    
    startGameAsClient();
}
