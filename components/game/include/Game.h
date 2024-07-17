#ifndef _GAME_H_
#define _GAME_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "Engine.h"
#include "Person.h"
#include "Bullet.h"
#include "Treasure.h"
#include "Weapon.h"
#include "Cpu.h"

enum keyFunc{
    IDLE1 = 0,
    IDLE2 = 1,
    PAUSE = 2,
    JUMP = 3,
    ATTACK = 4,
    ITEM = 5
};

typedef struct cpu CPU;

typedef struct game
{
    Person *player1, *player2;
    Engine *gEngine;
    
    // limitation of bullets : 20
    Bullet *my_bullet[20];
    Bullet *enemy_bullet[20];

    Weapon *weapons[6];

    Treasure *mTreasure;

    CPU *mCPU;

    //0: sasge, 1: musk, 2: english, 3: pie, 4: anya
    uint8_t player1_character_type;
    uint8_t player2_character_type;

    //0: pvc, 1: pvp (self-master), 2: pvp (self-slave)
    uint8_t mode;

    //0: title screen, 1: select screen, 2: maingame screen, 3: pause screen, 4: gameover screen
    uint8_t gameState;
    int frames;

    RenderObject *background, *ground;
    RenderObject *previews[5];
    RenderObject *blocks[5];
    RenderObject *HP[2][3];
    RenderObject *result;

    void (*init)(struct game*);
    void (*start)(struct game*);
    void (*readInput)(struct game*);
    //void (*checkTreasureChest)(struct game*);
    void (*update)(struct game*);
    void (*render)(struct game*);
}Game;

//--functions for internal usage only--//
void gameLoadPerson(Game* game_obj);
void gameSelect(Game* game_obj);
void gameStart(Game* game_obj);
void gameAddNewWeapon(Game* game_obj);
//----//

void gameNew(Game* game_obj);
//void gameCheckTreasureChest(Game* game_obj);
void gameInit(Game* game_obj);
void gameStart(Game* game_obj);
void gameReadInput(Game* game_obj);
void gameUpdate(Game* game_obj);
void gameRender(Game* game_obj);


#endif // _GAME_H_