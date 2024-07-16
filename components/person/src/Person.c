#include <stdio.h>
#include <stdint.h>
#include "Person.h"

void personMove(Person* obj, int16_t magX)
{
    obj->speedX = magX / 3072;
}

void personJump(Person* obj){
    if(obj->speedY==0||obj->mRenderObject->mPosY == 190||obj->mRenderObject->mPosY == 120||obj->mRenderObject->mPosY == 65)
        obj->speedY = 16; // initial speed of a jump
    else
        return;
}

void personUpdate(Person* obj){

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
    else if (obj->speedY<=0 && obj->mRenderObject->mPosY + 50 >= 170 && obj->mRenderObject->mPosY + 50 <= 170+15){
        
        if((obj->posX + 25 >= 20 && obj->posX + 25 <= 100)||(obj->posX + 25 >= 20+200 && obj->posX + 25 <= 100+200)){
            obj->posY = 170 - 50;
            obj->speedY = 0;
        }else{
            obj->posY -= obj->speedY;
            obj->speedY--;
        }
    }
    else if (obj->speedY<=0 && obj->mRenderObject->mPosY + 50 >= 115 && obj->mRenderObject->mPosY + 50 <= 115+15){
        
        if((obj->posX + 25 >= 60 && obj->posX + 25 <= 140)||(obj->posX + 25 >= 180 && obj->posX + 25 <= 260)){
            obj->posY = 115 - 50;
            obj->speedY = 0;
        }else{
            obj->posY -= obj->speedY;
            obj->speedY--;
        }
    }
    else if (obj->speedY<=0 && obj->mRenderObject->mPosY + 50 >= 60 && obj->mRenderObject->mPosY + 50 <= 15+60){
        
        if((obj->posX + 25 >= 120 && obj->posX + 25 <= 200)){
            obj->posY = 60 - 50;
            obj->speedY = 0;
        }else{
            obj->posY -= obj->speedY;
            obj->speedY--;
        }
    }
    else
    {
        obj->posY -= obj->speedY;
        obj->speedY--;
    }
    if(obj->speedY >= -15) obj->speedY--;
    //printf("PosX: %d, PosY: %d\n", obj->posX, obj->posY);
    obj->mRenderObject->setPos(obj->mRenderObject, obj->posX, obj->posY);
    obj->mWeaponObject->setPos(obj->mWeaponObject, obj->posX, obj->posY);

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
    obj->mWeaponObject = Engine_Render_newObject(engine, "weapon1-l", posX, posY, 1);

    return obj;
}

void deletePerson(Person* obj, Engine* engine)
{
    Engine_Render_deleteObject(engine, obj->mRenderObject);
    Engine_Render_deleteObject(engine, obj->mWeaponObject);

}