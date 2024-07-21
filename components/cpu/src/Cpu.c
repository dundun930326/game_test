#ifndef _CPU_C_
#define _CPU_C_

#include "Cpu.h"
#include "Game.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define HALF_POINT_X 135
#define MAX_JOYSTICK 32767
#define MIN_JOYSTICK -32768
#define WIDTH_MODIFY 15
#define HEIGHT_MODIFY 30
#define THRESHOLD 50.0

//w: 80
/*
  4
 2 3
0   1
  5
*/
extern int goalLocs[6][2] = {{35 - 10, 120}, {235 + 10, 120}, {75, 65}, {195, 65}, {120, 10}, {120, 190}};
int16_t blockPosX[3][2] = {{20, 220}, {60, 180}, {120, 120}};
int16_t blockPosY[3] = {170, 115, 60};
extern int8_t add[6];

void cpuLookFor(CPU* obj, Game* game)
{
    double motif;
    motif = goalLocs[obj->CurrentGoal][0] - game->player2->posX;
    //printf("CPU: Motif: %f\n", motif);

    if(motif > THRESHOLD) motif = 1;
    else if(motif * (-1) > THRESHOLD) motif = -1;
    else motif /= THRESHOLD;
    obj->JoystickXSim = (int16_t)(motif * MAX_JOYSTICK);
}

bool cpuFindWeapon(CPU* obj, Game* game)
{
    for(int i = 0; i < 6; i++)
    {
        if(game->weapons[i] != NULL)
        {
            if(game->weapons[i]->owner == NULL)
            {
                obj->CurrentGoal = game->weapons[i]->loc;
                //printf("CPU: find a weapon at loc %d\n", obj->CurrentGoal);
                return true;
            }
        }
    }
    return false;
}

bool cpuCanUseBig(CPU* obj, Game* game)
{
    if(game->player2_powerPer == 101)
    {
        if(game->player2_character_type == 0 || game->player2_character_type == 2 || game->player2_character_type == 4)
        {
            return true;
        }
        else
        {
            if(game->player2->weapon_type != 4)
            {
                return true;
            }
            else return false;
        }
    }
    else return false;
}

void cpuCompute(CPU* obj, Game* game)
{
    if(game->gameState == 2)
    {
        //state 1: use big power
        if(cpuCanUseBig(obj, game))
        {
            if(game->frames % 5 == 0) obj->keyboardSim += add[BIGPOWER];
        }
        //state 2: go for treasure
        else if(game->mTreasure->available)
        {
            //printf("CPU: now state: 1\n");
            if(game->player2->posY >= blockPosY[2])
            {
                if(game->frames % 5 == 1) obj->keyboardSim += add[JUMP];
            }

            if(game->player2->oriY != 1 || game->player2->posY <= 15)
            {
                cpuLookFor(obj, game);
            }
            else
            {
                if(game->player2->posX <= HALF_POINT_X)
                {
                    if(game->player2->posY >= blockPosY[0]) obj->CurrentGoal = 0;
                    else if(game->player2->posY >= blockPosY[1]) obj->CurrentGoal = 2;
                    else if(game->player2->posY >= blockPosY[2]) obj->CurrentGoal = 4;
                }
                else
                {
                    if(game->player2->posY >= blockPosY[0]) obj->CurrentGoal = 1;
                    else if(game->player2->posY >= blockPosY[1]) obj->CurrentGoal = 3;
                    else if(game->player2->posY >= blockPosY[2]) obj->CurrentGoal = 4;
                }
            }
        }
        //state 3: go for weapon
        else if(cpuFindWeapon(obj, game))
        {
            //printf("CPU: now state: 2\n");
            if(obj->CurrentGoal == 3 && game->player2->posY >= blockPosY[0]) obj->CurrentGoal = 1;
            else if(obj->CurrentGoal == 2 && game->player2->posY >= blockPosY[0]) obj->CurrentGoal = 0;
            if(game->frames % 5 == 4)
            {
                obj->keyboardSim += add[JUMP];
            }
            if(game->player2->oriY != 1 || game->player2->posY <= 15)
            {
                cpuLookFor(obj, game);
            }
        }
        //state 4: use item
        else if(game->player1->weapon_type != 4 && game->player2->item == 1)
        {
            //printf("CPU: now state: 3\n");
            if(game->frames % 5 == 2) obj->keyboardSim += add[ITEM];
        }
        //state 5: attack
        else if(game->player2->weapon_type != 4)
        {
            //printf("CPU: now state: 4\n");
            if(game->frames % 5 == 3) obj->keyboardSim += add[ATTACK];
            if(!(game->player1->power && game->player1_character_type == 0))
            {
                obj->JoystickXSim = game->player1->posX - game->player2->posX + (rand() % 50 - 25);
                obj->JoystickYSim = game->player2->posY - game->player1->posY + (rand() % 50 - 25);
            }
            else
            {
                obj->JoystickXSim = (rand() % 50 - 25);
                obj->JoystickYSim = (rand() % 50 - 25);
            }
        }
    }
}

void cpuUpdate(CPU* obj)
{
    obj->keyboardSim = 0;
    obj->JoystickXSim = 0;
    obj->JoystickYSim = 0;
}

CPU* newCPU()
{
    CPU* obj = calloc(1, sizeof(CPU));
    obj->keyboardSim = 0;
    obj->JoystickXSim = 0;
    obj->JoystickYSim = 0;
    obj->CurrentGoal = 1;
    obj->compute = cpuCompute;
    obj->update = cpuUpdate;
    return obj;
}

void deleteCPU(CPU* obj)
{
    if(obj != NULL)
    {
        free(obj);
    }
}

#endif // _CPU_C_