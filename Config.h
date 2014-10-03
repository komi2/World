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

// BG Color
#define WORLD_COLOR cocos2d::Color4B::Color4B(cocos2d::Color3B::Color3B(51, 51, 51))

// Status Normal
#define CL_NORAML_P cocos2d::Color4F::Color4F(cocos2d::Color3B::Color3B(98, 237, 0))
#define CL_NORAML_H cocos2d::Color4F::Color4F(cocos2d::Color3B::Color3B(0, 93, 255))
#define CL_NORAML_C cocos2d::Color4F::Color4F(cocos2d::Color3B::Color3B(229, 0, 65))
// Status Old
#define CL_OLD_P cocos2d::Color4F::Color4F(cocos2d::Color3B::Color3B(119, 135, 1))
#define CL_OLD_H cocos2d::Color4F::Color4F(cocos2d::Color3B::Color3B(7, 73, 127))
#define CL_OLD_C cocos2d::Color4F::Color4F(cocos2d::Color3B::Color3B(127, 0, 14))
// Status Breeding
#define CL_BREEDING_H cocos2d::Color4F::Color4F(cocos2d::Color3B::Color3B(0, 177, 247))
#define CL_BREEDING_C cocos2d::Color4F::Color4F(cocos2d::Color3B::Color3B(255, 0, 195))

#define OLD_POINT 500


enum zOrder
{
    zBackground,
    zPlant,
    zHerbivore,
    zCarnivore,
    zButton,
    zMenuLayer,
    zMenuItems
};

enum initNumber
{
    initNumC = 5,
    initNumH = 40,
    initNumP = 30,
};

// Type of Living Things
enum livingThingsType
{
    lTypeC,
    lTypeH,
    lTypeP,
};

enum sex
{
    male,
    female,
};


#endif