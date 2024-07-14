#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_spiffs.h"

#include "Engine.h"

#include "../files/people.h"
//--important variable--//
const int player1_x = 75;
const int player1_y = 200;
const int player2_x = 75;
const int player2_y = 200;


//--class declaration--//
typedef struct person;
typedef struct bullet;

//--class Person--//
typedef struct person
{
    RenderObject *mRenderObject;
    // int attack;
    int HP;
    int state;
    int oriX;
    int oriY;
    int preX;
    int preY;
    int posX;
    int posY;
    int speedY;// jump
    int weapon_type; // 1->pistol 2->shotgun 3->submachine
    int cd;

    void (*move)(struct person*);
    void (*jump)(struct person*);
    void (*update)(struct person*); //to update the state of a person.(cd--)
    void (*attack)(struct person*, struct bullet*);
}Person;

void personMove(Person* obj)
{
    if(obj->mRenderObject->mPosX + (5 * obj->oriX) <= 0 || obj->mRenderObject->mPosX + (5 * obj->oriX) + 50 >= 320)
    {
        obj->oriX *= -1;
    }

    // if(obj->preX + 5*obj->oriX >= 320-50 || obj->preX + 5*obj->oriX <0){
    //     obj->oriX *= -1;
    // }
    
    obj->mRenderObject->setPos(obj->mRenderObject, obj->mRenderObject->mPosX + (5 * obj->oriX), obj->mRenderObject->mPosY);
    
}

void personJump(Person* obj){
    if(obj->speedY==0)
        obj->speedY = 10; // initial speed of a jump
    else
        return;
}
void personupdate(Person* obj){
    // person damaged
    
    // person fallen
    if(obj->posY < 0){
        obj->HP --;
        obj->posX = player1_x;
        obj->posY = player1_y;
    }


    // person died
    if(obj->HP==0){
        
        
        
        
    }
}
void personAttack(Person* obj){
    
    if(obj->cd==0){
        switch (obj->weapon_type)
        {

        case 2://2->shotgun
            
            // obj->speed = 15;
            
            break;
        
        case 3://3->submachine
            
            // obj->speed = 20;
            

            break;

        default:// pistol

            // obj->speed = 10;

            break;
        }
    }
    else
        return;
}
void newPerson(Person* obj, Engine* engine, int16_t posX, int16_t posY)
{
    obj->move = personMove;
    obj->attack = personAttack;
    obj->jump = personJump;
    obj->update = personupdate;
    obj->state = 1;
    obj->oriX = 1;
    obj->oriY = 1;
    // obj->attack = 10;
    obj->HP = 100;
    obj->weapon_type = 1;
    obj->cd = 0;// cd=0 -> person can attack
    obj->posX = posX;
    obj->posY = posY;
    obj->preX = posX;
    obj->preY = posY;
    obj->speedY = 0;
    obj->mRenderObject = Engine_Render_newObject(engine, "person1", posX, posY, 1);
}

void deletePerson(Person* obj, Engine* engine)
{
    Engine_Render_deleteObject(engine, obj->mRenderObject);
}
//----//




//--class Bullet--//

typedef struct bullet
{
    RenderObject mRenderObject;
    int speed;
    int angle; //0~360 
    int posX;
    int posY;

    void (*new)(struct person*, struct bullet*, int16_t);
    bool (*move)(struct bullet*);
}Bullet;

bool bulletMove(Bullet* obj){ // return whether the bullet is alive

    obj->posX += cos(obj->angle) * obj->speed;
    obj->posY -= sin(obj->angle) * obj->speed; 
    
    if(obj->posX<0 || obj->posY<0 || obj->posX>320 || obj->posY > 240){
        return false;
    }
    return true;

}
void bulletNew(Person* person1, Bullet* obj, int16_t angle){

    obj->new = bulletNew;
    obj->move = bulletMove;

     //weapon
    //1->pistol speed=10 cd = 4 angle = 0 or 180
    //2->shotgun speed = 15 cd = 10 angle = 0, 30, -30 or 180 210 -210 (3*bullet)
    //3->submachine speed = 20 cd = 2 angle = 0 or 180
    obj->posX = person1->posX;
    obj->posY = person1->posY;
    obj->angle = angle;

    switch (person1->weapon_type)
    {
    case 2:
        
        obj->speed = 15;
        
        break;
    
    case 3:
        
        obj->speed = 20;
        
        break;

    default:

        obj->speed = 10;

        break;
    }

}

//----//



//--Declare Managers and objects--//
// extern const uint16_t people[];
// extern const uint16_t people2[];

extern const uint16_t Sasge[6][2500];
extern const uint16_t Musk[6][2500];
extern const uint16_t English[6][2500];

extern const uint16_t block[];




Engine* gEngine;

RenderObject *background, *ground;
RenderObject *block_1, *block_2, *block_3, *block_4, *block_5;

Person group[5];
//----//

