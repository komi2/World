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


#endif