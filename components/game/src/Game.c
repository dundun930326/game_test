#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "Game.h"
#include "people.h"
#include "weapon.h"
#include "Engine.h"

extern const uint16_t Sasge[6][2500];
extern const uint16_t Musk[6][2500];
extern const uint16_t English[6][2500];
extern const uint16_t Pie[6][2500];
extern const uint16_t Anya[6][2500];
extern const uint16_t block[];
extern const uint16_t backgroundImage[];
const uint16_t bulletImage[] = {0,0,0,0,0,0,0,0,0};

const char* ind[6] = {"1", "2", "3", "4", "5", "6"};
const uint16_t (*characters[5])[2500] = {Sasge, Musk, English, Pie, Anya};

//--functions for internal usage only--//
void gameLoadPerson(Game* game_obj)
{
    char name[10] = "person1-";
    for(int i = 0; i < 6; i++)
    {
        strcat(name, ind[i]);
        Engine_Render_addImage(game_obj->gEngine, name, characters[game_obj->player1_character_type][i], 50, 50);
        strcpy(name, "person1-");
    }
    strcpy(name, "person2-");
    for(int i = 0; i < 6; i++)
    {
        strcat(name, ind[i]);
        Engine_Render_addImage(game_obj->gEngine, name, characters[game_obj->player2_character_type][i], 50, 50);
        strcpy(name, "person2-");
    }
}

void gameSelect(Game* game_obj)
{
    for(int i = 0; i < 5; i++)
    {
        Engine_Render_addObject(game_obj->gEngine, game_obj->previews[i]);
    }
}

void gameStart(Game* game_obj)
{
    printf("Game starting...\n");

    for(int i = 0; i < 5; i++)
    {
        Engine_Render_removeObject(game_obj->gEngine, game_obj->previews[i]);
    }
    for(int i = 0; i < 5; i++)
    {
        Engine_Render_addObject(game_obj->gEngine, game_obj->blocks[i]);
    }
    gameLoadPerson(game_obj);
    game_obj->player1 = newPerson(game_obj->gEngine, 0, 190);
    Engine_Render_addObject(game_obj->gEngine, game_obj->player1->mRenderObject);
    game_obj->player2 = newPerson(game_obj->gEngine, 270, 190);
    Engine_Render_addObject(game_obj->gEngine, game_obj->player2->mRenderObject);
    printf("Game start!\n");
}

void gameCheckTreasureChest(Game* game_obj)
{
    // unused;
}
//----//

void gameNew(Game* game_obj){
    game_obj->gameState = 0;
    game_obj->frames = 0;
    game_obj->player1_character_type = 0;
    game_obj->player2_character_type = 0;
    game_obj->mode = 0;
    game_obj->gEngine = newEngine();
    game_obj->init = gameInit;
    game_obj->checkTreasureChest = gameCheckTreasureChest;
    game_obj->start = gameStart;
    game_obj->readInput = gameReadInput;
    game_obj->update = gameUpdate;
    game_obj->render = gameRender;
}

