#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "../../engine/include/Engine.h"
#include "../../person/include/Person.h"
#include "../../bullet/include/Bullet.h"



typedef struct game
{
    Person *player1, *player2;
    Engine* gEngine;
    Bullet my_bullet[50];// limitation of bullets : 50
    Bullet enemy_bullet[50];
    int frames;

    RenderObject *background, *ground;
    RenderObject *block_1, *block_2, *block_3, *block_4, *block_5;

    void (*init)(struct game*);
    void (*start)(struct game*);
    void (*readInput)(struct game*);
    void (*checkTreasureChest)(struct game*);
    void (*update)(struct game*);
    void (*render)(struct game*);

}Game;

void gameNew(Game* game_obj);
void gameCheckTreasureChest(Game* game_obj);
void gameIntit(Game* game_obj);
void gameStart(Game* game_obj);
void gameReadInput(Game* game_obj);
void gameUpdate(Game* game_obj);
void gameRender(Game* game_obj);


