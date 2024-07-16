
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
    int oriY;
    int preX;
    int preY;
    int posX;
    int posY;
    int speedX;
    int speedY;// jump
    int weapon_type; // 1->pistol 2->shotgun 3->submachine
    int cd;// frames

<<<<<<< HEAD
    void (*move)(struct person*, int16_t magX);
    void (*jump)(struct person*);
=======
    void (*move)(struct person*, int16_t, bool, bool);
>>>>>>> b9a4dc4 (the function of person)
    void (*update)(struct person*); //to update the state of a person.(cd--)
    void (*attack)(struct person*);
}Person;


<<<<<<< HEAD
void personMove(Person* obj, int16_t magX);
void personJump(Person* obj);
=======
void personMove(Person* obj, int speed_x, bool jump, bool downstair);//speed_x -> x data of joystick
>>>>>>> b9a4dc4 (the function of person)
void personUpdate(Person* obj);
void personAttack(Person* obj);
Person* newPerson(Engine* engine, int16_t posX, int16_t posY);
void deletePerson(Person* obj, Engine* engine);

#endif // _PERSON_H_
