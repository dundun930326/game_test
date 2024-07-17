#ifndef _GAME_C_
#define _GAME_C_

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Game.h"
#include "weaponImage.h"
#include "people.h"
#include "numbers_bitmap.h"
#include "box.h"
#include "Engine.h"

#define PI 3.14159265

extern const uint16_t* bitmap_allArray[10];
extern const uint16_t Sasge_left[6][2500];
extern const uint16_t Musk_left[6][2500];
extern const uint16_t English_left[6][2500];
extern const uint16_t Pie_left[6][2500];
extern const uint16_t Anya_left[6][2500];
extern const uint16_t Sasge_right[6][2500];
extern const uint16_t Musk_right[6][2500];
extern const uint16_t English_right[6][2500];
extern const uint16_t Pie_right[6][2500];
extern const uint16_t Anya_right[6][2500];
extern const uint16_t weapon1_right[3][2500];
extern const uint16_t weapon1_left[3][2500];

extern const uint16_t block[];
extern const uint16_t backgroundImage[];
extern const uint16_t box[];

const uint16_t weapon_right[3][2500];
const uint16_t weapon_left[3][2500];

const uint16_t bulletImage[] = {0,0,0,0,0,0,0,0,0};

const char* ind[11] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
const uint16_t (*characters[2][5])[2500] = {{Sasge_left, Musk_left, English_left, Pie_left, Anya_left}, 
                                        {Sasge_right, Musk_right, English_right, Pie_right, Anya_right}};
const char* person_allArray[2][2][6] = {{{"person1-1l", "person1-2l", "person1-3l", "person1-4l", "person1-5l", "person1-6l"}, {"person1-1r", "person1-2r", "person1-3r", "person1-4r", "person1-5r", "person1-6r"}},
{{"person2-1l", "person2-2l", "person2-3l", "person2-4l", "person2-5l", "person2-6l"}, {"person2-1r", "person2-2r", "person2-3r", "person2-4r", "person2-5r", "person2-6r"}}};

