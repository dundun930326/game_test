
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
<<<<<<< HEAD
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

    void (*move)(struct person*, int16_t, bool, bool);
=======
    // int attack;
    int HP;
    int state;
    int oriX;
    int oriY;
    int preX;
    int preY;
    int posX;
    int posY;
    int speedX;
    int speedY;// jump
    int weapon_type; // 1->pistol 2->shotgun 3->submachine
    int cd;

    void (*move)(struct person*, int16_t magX);
    void (*jump)(struct person*);
>>>>>>> 52d7500 (design gameflow)
    void (*update)(struct person*); //to update the state of a person.(cd--)
    void (*attack)(struct person*);
}Person;


<<<<<<< HEAD
void personMove(Person* obj, int speed_x, bool jump, bool downstair);//speed_x -> x data of joystick
=======
void personMove(Person* obj, int16_t magX);
void personJump(Person* obj);
>>>>>>> 52d7500 (design gameflow)
void personUpdate(Person* obj);
void personAttack(Person* obj);
Person* newPerson(Engine* engine, int16_t posX, int16_t posY);
void deletePerson(Person* obj, Engine* engine);

#endif // _PERSON_H_
