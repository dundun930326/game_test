#ifndef _PERSON_H_
#define _PERSON_H_

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "../../weapon/include/Weapon.h"
#include "../../engine/include/Engine.h"
#include "../../bullet/include/Bullet.h"

#define FPS 15

typedef struct weapon Weapon;
typedef struct bullet Bullet;

typedef struct person
{
    RenderObject *mRenderObject;
    //RenderObject *mWeaponObject;
    Weapon *mWeapon;

    //No. of the person
    uint8_t index;

    // int attack;
    uint8_t HP;
    uint8_t state; //1->normal 2->damaged >=3->invincible (decaded by frames)
    int8_t hurtTime;
    int8_t oriX;
    int16_t oriY;
    int16_t posX;
    int16_t posY;
    int16_t speedX;
    int16_t speedY;
    int8_t weapon_type; // 1->pistol 2->shotgun 3->submachine 4->none
    int8_t cd;// frames

    void (*move)(struct person*, int16_t);
    void (*jump)(struct person*);
    void (*update)(struct person*, Engine*, int); //to update the state of a person.(cd--)
    void (*attack)(struct person*, Bullet*[], Engine*);
    bool (*damage)(struct person*, Bullet*);
    void (*holdWeapon)(struct person*, Weapon*);
    void (*releaseWeapon)(struct person*);
}Person;


//void personMove(Person* obj, int speed_x, bool jump, bool downstair);//speed_x -> x data of joystick
void personMove(Person* obj, int16_t magX);//speed_x -> x data of joystick
void personUpdate(Person* obj, Engine* engine, int frames);
void personAttack(Person* obj, Bullet* bullets[], Engine* engine);
bool personDamage(Person* obj, Bullet* bullet);
void personHoldWeapon(Person* obj, Weapon* weapon);
void personReleaseWeapon(Person* obj);
Person* newPerson(Engine* engine, int16_t posX, int16_t posY, uint8_t index);
void deletePerson(Person* obj, Engine* engine);

#endif // _PERSON_H_
