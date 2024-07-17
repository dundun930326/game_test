#ifndef _PERSON_C_
#define _PERSON_C_

#include <stdio.h>
#include <stdint.h>
#include "Person.h"

extern const char* person_allArray[2][2][6];

void personMove(Person* obj, int16_t magX)
{
    if((obj->oriX < 0 && magX > 0)
        ||(obj->oriX > 0 && magX < 0))
    {
        obj->oriX *= -1;
    }
    obj->speedX = magX / 3072;
    //if(obj->speedX > 10) obj->speedX = 10;
    //else if(obj->speedX < -10) obj->speedX = -10;
}

void personJump(Person* obj){
    if(obj->speedY==0||obj->mRenderObject->mPosY == 190||obj->mRenderObject->mPosY == 120||obj->mRenderObject->mPosY == 65)
        obj->speedY = 16; // initial speed of a jump
    else
        return;
}

void personUpdate(Person* obj, Engine* engine, int frames){

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
    
    if(obj->oriX > 0)
    {
        if(frames % 4 == 1)
        {
            Engine_Render_changeObjectImage(engine, obj->mRenderObject, person_allArray[obj->index - 1][1][2 * obj->state - 2 + (obj->hurtTime>20)]);
        }
        if(frames % 4 == 3)
        {
            Engine_Render_changeObjectImage(engine, obj->mRenderObject, person_allArray[obj->index - 1][1][2 * obj->state - 1 + (obj->hurtTime>20)]);
        }
    }
    else
    {
        if(frames % 4 == 1)
        {
            Engine_Render_changeObjectImage(engine, obj->mRenderObject, person_allArray[obj->index - 1][0][2 * obj->state - 2 + (obj->hurtTime>20)]);
        }
        if(frames % 4 == 3)
        {
            Engine_Render_changeObjectImage(engine, obj->mRenderObject, person_allArray[obj->index - 1][0][2 * obj->state - 1 + (obj->hurtTime>20)]);
        }
    }

    if(obj->mWeapon != NULL)
    {
        obj->mWeapon->posX = obj->posX;
        obj->mWeapon->posY = obj->posY;
        obj->mWeapon->update(obj->mWeapon, engine);
    }
    obj->mRenderObject->setPos(obj->mRenderObject, obj->posX, obj->posY);
    //obj->mWeaponObject->setPos(obj->mWeaponObject, obj->posX, obj->posY);
    if(obj->cd != 0) obj->cd--;
    if(obj->hurtTime != 0) obj->hurtTime--;
    else
    {
        obj->state = 1;
    }
    //printf("set finished!\n");
    // person died
    if(obj->HP==0){
        
    }
}

void personAttack(Person* obj, Bullet* bullets[], Engine* engine){
    if(obj->cd == 0){
        switch(obj->weapon_type)
        {
            case 1:// pistol
                for(int i = 0; i < 20; i++)
                {
                    if(bullets[i] == NULL)
                    {
                        if(Engine_Joystick_notZero(engine))
                        {
                            bullets[i] = newBullet(engine, obj, Engine_Joystick_getAngle(engine));
                        }
                        else
                        {
                            bullets[i] = newBullet(engine, obj, (obj->oriX > 0) ? 0 : 180);
                        }
                        Engine_Render_addObject(engine, bullets[i]->mRenderObject);
                        break;
                    }
                }
                obj->cd = 5;
                // obj->speed = 10;
                break;
            
            case 2://2->shotgun
                for(int i = 0; i < 20; i++)
                {
                    if(bullets[i] == NULL)
                    {
                        if(Engine_Joystick_notZero(engine))
                        {
                            bullets[i] = newBullet(engine, obj, Engine_Joystick_getAngle(engine));
                        }
                        else
                        {
                            bullets[i] = newBullet(engine, obj, (obj->oriX > 0) ? 0 : 180);
                        }
                        Engine_Render_addObject(engine, bullets[i]->mRenderObject);
                        break;
                    }
                }
                obj->cd = 2;
                // obj->speed = 15;
                break;
            
            case 3://3->submachine
                int count = 0;
                double angle;
                if(Engine_Joystick_notZero(engine))
                {
                    angle = Engine_Joystick_getAngle(engine);
                }
                else
                {
                    angle = (obj->oriX > 0) ? 0 : 180;
                }
                for(int i = 0; i < 20; i++)
                {
                    if(bullets[i] == NULL)
                    {
                        bullets[i] = newBullet(engine, obj, angle + 5 * (count - 1));
                        Engine_Render_addObject(engine, bullets[i]->mRenderObject);
                        count++;
                    }
                    if(count == 3) break;
                }
                obj->cd = 8;
                // obj->speed = 20;
                break;

            default:
        }
    }
    else
        return;
}

