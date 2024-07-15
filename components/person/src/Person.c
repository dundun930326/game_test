#include <stdio.h>
#include <stdint.h>
#include "Person.h"

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
void personUpdate(Person* obj){
    // person damaged
    

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
    obj->attack = personAttack;
    obj->jump = personJump;
    obj->update = personUpdate;
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
    return obj;
}

void deletePerson(Person* obj, Engine* engine)
{
    Engine_Render_deleteObject(engine, obj->mRenderObject);
}