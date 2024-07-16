
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
    // int attack;
    uint8_t HP;
    uint8_t state;
    int8_t oriX;
    int oriY;
    int preX;
    int preY;
    int posX;
    int posY;
    int speedX;
    int speedY;// jump
    int weapon_type; // 1->pistol 2->shotgun 3->submachine
    int cd;// frames

    void (*move)(struct person*, int16_t magX);
    void (*jump)(struct person*);
    int cd;
    void (*update)(struct person*); //to update the state of a person.(cd--)
    void (*attack)(struct person*);
}Person;


void personMove(Person* obj, int16_t magX);
void personJump(Person* obj);
void personUpdate(Person* obj);
void personAttack(Person* obj);
Person* newPerson(Engine* engine, int16_t posX, int16_t posY);
void deletePerson(Person* obj, Engine* engine);

#endif // _PERSON_H_