bool personDamage(Person* obj, Bullet* bullet)
{
    int cenX = bullet->posX + 1;
    int cenY = bullet->posY + 1;
    if((obj->posX + 20 <= cenX && cenX <= obj->posX + 30)
        && (obj->posY + 5 <= cenY && cenY <= obj->posY + 15))
    {
        obj->HP = (obj->HP >= 10) ? (obj->HP - 10) : 0;
        obj->state = 2;
        obj->hurtTime = 30;
        return true;
    }
    else if((obj->posX + 15 <= cenX && cenX <= obj->posX + 35)
            && (obj->posY <= cenY && cenY <= obj->posY + 20))
    {
        obj->HP = (obj->HP >= 5) ? (obj->HP - 5) : 0;
        obj->state = 2;
        obj->hurtTime = 30;
        return true;
    }
    else if((obj->posX + 15 <= cenX && cenX <= obj->posX + 35)
            && (obj->posY <= cenY && cenY <= obj->posY + 35))
    {
        obj->HP = (obj->HP >= 2) ? (obj->HP - 2) : 0;
        obj->state = 2;
        obj->hurtTime = 30;
        return true;
    }
    else if((obj->posX + 15 <= cenX && cenX <= obj->posX + 35)
        && (obj->posY <= cenY && cenY <= obj->posY + 50))
    {
        obj->HP = (obj->HP >= 1) ? (obj->HP - 1) : 0;
        obj->state = 2;
        obj->hurtTime = 30;
        return true;
    }
    else return false;
}

void personHoldWeapon(Person* obj, Weapon* weapon)
{
    obj->mWeapon = weapon;
    obj->weapon_type = weapon->weaponType;
}

void personReleaseWeapon(Person* obj)
{
    if(obj->mWeapon != NULL)
    {
        obj->mWeapon->setAvailable(obj->mWeapon, 0);
        obj->mWeapon = NULL;
        obj->weapon_type = 4;
    }
}

Person* newPerson(Engine* engine, int16_t posX, int16_t posY, uint8_t index)
{
    Person* obj = calloc(1, sizeof(Person));
    obj->move = personMove;
    obj->jump = personJump;
    obj->attack = personAttack;
    obj->damage = personDamage;
    obj->update = personUpdate;
    obj->holdWeapon = personHoldWeapon;
    obj->releaseWeapon = personReleaseWeapon;

    obj->state = 1; //1->normal 2->damaged >=3->invincible (decaded by frames)
    obj->oriX = (index == 1 ? 1 : -1);
    obj->oriY = 0; //oriY=0 -> stand on the floor
    obj->hurtTime = 0;
    obj->HP = 100;
    obj->index = index;
    obj->weapon_type = 4;
    obj->cd = 0;// cd=0 -> person can attack
    obj->posX = posX;
    obj->posY = posY;
    obj->mRenderObject = Engine_Render_newObject(engine, person_allArray[obj->index - 1][1][2 * obj->state - 2], posX, posY, 1);
    //obj->mWeaponObject = Engine_Render_newObject(engine, "weapon1-l", posX, posY, 1);

    return obj;
}

void deletePerson(Person* obj, Engine* engine)
{
    Engine_Render_deleteObject(engine, obj->mRenderObject);
    //Engine_Render_deleteObject(engine, obj->mWeaponObject);

}

#endif // _PERSON_C_