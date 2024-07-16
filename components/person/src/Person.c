#include <stdio.h>
#include <stdint.h>
#include "Person.h"

//X, Y 的讀值在-32678至32677間
//FPS = 15
// 

void personMove(Person* obj, int16_t magX)
{
    obj->speedX = magX / 3000;
}

void personJump(Person* obj)
{
    obj->speedY = 10;
}

void personUpdate(Person* obj){
    // person damaged
    if(obj->mRenderObject->mPosX + obj->speedX >= 0 && obj->mRenderObject->mPosX + obj->speedX + 50 < 320)
    {
        obj->posX = obj->mRenderObject->mPosX + obj->speedX;
    }
    if(obj->mRenderObject->mPosY + (-1 * obj->speedY) + 50 >= 240)
    {
        obj->posY = 190;
        obj->speedY = 0;
    }
    else if(obj->mRenderObject->mPosY + (-1 * obj->speedY) <= 0)
    {
        obj->posY = 0;
        obj->speedY = 0;
    }
    else
    {
        obj->posY -= obj->speedY;
        obj->speedY--;
    }
    if(obj->speedY >= -15) obj->speedY--;
    //printf("PosX: %d, PosY: %d\n", obj->posX, obj->posY);
    obj->mRenderObject->setPos(obj->mRenderObject, obj->posX, obj->posY);
    //printf("set finished!\n");
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

Person* newPerson(Engine* engine, int16_t posX, int16_t posY)
{
    Person* obj = calloc(1, sizeof(Person));
    obj->move = personMove;
    obj->jump = personJump;
    obj->attack = personAttack;
    obj->update = personUpdate;
    obj->state = 1; //1->normal 2->damaged >=3->invincible (decaded by frames)
    obj->oriX = 0;
    obj->oriY = 0; //oriY=0 -> stand on the floor
    obj->HP = 100;
    obj->weapon_type = 1;
    obj->cd = 0;// cd=0 -> person can attack
    obj->posX = posX;
    obj->posY = posY;
    obj->mRenderObject = Engine_Render_newObject(engine, "person1-1l", posX, posY, 1);
    //obj->mWeaponObject = Engine_Render_newObject(engine, "weapon1", posX, posY, 1);

    return obj;
}

void deletePerson(Person* obj, Engine* engine)
{
    Engine_Render_deleteObject(engine, obj->mRenderObject);
    //Engine_Render_deleteObject(engine, obj->mWeaponObject);
}