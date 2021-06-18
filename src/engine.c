/* This Source Code Form is subject to the terms of the Mozilla
 * Public License, v. 2.0. If a copy of the MPL was not distributed
 * with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2021 Ilya Zemskov */

//#include <graphics.h>
#include <stdio.h>

#include "vector.h"
#include "point.h"

#include "engine.h"

void drawLine(int x1, int y1, int x2, int y2) {
	draw(x1, y1, x2, y2);
}

void drawPoint(struct Point * point) {
    if (point == NULL)
        return ;

    printf("%d,%d,%d\n", point->x, point->y, point->z);
}

/*void drawVector(struct Vector * vector) {
    if (vector == NULL)
        return ;

    printf("%d,%d,%d", vector->x, vector->y, vector->z);
}*/

void initContext() {
	clg();
}