<<<<<<< HEAD
void gameIntit(Game* game_obj){
    
    int player1_character_type = 0;
    int player2_character_type = 0;
    //--Choose Character--//





    //load charactor image
    //0->sasge
    if(player1_character_type == 0){
        extern const uint16_t Anya_left[6][2500];
        Engine_Render_addImage(game_obj->gEngine, "person1", Anya_left[0], 50, 50);
        Engine_Render_addImage(game_obj->gEngine, "person2", Anya_left[1], 50, 50);
    }
    //1->
    //...




    //----//


    //--Load Resources--//
    extern const uint16_t weapon_right[3][2500];
    Engine_Render_addImage(game_obj->gEngine, "weapon1", weapon_left[1], 50, 50);
=======
void gameInit(Game* game_obj){
    //--Load Resources--//
>>>>>>> 52d7500 (design gameflow)
    Engine_Render_addImage(game_obj->gEngine, "block", block, 80, 15);
    Engine_Render_addImage(game_obj->gEngine, "background", backgroundImage, 320, 240);
    Engine_Render_addImage(game_obj->gEngine, "ground", block, 320, 15);
<<<<<<< HEAD
    Engine_Render_addImage(game_obj->gEngine, "background", backgroundImage, 320, 240);
=======
    Engine_Render_addImage(game_obj->gEngine, "bullet", bulletImage, 3, 3);
<<<<<<< HEAD
    Engine_Render_addImage(game_obj->gEngine, "preview1-1", characters[0][0], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "preview2-1", characters[1][0], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "preview3-1", characters[2][0], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "preview4-1", characters[3][0], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "preview5-1", characters[4][0], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "preview1-2", characters[0][5], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "preview2-2", characters[1][5], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "preview3-2", characters[2][5], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "preview4-2", characters[3][5], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "preview5-2", characters[4][5], 50, 50);
>>>>>>> 52d7500 (design gameflow)
=======
    Engine_Render_addImage(game_obj->gEngine, "preview1-1", characters[0][0][0], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "preview2-1", characters[0][1][0], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "preview3-1", characters[0][2][0], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "preview4-1", characters[0][3][0], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "preview5-1", characters[0][4][0], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "preview1-2", characters[0][0][5], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "preview2-2", characters[0][1][5], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "preview3-2", characters[0][2][5], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "preview4-2", characters[0][3][5], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "preview5-2", characters[0][4][5], 50, 50);
    for(int i = 0; i < 10; i++)
    {
        Engine_Render_addImage(game_obj->gEngine, ind[i], bitmap_allArray[i], 50, 50);
    }
>>>>>>> 6b98f3b (GameState control, bullets, and second person)
    Engine_Audio_addAudio(game_obj->gEngine, "/spiffs/adf_music.mp3");
    Engine_Audio_addAudio(game_obj->gEngine, "/spiffs/gunshot.mp3");
    Engine_Audio_addAudio(game_obj->gEngine, "/spiffs/metalpipe.mp3");
    Engine_Audio_addAudio(game_obj->gEngine, "/spiffs/potai.mp3");
    Engine_Audio_addAudio(game_obj->gEngine, "/spiffs/yamete.mp3");
    Engine_Audio_addAudio(game_obj->gEngine, "/spiffs/guncock.mp3");
    Engine_Audio_addAudio(game_obj->gEngine, "/spiffs/bipbop.mp3");
    Engine_Audio_setVolume(game_obj->gEngine, 0);
    
    game_obj->background = Engine_Render_newObject(game_obj->gEngine, "background", 0, 0, 1);
    game_obj->ground = Engine_Render_newObject(game_obj->gEngine, "ground", 0, 225, 1);
<<<<<<< HEAD
    game_obj->block_1 = Engine_Render_newObject(game_obj->gEngine, "block", 20, 170, 1);
    game_obj->block_2 = Engine_Render_newObject(game_obj->gEngine, "block", 220, 170, 1);
    game_obj->block_3 = Engine_Render_newObject(game_obj->gEngine, "block", 60, 115, 1);
    game_obj->block_4 = Engine_Render_newObject(game_obj->gEngine, "block", 180, 115, 1);
    game_obj->block_5 = Engine_Render_newObject(game_obj->gEngine, "block", 120, 60, 1);
    
    //----//

}

void gameCheckTreasureChest(Game* game_obj)
{
    // unused;
}

void gameStart(Game* game_obj){
    Engine_Render_addObject(game_obj->gEngine, game_obj->background);
    Engine_Render_addObject(game_obj->gEngine, game_obj->block_1);
    Engine_Render_addObject(game_obj->gEngine, game_obj->block_2);
    Engine_Render_addObject(game_obj->gEngine, game_obj->block_3);
    Engine_Render_addObject(game_obj->gEngine, game_obj->block_4);
    Engine_Render_addObject(game_obj->gEngine, game_obj->block_5);

    game_obj->player1 = newPerson(game_obj->gEngine, 1, 190);
    Engine_Render_addObject(game_obj->gEngine, game_obj->player1->mRenderObject);
    
=======
    game_obj->blocks[0] = Engine_Render_newObject(game_obj->gEngine, "block", 20, 170, 1);
    game_obj->blocks[1] = Engine_Render_newObject(game_obj->gEngine, "block", 220, 170, 1);
    game_obj->blocks[2] = Engine_Render_newObject(game_obj->gEngine, "block", 60, 115, 1);
    game_obj->blocks[3] = Engine_Render_newObject(game_obj->gEngine, "block", 180, 115, 1);
    game_obj->blocks[4] = Engine_Render_newObject(game_obj->gEngine, "block", 120, 70, 1);
    for(int i = 0; i < 5; i++)
    {
        char name[11] = "preview";
        strcat(name, ind[i]);
        if(game_obj->player1_character_type != i) strcat(name, "-1");
        else strcat(name, "-2");
        game_obj->previews[i] = Engine_Render_newObject(game_obj->gEngine, name, 35 + 50 * i, 95, 1);
        strcpy(name, "preview");
    }
    //----//

    //--Add object to the render list for the first time--//
    Engine_Render_addObject(game_obj->gEngine, game_obj->background);
    Engine_Render_addObject(game_obj->gEngine, game_obj->ground);
    //
>>>>>>> 52d7500 (design gameflow)
}

void gameReadInput(Game* game_obj)
{
<<<<<<< HEAD
    // 
    Engine_Detect(game_obj->gEngine);

}

void gameUpdate(Game* game_obj){

    Engine_Audio_handleAudioEvents(game_obj->gEngine);
    
    // game_obj->player1->move((game_obj->player1),30000,true,false);
    // Engine_Render_render(game_obj->gEngine, game_obj->player1->mRenderObject);
    // if(game_obj->frames%4==1){
    //     Engine_Render_changeObjectImage(game_obj->gEngine, game_obj->player1->mRenderObject, "person2");
    //     Engine_Render_render(game_obj->gEngine, game_obj->player1->mRenderObject);
    // }
    // if(game_obj->frames%4==3){
    //     Engine_Render_changeObjectImage(game_obj->gEngine, game_obj->player1->mRenderObject, "person1");
    //     Engine_Render_render(game_obj->gEngine, game_obj->player1->mRenderObject);
    // }

    game_obj->frames ++;
=======
    Engine_Detect(game_obj->gEngine);
    switch(game_obj->gameState)
    {
        case 0:
            if(Engine_Keyboard_getKeyPress(game_obj->gEngine) == 0b000001)
            {
                Engine_Audio_play(game_obj->gEngine, "/spiffs/guncock.mp3");
                game_obj->mode = 0;
            }
            else if(Engine_Keyboard_getKeyPress(game_obj->gEngine) == 0b000010)
            {
                Engine_Audio_play(game_obj->gEngine, "/spiffs/guncock.mp3");
                game_obj->mode = 1;
            }  
            else if(Engine_Keyboard_getKeyPress(game_obj->gEngine) == 0b000100)
            {
                if(game_obj->mode == 0)
                {
                    game_obj->gameState = 1;
                    gameSelect(game_obj);
                }
                Engine_Audio_play(game_obj->gEngine, "/spiffs/gunshot.mp3");
            }
            break;          
        
        case 1:
            if(Engine_Keyboard_getKeyPress(game_obj->gEngine) == 0b000001)
            {
                Engine_Audio_play(game_obj->gEngine, "/spiffs/guncock.mp3");
                game_obj->player1_character_type = 0;
            }
            else if(Engine_Keyboard_getKeyPress(game_obj->gEngine) == 0b000010)
            {
                Engine_Audio_play(game_obj->gEngine, "/spiffs/guncock.mp3");
                game_obj->player1_character_type = 1;
            }
            else if(Engine_Keyboard_getKeyPress(game_obj->gEngine) == 0b001000)
            {
                Engine_Audio_play(game_obj->gEngine, "/spiffs/guncock.mp3");
                game_obj->player1_character_type = 2;
            }
            else if(Engine_Keyboard_getKeyPress(game_obj->gEngine) == 0b010000)
            {
                Engine_Audio_play(game_obj->gEngine, "/spiffs/guncock.mp3");
                game_obj->player1_character_type = 3;
            }
            else if(Engine_Keyboard_getKeyPress(game_obj->gEngine) == 0b100000)
            {
                Engine_Audio_play(game_obj->gEngine, "/spiffs/guncock.mp3");
                game_obj->player1_character_type = 4;
            }
            else if(Engine_Keyboard_getKeyPress(game_obj->gEngine) == 0b000100)
            {
                game_obj->gameState = 2;
                Engine_Audio_play(game_obj->gEngine, "/spiffs/gunshot.mp3");
                gameStart(game_obj);
            }
            break;

        case 2:
            if(Engine_Keyboard_getKeyPress(game_obj->gEngine) == 0b001000)
            {
                printf("Jump!\n");
                game_obj->player1->jump(game_obj->player1);
            }
            else if(Engine_Keyboard_getKeyPress(game_obj->gEngine) == 0b010000)
            {
                Engine_Audio_play(game_obj->gEngine, "/spiffs/gunshot.mp3");
                for(int i = 0; i < 20; i++)
                {
                    if(game_obj->my_bullet[i] == NULL)
                    {
                        game_obj->my_bullet[i] = newBullet(game_obj->gEngine, game_obj->player1, Engine_Joystick_getAngle(game_obj->gEngine));
                        Engine_Render_addObject(game_obj->gEngine, game_obj->my_bullet[i]->mRenderObject);
                        break;
                    }
                }
            }
            else if(Engine_Keyboard_getKeyPress(game_obj->gEngine) == 0b000100)
            {
                game_obj->gameState = 3;
                Engine_Audio_play(game_obj->gEngine, "/spiffs/bipbop.mp3");
            }
            game_obj->player1->move(game_obj->player1, Engine_Joystick_getX(game_obj->gEngine));
            break;

        case 3:
            if(Engine_Keyboard_getKeyPress(game_obj->gEngine) == 0b000100)
            {
                game_obj->gameState = 2;
                Engine_Audio_play(game_obj->gEngine, "/spiffs/bipbop.mp3");
            }
            break;
    }
>>>>>>> 52d7500 (design gameflow)
}

void gameUpdate(Game* game_obj)
{
    Engine_Audio_handleAudioEvents(game_obj->gEngine);

    switch(game_obj->gameState)
    {
        case 1:
            for(int i = 0; i < 5; i++)
            {
                char name[11] = "preview";
                strcat(name, ind[i]);
                if(game_obj->player1_character_type != i) strcat(name, "-1");
                else strcat(name, "-2");
                Engine_Render_changeObjectImage(game_obj->gEngine, game_obj->previews[i], name);
                Engine_Render_render(game_obj->gEngine, game_obj->previews[i]);
                strcpy(name, "preview");
            }
            break;
        
        case 2:
            game_obj->player1->update((game_obj->player1));
            if(game_obj->frames%4==1){
                Engine_Render_changeObjectImage(game_obj->gEngine, game_obj->player1->mRenderObject, "person1-2");
            }
            if(game_obj->frames%4==3){
                Engine_Render_changeObjectImage(game_obj->gEngine, game_obj->player1->mRenderObject, "person1-1");
            }
            Engine_Render_render(game_obj->gEngine, game_obj->player1->mRenderObject);
            for(int i = 0; i < 20; i++)
            {
                if(game_obj->my_bullet[i] != NULL)
                {
                    //printf("find a non-null bullet at (%d, %d)\n", game_obj->my_bullet[i]->posX, game_obj->my_bullet[i]->posY);
                    if(!(game_obj->my_bullet[i]->move(game_obj->my_bullet[i])))
                    {
                        Engine_Render_removeObject(game_obj->gEngine, game_obj->my_bullet[i]->mRenderObject);
                        deleteBullet(game_obj->my_bullet[i], game_obj->gEngine);
                        game_obj->my_bullet[i] = NULL;
                    }
                    else
                    {
                        game_obj->my_bullet[i]->update(game_obj->my_bullet[i]);
                        Engine_Render_render(game_obj->gEngine, game_obj->my_bullet[i]->mRenderObject);
                    }
                }
            }
            break;
    }
    game_obj->frames++;
}

void gameRender(Game* game_obj){
    Engine_Render_update(game_obj->gEngine);
}
