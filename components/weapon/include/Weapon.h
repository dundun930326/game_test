#ifndef _WEAPON_H_
#define _WEAPON_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "../../engine/include/Engine.h"
#include "../../person/include/Person.h"

typedef struct person Person;

typedef struct weapon
{
    RenderObject *mRenderObject;
    Person *owner;
    bool available;
    uint8_t remainTime;
    uint8_t weaponType;

    uint16_t posX;
    uint16_t posY;

    void (*setAvailable)(struct weapon*, bool);
    bool (*hit)(struct weapon*, Person*);
    void (*update)(struct weapon*, Engine*);
}Weapon;

void weaponSetAvailable(Weapon* obj, bool available);
bool weaponHit(Weapon* obj, Person* person);
void weaponUpdate(Weapon* obj, Engine* engine);
Weapon* newWeapon(Engine* engine, uint8_t weaponType, int16_t posX, int16_t posY);
void deleteWeapon(Weapon* obj, Engine* engine);

#endif // _WEAPON_H_
