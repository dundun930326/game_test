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
#include "client_start.c"
#include "uartFunction.h"
#include "Game.h"

extern Game game;

double timer_val_1 = 0;
double timer_val_2 = 0;

void startGameAsHost()
{
    printf("starting game as host...\n");
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

void hostStart()
{
    //clearBuffer();
    sendRequest();
    game.mode = PVP_MASTER;

    // wait for client to accept request
    while(1) {
        bool response = acceptRequest();
        if (response) {
            printf("Client responded to request\n");
            break;
        }
    }
    //clearBuffer();

    // game loop to select character
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
}
