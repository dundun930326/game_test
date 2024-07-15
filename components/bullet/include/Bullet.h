#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#ifndef _BULLET_H_
#define _BULLET_H_


#include "../../engine/include/Engine.h"
#include "../../person/include/Person.h"




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


bool bulletMove(Bullet* obj);// return whether the bullet is alive
void bulletNew(Person* person, Bullet* obj, int16_t angle); // create a bullet from the position of a person

#endif // _BULLET_H_
