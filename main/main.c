#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_system.h"
#include "host_start.c"
#include "Game.h"

//--important variable--//
Game game;
//----//

bool isPvP = false;
// check if player has pressed start
bool startButtonPressed = true;
// check if client wants to accept PVP request
bool playerWantsToStart = true;

//double timer_val_1 = 0;
//double timer_val_2 = 0;
double my_timer_val_3 = 0;
double other_timer_val_3 = 0;
double delay = 0;

// there are 4 timers in esp32, parameter is 0-3 for each timer, timerSetup starts the timer, getTime assigns the time in seconds to timer_val
// ex:
// timerSetup(0);
// double timer_val;
// getTime(0, &timer_val);
// printf("Time: %f\n", timer_val);

timer_config_t config = {
    .divider = 16,  // Clock divider
    .counter_dir = TIMER_COUNT_UP,  // Counting direction
    .counter_en = TIMER_PAUSE,      // Timer state
    .alarm_en = TIMER_ALARM_EN,     // Enable alarm
    .auto_reload = true,            // Auto-reload on alarm
};


void timerSetup(int x)
{
    int i = x / 2;
    int j = x % 2;
    timer_init(i, j, &config);
    timer_set_counter_value(i, j, 0);
    timer_start(i, j);
    printf("Timer%d started\n", x);
}


void getTime(int x, double *timer_val)
{
    int i = x / 2;
    int j = x % 2;
    timer_get_counter_time_sec(i, j, timer_val);
}

void startPVCGame() {
    //printf("Starting game in PVC mode...\n");
    game.readInput(&game);
    game.update(&game);
    game.render(&game);
    vTaskDelay((2000/60)/portTICK_PERIOD_MS);
}

void app_main(void) {
    uartSetup();
    setTimeoutMs(100);
    clearBuffer();
    vTaskDelay(5000/portTICK_PERIOD_MS);

    gameNew(&game);
    game.init(&game);
    printf("Game init success!!!\n");
    
    while(!isPvP)
    {
        if((game.mode == PVP_MASTER || game.mode == PVP_SLAVE) && game.startPressed == true)
        {
            isPvP = true;
            game.startPressed = false;
        }
        else
        {
            startPVCGame();
        }
    }

    while (true)
    {
        // look for requests, if found request, start game as client. If not, check if start button is pressed
        // if start button is pressed, start the game as host
        if(receiveAvaliable() > 0)
        {
            bool foundRequest = acceptRequest();
            if (foundRequest) {
                if(playerWantsToStart) {
                    printf("hello I am client!\n");
                    clientStart();
                } 
            } else if(startButtonPressed) {
                    printf("hello I am host!\n");
                    hostStart();
            }
        }
    }
}
