/* This Source Code Form is subject to the terms of the Mozilla
 * Public License, v. 2.0. If a copy of the MPL was not distributed
 * with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2021 Ilya Zemskov */

#ifndef ENGINE__H
#define ENGINE__H

#include "vector.h"
#include "point.h"
#include "edge.h"
#include "model3d.h"

#ifdef LOW_RESOLUTION_MODE
    #define SCREEN_WIDTH  30
    #define SCREEN_HEIGHT 30
    #define HALF_SCREEN_WIDTH  15
    #define HALF_SCREEN_HEIGHT 15
#else
    /*#define SCREEN_WIDTH  256
    #define SCREEN_HEIGHT 192
    #define HALF_SCREEN_WIDTH  128
    #define HALF_SCREEN_HEIGHT 96*/

    #define SCREEN_WIDTH  30
    #define SCREEN_HEIGHT 30
    #define HALF_SCREEN_WIDTH  15
    #define HALF_SCREEN_HEIGHT 15
#endif

#ifdef LOW_RESOLUTION_MODE
    #ifdef ALTLOWGFX  
        #define ddraw(x,y,x1,y1,c) cdraw(2*(x),y,2*(x1),y1,c);
    #else
        #define ddraw(x,y,x1,y1,c) cdraw(x,2*(y),x1,2*(y1),c);
    #endif
#endif

#define SCREEN_DEPTH  50

void drawLine(int x1, int y1, int x2, int y2);
void drawVector(struct Vector * vector);
void drawPoint(struct Point * point);
void drawModel3D(struct Model3D * model3d);
void processModel(struct Model3D * model3d);

void initContext();

#endif
