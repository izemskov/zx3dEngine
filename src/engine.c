/* This Source Code Form is subject to the terms of the Mozilla
 * Public License, v. 2.0. If a copy of the MPL was not distributed
 * with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2021 Ilya Zemskov */

#include <graphics.h>
#include <stdio.h>
#include <math.h>

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

void drawModel3D(const struct Model3D * model3d) {
	if (model3d == NULL)
		return;		

	for (int i = 0; i < model3d->edgesCount; i++) {
		int xs, ys, xe, ye;

		int x = model3d->vertices[model3d->edges[i].src].x + model3d->center.x;
		int y = model3d->vertices[model3d->edges[i].src].y + model3d->center.y;
		int z = model3d->vertices[model3d->edges[i].src].z + model3d->center.z;
	
		xs = HALF_SCREEN_WIDTH + SCREEN_DEPTH * x / z;
		ys = HALF_SCREEN_HEIGHT + SCREEN_DEPTH * y / z;

		x = model3d->vertices[model3d->edges[i].dst].x + model3d->center.x;
		y = model3d->vertices[model3d->edges[i].dst].y + model3d->center.y;
		z = model3d->vertices[model3d->edges[i].dst].z + model3d->center.z;
		
		xe = HALF_SCREEN_WIDTH + SCREEN_DEPTH * x / z;
		ye = HALF_SCREEN_HEIGHT + SCREEN_DEPTH * y / z;

		drawLine(xs, ys, xe, ye);
	}
}

void initContext() {
	clg();
}
