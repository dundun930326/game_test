
#ifndef _PERSON_H_
#define _PERSON_H_

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "../../engine/include/Engine.h"

#define FPS 15

typedef struct person
{
    RenderObject *mRenderObject;
    RenderObject *mWeaponObject;

    // int attack;
    uint8_t HP;
    uint8_t state;
    int8_t oriX;
    int16_t oriY;
    int16_t posX;
    int16_t posY;
    int8_t weapon_type; // 1->pistol 2->shotgun 3->submachine
    int8_t cd;// frames

    void (*move)(struct person*, int16_t, int16_t);
    void (*update)(struct person*); //to update the state of a person.(cd--)
    void (*attack)(struct person*);
}Person;


void personMove(Person* obj, int speed_x, bool jump);
void personUpdate(Person* obj);
void personAttack(Person* obj);
Person* newPerson(Engine* engine, int16_t posX, int16_t posY);
void deletePerson(Person* obj, Engine* engine);

#endif // _PERSON_H_
