#ifndef _PERSON_C_
#define _PERSON_C_

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "Person.h"

#define PI 3.14159265

extern const char* person_allArray[2][2][6];

void personMove(Person* obj, int16_t magX)
{
    if((obj->oriX < 0 && magX > 0)
        ||(obj->oriX > 0 && magX < 0))
    {
        obj->oriX *= -1;
    }
    if(!obj->stick) obj->speedX = magX / 3072 + obj->hurtPenalty;
    else obj->speedX = 0;
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
        obj->oriY = 1; //stand on the floor
    }
    else if(obj->mRenderObject->mPosY + (-1 * obj->speedY) <= 0)
    {
        obj->posY = 0;
        obj->speedY = 0;
        obj->oriY = -1; //hit the ceiling
        //printf("hit ceiling!!!\n");
    }
    else if (obj->speedY<=0 && obj->mRenderObject->mPosY + 50 >= 170 && obj->mRenderObject->mPosY + 50 <= 170+15){
        
        if((obj->posX + 25 >= 20 && obj->posX + 25 <= 100)||(obj->posX + 25 >= 20+200 && obj->posX + 25 <= 100+200)){
            obj->posY = 170 - 50;
            obj->speedY = 0;
            obj->oriY = 1;
        }else{
            obj->posY -= obj->speedY;
            obj->speedY -= obj->accel;
            obj->oriY = 0;
        }
    }
    else if (obj->speedY<=0 && obj->mRenderObject->mPosY + 50 >= 115 && obj->mRenderObject->mPosY + 50 <= 115+15){
        
        if((obj->posX + 25 >= 60 && obj->posX + 25 <= 140)||(obj->posX + 25 >= 180 && obj->posX + 25 <= 260)){
            obj->posY = 115 - 50;
            obj->speedY = 0;
            obj->oriY = 1;
        }else{
            obj->posY -= obj->speedY;
            obj->speedY -= obj->accel;
            obj->oriY = 0;
        }
    }
    else if (obj->speedY<=0 && obj->mRenderObject->mPosY + 50 >= 60 && obj->mRenderObject->mPosY + 50 <= 15+60){
        
        if((obj->posX + 25 >= 120 && obj->posX + 25 <= 200)){
            obj->posY = 60 - 50;
            obj->speedY = 0;
            obj->oriY = 1;
        }else{
            obj->posY -= obj->speedY;
            obj->speedY -= obj->accel;
            obj->oriY = 0;
        }
    }
    else
    {
        obj->posY -= obj->speedY;
        obj->speedY -= obj->accel;
        obj->oriY = 0;
    }
    if(obj->speedY >= -15) obj->speedY--;

    //printf("posX: %d, posY: %d, oriX: %d, oriY: %d\n", obj->posX, obj->posY, obj->oriX, obj->oriY);
    
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
    obj->mItemObject->setPos(obj->mItemObject, obj->posX, obj->posY);
    if(obj->cd != 0) obj->cd--;

    if(obj->hurtTime != 0) obj->hurtTime--;
    else
    {
        if(obj->state == 2) obj->state = 1;
    }
    if(obj->hurtPenalty > 0) obj->hurtPenalty--;
    else if(obj->hurtPenalty < 0) obj->hurtPenalty++;

    if(obj->itemTime != 0) obj->itemTime--;
    else
    {
        if(obj->state == 3) obj->state = 1;
    }

    if(obj->powerTime >= 1)
    {
        obj->powerTime--;
        if(obj->powerTime == 0)
        {
            obj->power = false;
            if(obj->index == 2)
            {
                obj->mRenderObject->setVisible(obj->mRenderObject, 1);
                obj->mItemObject->setVisible(obj->mRenderObject, 1);
                if(obj->mWeapon != NULL) obj->mWeapon->mRenderObject->setVisible(obj->mRenderObject, 1);
            }
        }
    }
    
    //printf("now power duration to %d\n", obj->powerTime);
    //printf("now state: %d\n", obj->state);
    // person died
    if(obj->HP==0){
        
    }
}