//--Init Function--//
void init()
{   
    gEngine = newEngine();
    Engine_Render_addImage(gEngine, "person1", English[0], 50, 50);
    Engine_Render_addImage(gEngine, "person2", English[1], 50, 50);
    Engine_Render_addImage(gEngine, "background", backgroundImage, 320, 240);
    Engine_Render_addImage(gEngine, "block", block, 80, 15);
    Engine_Render_addImage(gEngine, "ground", block, 320, 15);
    Engine_Audio_addAudio(gEngine, "/spiffs/adf_music.mp3");
    Engine_Audio_addAudio(gEngine, "/spiffs/gunshot.mp3");
    Engine_Audio_addAudio(gEngine, "/spiffs/metalpipe.mp3");
    Engine_Audio_addAudio(gEngine, "/spiffs/potai.mp3");
    Engine_Audio_addAudio(gEngine, "/spiffs/yamete.mp3");
    Engine_Audio_addAudio(gEngine, "/spiffs/guncock.mp3");
    Engine_Audio_setVolume(gEngine, 0);
}
//----//

void app_main(void)
{   
    init();

    background = Engine_Render_newObject(gEngine, "background", 0, 0, 1);
    ground = Engine_Render_newObject(gEngine, "ground", 0, 225, 1);
    block_1 = Engine_Render_newObject(gEngine, "block", 20, 170, 1);
    block_2 = Engine_Render_newObject(gEngine, "block", 220, 170, 1);
    block_3 = Engine_Render_newObject(gEngine, "block", 60, 115, 1);
    block_4 = Engine_Render_newObject(gEngine, "block", 180, 115, 1);
    block_5 = Engine_Render_newObject(gEngine, "block", 120, 70, 1);
    Engine_Render_addObject(gEngine, background);
    Engine_Render_addObject(gEngine, block_1);
    Engine_Render_addObject(gEngine, block_2);
    Engine_Render_addObject(gEngine, block_3);
    Engine_Render_addObject(gEngine, block_4);
    Engine_Render_addObject(gEngine, block_5);
    // Engine_Render_addObject(gEngine, ground);

    for(int i = 0; i < 1; i++)
    {
        newPerson(&group[i], gEngine, 1, 190);
        Engine_Render_addObject(gEngine, group[i].mRenderObject);
    }
    // for(int i = 0; i < 2; i++)
    // {
    //     Engine_Render_changeObjectImage(gEngine, group[i].mRenderObject, "person2");
    // }

    int16_t frame_count = 0;

    while(1){
        Engine_Detect(gEngine);
        Engine_Audio_handleAudioEvents(gEngine);

        group[0].move(&(group[0]));
        Engine_Render_render(gEngine, group[0].mRenderObject);
        if(frame_count%4==1){
            Engine_Render_changeObjectImage(gEngine, group[0].mRenderObject, "person2");
            Engine_Render_render(gEngine, group[0].mRenderObject);
        }
        if(frame_count%4==3){
            Engine_Render_changeObjectImage(gEngine, group[0].mRenderObject, "person1");
            Engine_Render_render(gEngine, group[0].mRenderObject);
        }

        Engine_Render_update(gEngine);
        vTaskDelay((2000/60)/portTICK_PERIOD_MS);
        frame_count ++;
    }

    
    // while(1)
    // {
    //     Engine_Detect(gEngine);
    //     Engine_Audio_handleAudioEvents(gEngine);

    //     if(Engine_Keyboard_isKeyPress(gEngine, 0b000001))
    //     {
    //         Engine_Audio_play(gEngine, "/spiffs/gunshot.mp3");
    //     }
    //     else if(Engine_Keyboard_isKeyPress(gEngine, 0b000010))
    //     {
    //         Engine_Audio_play(gEngine, "/spiffs/adf_music.mp3");
    //     }
    //     else if(Engine_Keyboard_isKeyPress(gEngine, 0b000100))
    //     {
    //         Engine_Audio_play(gEngine, "/spiffs/metalpipe.mp3");
    //     }
    //     else if(Engine_Keyboard_isKeyPress(gEngine, 0b001000))
    //     {
    //         Engine_Audio_play(gEngine, "/spiffs/potai.mp3");
    //     }
    //     else if(Engine_Keyboard_isKeyPress(gEngine, 0b010000))
    //     {
    //         Engine_Audio_play(gEngine, "/spiffs/yamete.mp3");
    //     }
    //     else if(Engine_Keyboard_isKeyPress(gEngine, 0b100000))
    //     {
    //         Engine_Audio_play(gEngine, "/spiffs/guncock.mp3");
    //     }

        
    //     for(int i = 0; i < 5; i++)
    //     {
    //         group[i].move(&(group[i]));
    //     }
    //     for(int i = 0; i < 5; i++)
    //     {
    //         Engine_Render_render(gEngine, group[i].mRenderObject);
    //     }
    //     Engine_Render_update(gEngine);
    //     vTaskDelay((1000/60)/portTICK_PERIOD_MS);
    // }

    /*
    for(int i = 0; i < 5; i++)
    {
        deletePerson(&group[i], gEngine);
    }
    */
    //printf("%s\n", "Code finished.");
    //return 0;
}
