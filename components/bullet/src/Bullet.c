#include "Bullet.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

bool bulletMove(Bullet* obj){ // return whether the bullet is alive

    obj->posX += cos(obj->angle) * obj->speed;
    obj->posY -= sin(obj->angle) * obj->speed;
    
    if(obj->posX<0 || obj->posY<0 || obj->posX>320 || obj->posY > 240){
        return false;
    }
    return true;

}
void bulletNew(Person* person, Bullet* obj, int16_t angle){

    obj->new = bulletNew;
    obj->move = bulletMove;

     //weapon
    //1->pistol speed=10 cd = 4 angle = 0 or 180
    //2->shotgun speed = 15 cd = 10 angle = 0, 30, -30 or 180 210 -210 (3*bullet)
    //3->submachine speed = 20 cd = 2 angle = 0 or 180
    obj->posX = person->posX;
    obj->posY = person->posY;
    obj->angle = angle;

    switch (person->weapon_type)
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