//
//  Global.cpp
//  World
//
//  Created by shuhei_komino on 2014/10/03.
//
//

#include "Global.h"

Global* G = new Global;

void Global::switchVisual(int lType)
{
    isVisualList[lType] = ( isVisualList[lType] ) ? false : true ;
}