//--functions for internal usage only--//
void gameLoadPerson(Game* game_obj)
{
    for(int i = 0; i < 6; i++)
    {
        Engine_Render_addImage(game_obj->gEngine, person_allArray[0][0][i], characters[0][game_obj->player1_character_type][i], 50, 50);
    }
    for(int i = 0; i < 6; i++)
    {
        Engine_Render_addImage(game_obj->gEngine, person_allArray[0][1][i], characters[1][game_obj->player1_character_type][i], 50, 50);
    }
    for(int i = 0; i < 6; i++)
    {
        Engine_Render_addImage(game_obj->gEngine, person_allArray[1][0][i], characters[0][game_obj->player2_character_type][i], 50, 50);
    }
    for(int i = 0; i < 6; i++)
    {
        Engine_Render_addImage(game_obj->gEngine, person_allArray[1][1][i], characters[1][game_obj->player2_character_type][i], 50, 50);
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
    game_obj->frames = 0;

    for(int i = 0; i < 5; i++)
    {
        Engine_Render_removeObject(game_obj->gEngine, game_obj->previews[i]);
    }
    for(int i = 0; i < 5; i++)
    {
        Engine_Render_addObject(game_obj->gEngine, game_obj->blocks[i]);
    }
    gameLoadPerson(game_obj);

    //create treasure object
    game_obj->mTreasure = newTreasure(game_obj->gEngine);
    Engine_Render_addObject(game_obj->gEngine, game_obj->mTreasure->mRenderObject);

    //create person objects
    game_obj->player1 = newPerson(game_obj->gEngine, 0, 190, 1);
    Engine_Render_addObject(game_obj->gEngine, game_obj->player1->mRenderObject);
    Engine_Render_addObject(game_obj->gEngine, game_obj->player1->mItemObject);

    game_obj->player2 = newPerson(game_obj->gEngine, 270, 190, 2);
    Engine_Render_addObject(game_obj->gEngine, game_obj->player2->mRenderObject);
    Engine_Render_addObject(game_obj->gEngine, game_obj->player2->mItemObject);

    printf("Game start!\n");

    //create HP text objects
    int temp = game_obj->player1->HP;
    for(int i = 0; i < 3; i++)
    {
        game_obj->HP[0][2 - i] = Engine_Render_newObject(game_obj->gEngine, ind[temp % 10], 15 + 28 * (2 - i), 15, 1);
        Engine_Render_addObject(game_obj->gEngine, game_obj->HP[0][2 - i]);
        temp /= 10;
    }
    temp = game_obj->player2->HP;
    for(int i = 0; i < 3; i++)
    {
        game_obj->HP[1][2 - i] = Engine_Render_newObject(game_obj->gEngine, ind[temp % 10], 221 + 28 * (2 - i), 15, 1);
        Engine_Render_addObject(game_obj->gEngine, game_obj->HP[1][2 - i]);
        temp /= 10;
    }

    if(game_obj->mode == 0)
    {
        game_obj->mCPU = newCPU();
    }
}

void gameAddNewWeapon(Game* game_obj)
{
    srand(game_obj->frames);
    int type = rand() % 3 + 1;
    int loc = rand() % 4;
    for(int i = 0; i < 6; i++)
    {
        if(game_obj->weapons[i] == NULL)
        {
            game_obj->weapons[i] = newWeapon(game_obj->gEngine, type, loc);
            Engine_Render_addObject(game_obj->gEngine, game_obj->weapons[i]->mRenderObject);
            break;
        }
    }
    printf("Add a new weapon!!!\n");
}

void gameOver(Game* game_obj, bool result)
{
    if(result)
    {
        game_obj->result = Engine_Render_newObject(game_obj->gEngine, "win", 0, 0, 1);
    }
    else
    {
        game_obj->result = Engine_Render_newObject(game_obj->gEngine, "lose", 0, 0, 1);
    }
    Engine_Render_addObject(game_obj->gEngine, game_obj->result);
}

void gameReset(Game* game_obj)
{
    for(int i = 0; i < 5; i++)
    {
        Engine_Render_removeObject(game_obj->gEngine, game_obj->blocks[i]);
    }
    Engine_Render_removeObject(game_obj->gEngine, game_obj->player1->mRenderObject);
    Engine_Render_removeObject(game_obj->gEngine, game_obj->player1->mItemObject);
    deletePerson(game_obj->player1, game_obj->gEngine);
    Engine_Render_removeObject(game_obj->gEngine, game_obj->player2->mRenderObject);
    Engine_Render_removeObject(game_obj->gEngine, game_obj->player2->mItemObject);
    deletePerson(game_obj->player2, game_obj->gEngine);

    Engine_Render_removeObject(game_obj->gEngine, game_obj->mTreasure->mRenderObject);
    deleteTreasure(game_obj->mTreasure, game_obj->gEngine);

    for(int i = 0; i < 20; i++)
    {
        if(game_obj->my_bullet[i] != NULL)
        {
            Engine_Render_removeObject(game_obj->gEngine, game_obj->my_bullet[i]->mRenderObject);
            deleteBullet(game_obj->my_bullet[i], game_obj->gEngine);
            game_obj->my_bullet[i] = NULL;
        }
    }
    for(int i = 0; i < 20; i++)
    {
        if(game_obj->enemy_bullet[i] != NULL)
        {
            Engine_Render_removeObject(game_obj->gEngine, game_obj->enemy_bullet[i]->mRenderObject);
            deleteBullet(game_obj->enemy_bullet[i], game_obj->gEngine);
            game_obj->enemy_bullet[i] = NULL;
        }
    }

    for(int i = 0; i < 6; i++)
    {
        if(game_obj->weapons[i] != NULL)
        {
            Engine_Render_removeObject(game_obj->gEngine, game_obj->weapons[i]->mRenderObject);
            deleteWeapon(game_obj->weapons[i], game_obj->gEngine);
            game_obj->weapons[i] = NULL;
        }
    }

    for(int i = 0; i < 3; i++)
    {
        Engine_Render_removeObject(game_obj->gEngine, game_obj->HP[0][2 - i]);
        Engine_Render_deleteObject(game_obj->gEngine, game_obj->HP[0][2 - i]);
    }
    for(int i = 0; i < 3; i++)
    {
        Engine_Render_removeObject(game_obj->gEngine, game_obj->HP[1][2 - i]);
        Engine_Render_deleteObject(game_obj->gEngine, game_obj->HP[1][2 - i]);
    }

    Engine_Render_removeObject(game_obj->gEngine, game_obj->result);
    Engine_Render_deleteObject(game_obj->gEngine, game_obj->result);

    if(game_obj->mode == 0)
    {
        deleteCPU(game_obj->mCPU);
    }
}
//----//

void gameNew(Game* game_obj)
{
    game_obj->gameState = 0;
    game_obj->frames = 0;
    game_obj->player1_character_type = 0;
    game_obj->player2_character_type = 0;
    game_obj->mode = 0;
    game_obj->gEngine = newEngine();
    game_obj->init = gameInit;
    //game_obj->checkTreasureChest = gameCheckTreasureChest;
    game_obj->start = gameStart;
    game_obj->readInput = gameReadInput;
    game_obj->update = gameUpdate;
    game_obj->render = gameRender;
}

void gameInit(Game* game_obj)
{
    //--Load Resources--//
    Engine_Render_addImage(game_obj->gEngine, "treasure", box, 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "block", block, 80, 15);
    Engine_Render_addImage(game_obj->gEngine, "background", backgroundImage, 320, 240); //TODO: change image
    Engine_Render_addImage(game_obj->gEngine, "win", block, 50, 50); //TODO: change image
    Engine_Render_addImage(game_obj->gEngine, "lose", block, 50, 50); //TODO: change image
    Engine_Render_addImage(game_obj->gEngine, "item", block, 50, 50); //TODO: change image
    Engine_Render_addImage(game_obj->gEngine, "ground", block, 320, 15);
    Engine_Render_addImage(game_obj->gEngine, "bullet", bulletImage, 3, 3);
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
    Engine_Render_addImage(game_obj->gEngine, "weapon1-r", weapon_right[0], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "weapon2-r", weapon_right[1], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "weapon3-r", weapon_right[2], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "weapon1-l", weapon_left[0], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "weapon2-l", weapon_left[1], 50, 50);
    Engine_Render_addImage(game_obj->gEngine, "weapon3-l", weapon_left[2], 50, 50);

    for(int i = 0; i < 10; i++)
    {
        Engine_Render_addImage(game_obj->gEngine, ind[i], bitmap_allArray[i], 28, 40);
    }
    Engine_Audio_addAudio(game_obj->gEngine, "/spiffs/adf_music.mp3");
    Engine_Audio_addAudio(game_obj->gEngine, "/spiffs/gunshot.mp3");
    Engine_Audio_addAudio(game_obj->gEngine, "/spiffs/metalpipe.mp3");
    Engine_Audio_addAudio(game_obj->gEngine, "/spiffs/potai.mp3");
    Engine_Audio_addAudio(game_obj->gEngine, "/spiffs/yamete.mp3");
    Engine_Audio_addAudio(game_obj->gEngine, "/spiffs/guncock.mp3");
    Engine_Audio_addAudio(game_obj->gEngine, "/spiffs/bipbop.mp3");

    Engine_Audio_setVolume(game_obj->gEngine, 0);
    Engine_Joystick_setThreshold(game_obj->gEngine, 255);
    
    game_obj->background = Engine_Render_newObject(game_obj->gEngine, "background", 0, 0, 1);
    game_obj->ground = Engine_Render_newObject(game_obj->gEngine, "ground", 0, 225, 1);

    game_obj->blocks[0] = Engine_Render_newObject(game_obj->gEngine, "block", 20, 170, 1);
    game_obj->blocks[1] = Engine_Render_newObject(game_obj->gEngine, "block", 220, 170, 1);
    game_obj->blocks[2] = Engine_Render_newObject(game_obj->gEngine, "block", 60, 115, 1);
    game_obj->blocks[3] = Engine_Render_newObject(game_obj->gEngine, "block", 180, 115, 1);
    game_obj->blocks[4] = Engine_Render_newObject(game_obj->gEngine, "block", 120, 60, 1);
    for(int i = 1; i < 6; i++)
    {
        char name[11] = "preview";
        strcat(name, ind[i]);
        if(game_obj->player1_character_type != i) strcat(name, "-1");
        else strcat(name, "-2");
        game_obj->previews[i - 1] = Engine_Render_newObject(game_obj->gEngine, name, 50 * i - 15, 95, 1);
        strcpy(name, "preview");
    }
    //----//

    //--Add object to the render list for the first time--//
    Engine_Render_addObject(game_obj->gEngine, game_obj->background);
    Engine_Render_addObject(game_obj->gEngine, game_obj->ground);
    //
}

void gameReadInput(Game* game_obj)
{
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
                game_obj->player1->jump(game_obj->player1);
            }
            else if(Engine_Keyboard_getKeyPress(game_obj->gEngine) == 0b010000)
            {
                Engine_Audio_play(game_obj->gEngine, "/spiffs/gunshot.mp3");
                if(Engine_Joystick_notZero(game_obj->gEngine))
                {
                    game_obj->player1->attack(game_obj->player1, game_obj->my_bullet, game_obj->gEngine, Engine_Joystick_getAngle(game_obj->gEngine));
                }
                else
                {
                    game_obj->player1->attack(game_obj->player1, game_obj->my_bullet, game_obj->gEngine, (game_obj->player1->oriX > 0) ? 0 : 180);
                }
            }
            else if(Engine_Keyboard_getKeyPress(game_obj->gEngine) == 0b100000)
            {
                game_obj->player1->useItem(game_obj->player1);
            }
            else if(Engine_Keyboard_getKeyPress(game_obj->gEngine) == 0b000100)
            {
                if(game_obj->mode == 0)
                {
                    game_obj->gameState = 3;
                    Engine_Audio_play(game_obj->gEngine, "/spiffs/bipbop.mp3");
                }
            }
            game_obj->player1->move(game_obj->player1, Engine_Joystick_getX(game_obj->gEngine));
            
            //virtual input section for either computer or connection datas
            if(game_obj->mode == 0) //pvc
            {
                game_obj->mCPU->compute(game_obj->mCPU, game_obj);
                if(game_obj->mCPU->keyboardSim[JUMP] == 1)
                {
                    game_obj->player2->jump(game_obj->player2);
                }
                else if(game_obj->mCPU->keyboardSim[ITEM] == 1)
                {
                    game_obj->player2->useItem(game_obj->player2);
                }
                else if(game_obj->mCPU->keyboardSim[ATTACK] == 1)
                {
                    game_obj->player2->attack(game_obj->player2, game_obj->enemy_bullet, game_obj->gEngine, atan2(game_obj->mCPU->JoystickYSim, game_obj->mCPU->JoystickXSim) * 180 / PI);
                }
                game_obj->player2->move(game_obj->player2, game_obj->mCPU->JoystickXSim);
            }
            else if(game_obj->mode == 1) // pvp (self-master)
            {
                //
            }
            break;

        case 3:
            if(Engine_Keyboard_getKeyPress(game_obj->gEngine) == 0b000100)
            {
                game_obj->gameState = 2;
                Engine_Audio_play(game_obj->gEngine, "/spiffs/bipbop.mp3");
            }
            break;
        
        case 4:
            if(Engine_Keyboard_getKeyPress(game_obj->gEngine) == 0b000100)
            {
                game_obj->gameState = 0;
                Engine_Audio_play(game_obj->gEngine, "/spiffs/guncock.mp3");
                gameReset(game_obj);
            }
            break;
    }
}

