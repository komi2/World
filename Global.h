#ifndef __GLOBAL_H__
#define __GLOBAL_H__

//
//  Global.h
//  World
//
//  Created by shuhei_komino on 2014/10/03.
//
//

#include <stdio.h>
#include "cocos2d.h"
#include "Config.h"

class Global
{
public:
    // Living Things visual flag
    bool isVisualList[2];
    
    // Window size
    cocos2d::Size winSize;
    
    void switchVisual(int lType);
};

extern Global* G;

#endif


