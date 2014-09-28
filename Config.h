#ifndef __CONFIG_H__
#define __CONFIG_H__
//
//  Config.h
//  World
//
//  Created by shuhei_komino on 2014/09/15.
//
//

#include <stdio.h>
#include "cocos2d.h"

// Debug mode management
#define DEBUG_MODE true

// Setting common font
#define GAME_FONT "HiraKakuProN-W6"

// Living Things max~min lifes
#define P_MIN_LIFE 7000
#define P_MAX_LIFE 8000
#define H_MIN_LIFE 4000
#define H_MAX_LIFE 5000
#define C_MIN_LIFE 5000
#define C_MAX_LIFE 6000


enum zOrder
{
    zBackground,
    zPlant,
    zHerbivore,
    zCarnivore,
};

enum initNumber
{
    initNumC = 5,
    initNumH = 40,
    initNumP = 30,
};

enum sex
{
    male,
    female,
};

#endif