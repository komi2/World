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

// Initial amount of Living Things
#define INIT_AMOUNT_C 10
#define INIT_AMOUNT_H 30
#define INIT_AMOUNT_P 60

// Visual angle
// Normal
#define VISUAL_DISTANCE_H 70
#define VISUAL_WIDTH_H 50
#define VISUAL_DISTANCE_C 70
#define VISUAL_WIDTH_C 20
// Hunting
#define VISUAL_DISTANCE_HUNTING_H 80
#define VISUAL_WIDTH_HUNTING_H 90
#define VISUAL_DISTANCE_HUNTING_C 180
#define VISUAL_WIDTH_HUNTING_C 25

// Living Things max~min lifes
#define MIN_LIFE_P 7000
#define MAX_LIFE_P 9000
#define MIN_LIFE_H 4000
#define MAX_LIFE_H 8000
#define MIN_LIFE_C 5000
#define MAX_LIFE_C 8000

// Living Things max~min nutrition
#define MIN_NUTRITION_P 5000
#define MAX_NUTRITION_P 7000
#define MIN_NUTRITION_H 4500
#define MAX_NUTRITION_H 7000
#define MIN_NUTRITION_C 3000
#define MAX_NUTRITION_C 6000

// Living Things speed
#define NORMAL_SPPED_H 1.0
#define RUNNING_SPEED_H 1.3
#define NORMAL_SPPED_C 1.0
#define RUNNING_SPEED_C 1.5

// BG Color
#define WORLD_COLOR cocos2d::Color4B::Color4B(cocos2d::Color3B::Color3B(51, 51, 51))

// Status Normal
#define CL_NORAML_P cocos2d::Color4F::Color4F(cocos2d::Color3B::Color3B(98, 237, 0))
#define CL_NORAML_H cocos2d::Color4F::Color4F(cocos2d::Color3B::Color3B(0, 93, 255))
#define CL_NORAML_C cocos2d::Color4F::Color4F(cocos2d::Color3B::Color3B(229, 0, 65))
// Status Old
#define CL_OLD_P cocos2d::Color4F::Color4F(cocos2d::Color3B::Color3B(119, 135, 1))
#define CL_OLD_H cocos2d::Color4F::Color4F(cocos2d::Color3B::Color3B(39, 125, 142))
#define CL_OLD_C cocos2d::Color4F::Color4F(cocos2d::Color3B::Color3B(127, 24, 77))

// Status Breeding
#define CL_BREEDING_H cocos2d::Color4F::Color4F(cocos2d::Color3B::Color3B(0, 177, 247))
#define CL_BREEDING_C cocos2d::Color4F::Color4F(cocos2d::Color3B::Color3B(255, 0, 195))

#define BREEDING_MIN_AMOUNT_H 2
#define BREEDING_MAX_AMOUNT_H 4
#define BREEDING_MIN_AMOUNT_C 1
#define BREEDING_MAX_AMOUNT_C 3

// Max amount of breedable number in one season
#define BREEDABLE_MAX_AMOUNT 2

// turning point
#define OLD_POINT 500

// Hunting point
#define HUNTING_POINT 2000

// Nutrition division point
#define NUTRITION_DIV_POINT 3

// Span of breeding
#define F_BREEDING 1500

// Eating amount of necessity breeding
#define GOAL_EATING_AMOUNT 1


enum zOrder
{
    zBackground,
    zPlant,
    zHerbivore,
    zCarnivore,
    zVision,
    zButton,
    zMenuLayer,
    zMenuItems
};

// Type of Living Things
enum livingThingsType
{
    lTypeC,
    lTypeH,
    lTypeP,
};

enum sexType
{
    male,
    female,
};

enum causeOfDeath
{
    naturalDeath,
    prey,
    starvation,
};

enum DNAType
{
    dBehavior,
    dVision,
};

enum behaviorType
{
    loneWolf,
    collective,
    laziness,
};

enum visionType
{
    visNone,
    visSearching,
};

#endif