void personUpdateData(Person* obj, Engine* engine, ConnectionData* data)
{
    
    if(obj->HP != data->player_HP)
    {
        obj->HP = data->player_HP;
        obj->HPchange = true;
    }
    //obj->HP = abs(obj->HP - data->player_HP) <= 10 ? data->player_HP : obj->HP;
    obj->state = (1 <= data->player_state && data->player_state <= 3) ? data->player_state : obj->state;
    obj->oriX = data->player_oriX;
    obj->oriY = data->player_oriY;
    obj->posX = data->player_posX;
    obj->posY = data->player_posY;
    //obj->posX = abs(obj->posX - data->player_posX) <= 20 ? data->player_posX : obj->posX;
    //obj->posY = abs(obj->posY - data->player_posY) <= 20 ? data->player_posY : obj->posY;
    obj->speedX = data->player_speedX;
    obj->speedY = data->player_speedY;
    obj->weapon_type = data->player_weapon_type;
    //printf("update P2's information!!\n");
}

void personAttack(Person* obj, Bullet* bullets[], Engine* engine, double angle, Game* game){
    if(obj->cd == 0 || (obj->power && obj->person_type == 3)){
        double bestAngle;
        if(obj->index == 1)
        {
            bestAngle = atan2(game->player1->posY - game->player2->posY, game->player2->posX - game->player1->posX) * 180 / PI;
        }
        else
        {
            bestAngle = atan2(game->player2->posY - game->player1->posY, game->player1->posX - game->player2->posX) * 180 / PI;
        }
        //printf("bestAngle: %f\n", bestAngle);
        switch(obj->weapon_type)
        {
            case 1:// pistol
                for(int i = 0; i < 20; i++)
                {
                    if(bullets[i] == NULL)
                    {
                        bullets[i] = newBullet(engine, obj, (obj->power && obj->person_type == 1) ? bestAngle : angle);
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
                        bullets[i] = newBullet(engine, obj, (obj->power && obj->person_type == 1) ? bestAngle : angle);
                        Engine_Render_addObject(engine, bullets[i]->mRenderObject);
                        break;
                    }
                }
                obj->cd = 2;
                // obj->speed = 15;
                break;
            
            case 3://3->submachine
                int count = 0;
                for(int i = 0; i < 20; i++)
                {
                    if(bullets[i] == NULL)
                    {
                        bullets[i] = newBullet(engine, obj, (obj->power && obj->person_type == 1) ? (bestAngle + 5 * (count - 1)) : (angle + 5 * (count - 1)));
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

void personBigPower(Person* obj, Bullet* bullets[], Engine* engine, double angle)
{
    obj->power = true;
    switch(obj->person_type)
    {
        case 0: //Sasge: Disappear
            if(obj->index == 2)
            {
                obj->mRenderObject->setVisible(obj->mRenderObject, 0);
                Engine_Render_render(engine, obj->mRenderObject);
                obj->mItemObject->setVisible(obj->mItemObject, 0);
                Engine_Render_render(engine, obj->mItemObject);
                if(obj->mWeapon != NULL)
                {
                    obj->mWeapon->mRenderObject->setVisible(obj->mWeapon->mRenderObject, 0);
                    Engine_Render_render(engine, obj->mWeapon->mRenderObject);
                }
            }
            obj->powerTime = 80;
            break;

        case 1: //Musk: Auto aim ???
            obj->powerTime = 80;
            break;

        case 2: //English: 15 bullet at once
            int count = 0;
            for(int i = 0; i < 20; i++)
            {
                if(bullets[i] == NULL)
                {
                    bullets[i] = newBullet(engine, obj, 24 * count);
                    Engine_Render_addObject(engine, bullets[i]->mRenderObject);
                    count++;
                }
                if(count == 16) break;
            }
            break;

        case 3: //Pie: No CD
            obj->powerTime = 40;
            break;

        case 4: //Anya: Reverse bullet
            obj->powerTime = 80;
            break;
    }
}

bool personDamage(Person* obj, Bullet* bullet, Bullet* bullets[], Engine* engine)
{
    int cenX = bullet->posX + 1;
    int cenY = bullet->posY + 1;
    if((obj->posX + 15 <= cenX && cenX <= obj->posX + 35)
        && (obj->posY <= cenY && cenY <= obj->posY + 50)
        && obj->state == 1)
    {
        if(obj->power && obj->person_type == 4)
        {
            for(int i = 0; i < 20; i++)
            {
                if(bullets[i] == NULL)
                {
                    bullets[i] = newBullet(engine, obj, bullet->angle + 180);
                    Engine_Render_addObject(engine, bullets[i]->mRenderObject);
                    break;
                }
            }
            return true;
        }
        else
        {
            obj->HPchange = true;
            obj->state = 2;
            obj->hurtTime = HURTTIME_DURATION;
            obj->hurtPenalty = 15 * cos(bullet->angle * PI / 180);
            obj->speedY += 15 * sin(bullet->angle * PI / 180);
            obj->dropWeapon(obj);
            if((obj->posX + 20 <= cenX && cenX <= obj->posX + 30)
                && (obj->posY + 5 <= cenY && cenY <= obj->posY + 15))
            {
                obj->HP = (obj->HP >= 10) ? (obj->HP - 10) : 0;
                return true;
            }
            else if((obj->posX + 15 <= cenX && cenX <= obj->posX + 35)
                && (obj->posY <= cenY && cenY <= obj->posY + 20))
            {
                obj->HP = (obj->HP >= 5) ? (obj->HP - 5) : 0;
                return true;
            }
            else if((obj->posX + 15 <= cenX && cenX <= obj->posX + 35)
                && (obj->posY <= cenY && cenY <= obj->posY + 35))
            {
                obj->HP = (obj->HP >= 2) ? (obj->HP - 2) : 0;
                return true;
            }
            else
            {
                obj->HP = (obj->HP >= 1) ? (obj->HP - 1) : 0;
                return true;
            }
        }
    }
    else return false;
}

void personHoldWeapon(Person* obj, Weapon* weapon)
{
    obj->mWeapon = weapon;
    obj->weapon_type = weapon->weaponType;
}

//change weapon due to obtaining a new one
void personReleaseWeapon(Person* obj)
{
    if(obj->mWeapon != NULL)
    {
        obj->mWeapon->setAvailable(obj->mWeapon, 0);
        obj->mWeapon = NULL;
        obj->weapon_type = 4;
    }
}

//change weapon due to damaged
void personDropWeapon(Person* obj)
{
    // if(obj->mWeapon != NULL)
    // {
    //     obj->mWeapon->drop(obj->mWeapon);
    //     obj->mWeapon = NULL;
    //     obj->weapon_type = 4;
    // }
}

void personObtainItem(Person* obj)
{
    obj->item = 1;
    obj->mItemObject->setVisible(obj->mItemObject, 1);
}

void personUseItem(Person* obj)
{
    if(obj->item == 1)
    {
        obj->item = 0;
        obj->state = 3;
        obj->itemTime = ITEMTIME_DURATION;
        obj->mItemObject->setVisible(obj->mItemObject, 0);
    }
}

Person* newPerson(Engine* engine, int16_t posX, int16_t posY, uint8_t index, uint8_t type)
{
    Person* obj = calloc(1, sizeof(Person));
    obj->move = personMove;
    obj->jump = personJump;
    obj->attack = personAttack;
    obj->bigPower = personBigPower;
    obj->damage = personDamage;
    obj->update = personUpdate;
    obj->updateData = personUpdateData;
    obj->holdWeapon = personHoldWeapon;
    obj->releaseWeapon = personReleaseWeapon;
    obj->dropWeapon = personDropWeapon;
    obj->obtainItem = personObtainItem;
    obj->useItem = personUseItem;
    obj->state = 1; //1->normal 2->damaged >=3->invincible (decaded by frames)
    obj->stick = 0;
    obj->oriX = (index == 1 ? 1 : -1);
    obj->oriY = 1; //oriY=1 -> stand on the floor
    obj->hurtTime = 0;
    obj->hurtPenalty = 0;
    obj->itemTime = 0;
    obj->powerTime = 0;
    obj->power = false;
    obj->HPchange = false;
    obj->accel = 1;
    obj->HP = 100;
    obj->index = index;
    //weapon type
    obj->weapon_type = 4;
    obj->person_type = type;
    obj->cd = 0;// cd=0 -> person can attack
    obj->posX = posX;
    obj->posY = posY;
    obj->item = 0;
    obj->mRenderObject = Engine_Render_newObject(engine, person_allArray[obj->index - 1][1][2 * obj->state - 2], posX, posY, 1);
    obj->mItemObject = Engine_Render_newObject(engine, "item", posX, posY, 0);

    return obj;
}

void deletePerson(Person* obj, Engine* engine)
{
    if(obj != NULL)
    {
        Engine_Render_deleteObject(engine, obj->mRenderObject);
        Engine_Render_deleteObject(engine, obj->mItemObject);
        free(obj);
    }
}

#endif // _PERSON_C_