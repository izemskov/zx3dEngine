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

#define SCREEN_WIDTH  256
#define SCREEN_HEIGHT 192
#define SCREEN_DEPTH  50

#define HALF_SCREEN_WIDTH  128
#define HALF_SCREEN_HEIGHT 96

void drawLine(int x1, int y1, int x2, int y2);
void drawVector(struct Vector * vector);
void drawPoint(struct Point * point);
void drawModel3D(const struct Model3D * model3d);

void initContext();

#endif