void gameUpdate(Game* game_obj)
{
    Engine_Audio_handleAudioEvents(game_obj->gEngine);

    switch(game_obj->gameState)
    {
        case 1:
            for(int i = 1; i < 6; i++)
            {
                char name[11] = "preview";
                strcat(name, ind[i]);
                if(game_obj->player1_character_type != i - 1) strcat(name, "-1");
                else strcat(name, "-2");
                Engine_Render_changeObjectImage(game_obj->gEngine, game_obj->previews[i - 1], name);
                Engine_Render_render(game_obj->gEngine, game_obj->previews[i - 1]);
                strcpy(name, "preview");
            }
            break;
        
        case 2:
            //update bullet
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
                    else if(game_obj->player2->damage(game_obj->player2, game_obj->my_bullet[i]))
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
                if(game_obj->enemy_bullet[i] != NULL)
                {
                    if(!(game_obj->enemy_bullet[i]->move(game_obj->enemy_bullet[i])))
                    {
                        Engine_Render_removeObject(game_obj->gEngine, game_obj->enemy_bullet[i]->mRenderObject);
                        deleteBullet(game_obj->enemy_bullet[i], game_obj->gEngine);
                        game_obj->enemy_bullet[i] = NULL;
                    }
                    else if(game_obj->player1->damage(game_obj->player1, game_obj->enemy_bullet[i]))
                    {
                        Engine_Render_removeObject(game_obj->gEngine, game_obj->enemy_bullet[i]->mRenderObject);
                        deleteBullet(game_obj->enemy_bullet[i], game_obj->gEngine);
                        game_obj->enemy_bullet[i] = NULL;
                    }
                    else
                    {
                        game_obj->enemy_bullet[i]->update(game_obj->enemy_bullet[i]);
                        Engine_Render_render(game_obj->gEngine, game_obj->enemy_bullet[i]->mRenderObject);
                    }
                }
            }
            
            //update weapon
            for(int i = 0; i < 6; i++)
            {
                if(game_obj->weapons[i] != NULL)
                {
                    if(game_obj->weapons[i]->available)
                    {
                        game_obj->weapons[i]->hit(game_obj->weapons[i], game_obj->player1);
                        game_obj->weapons[i]->hit(game_obj->weapons[i], game_obj->player2);
                        if(game_obj->weapons[i]->owner == NULL)
                        {
                            game_obj->weapons[i]->update(game_obj->weapons[i], game_obj->gEngine);
                            Engine_Render_render(game_obj->gEngine, game_obj->weapons[i]->mRenderObject);
                        }
                    }
                    else
                    {
                        Engine_Render_removeObject(game_obj->gEngine, game_obj->weapons[i]->mRenderObject);
                        deleteWeapon(game_obj->weapons[i], game_obj->gEngine);
                        game_obj->weapons[i] = NULL;
                    }
                }
            }

            //update treasure
            if(game_obj->frames % 300 == 0)
            {
                game_obj->mTreasure->setAvailable(game_obj->mTreasure, 1);
            }
            else if(game_obj->mTreasure->hit(game_obj->mTreasure, game_obj->player1) || game_obj->mTreasure->hit(game_obj->mTreasure, game_obj->player2))
            {
                game_obj->mTreasure->setAvailable(game_obj->mTreasure, 0);
                gameAddNewWeapon(game_obj);
            }
            game_obj->mTreasure->update(game_obj->mTreasure);
            Engine_Render_render(game_obj->gEngine, game_obj->mTreasure->mRenderObject);

            //update person
            game_obj->player1->update(game_obj->player1, game_obj->gEngine, game_obj->frames);
            game_obj->player2->update(game_obj->player2, game_obj->gEngine, game_obj->frames);
            Engine_Render_render(game_obj->gEngine, game_obj->player1->mRenderObject);
            if(game_obj->player1->mWeapon != NULL) Engine_Render_render(game_obj->gEngine, game_obj->player1->mWeapon->mRenderObject);
            Engine_Render_render(game_obj->gEngine, game_obj->player2->mRenderObject);
            if(game_obj->player2->mWeapon != NULL) Engine_Render_render(game_obj->gEngine, game_obj->player2->mWeapon->mRenderObject);

            //update HP text
            //printf("now P1: %d, P2: %d\n", game_obj->player1->HP, game_obj->player2->HP);
            if(game_obj->player1->hurtTime >= HURTTIME_DURATION - 1)
            {
                int temp = game_obj->player1->HP;
                for(int i = 0; i < 3; i++)
                {
                    Engine_Render_changeObjectImage(game_obj->gEngine, game_obj->HP[0][2 - i], ind[temp % 10]);
                    Engine_Render_render(game_obj->gEngine, game_obj->HP[0][2 - i]);
                    temp /= 10;
                }
            }
            if(game_obj->player2->hurtTime >= HURTTIME_DURATION - 1)
            {
                int temp = game_obj->player2->HP;
                for(int i = 0; i < 3; i++)
                {
                    Engine_Render_changeObjectImage(game_obj->gEngine, game_obj->HP[1][2 - i], ind[temp % 10]);
                    Engine_Render_render(game_obj->gEngine, game_obj->HP[1][2 - i]);
                    temp /= 10;
                }
            }

            //refresh CPU
            if(game_obj->mode == 0)
            {
                game_obj->mCPU->update(game_obj->mCPU);
            }

            //detect gameover or not
            if(game_obj->player1->HP == 0)
            {
                gameOver(game_obj, 0);
                game_obj->gameState = 4;
            }
            else if(game_obj->player2->HP == 0)
            {
                gameOver(game_obj, 1);
                game_obj->gameState = 4;
            }
            break;
    }
    game_obj->frames++;
}

void gameRender(Game* game_obj){
    Engine_Render_update(game_obj->gEngine);
}

#endif // _GAME_C_