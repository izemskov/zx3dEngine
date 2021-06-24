/* This Source Code Form is subject to the terms of the Mozilla
 * Public License, v. 2.0. If a copy of the MPL was not distributed
 * with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2021 Ilya Zemskov */

#ifndef LOW_RESOLUTION_MODE
#include <graphics.h>
#endif

#include <stdio.h>
#include <math.h>

#include "linear_alg.h"

#include "engine.h"

void drawLine(int x1, int y1, int x2, int y2) {
#ifdef LOW_RESOLUTION_MODE
	ddraw(x1, y1, x2, y2, 6);
#else
	draw(x1, y1, x2, y2);
#endif
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

void processModel(struct Model3D * model3d) {
	if (model3d == NULL)
		return;	

	if (model3d->angleY != model3d->oldAngleY) {
		getRotateOYMatrix(model3d->rotateMatrixY, model3d->angleY);
	}

	for (int i = 0; i < model3d->verticesCount; i++) {
		model3d->processedVerticies[i].x = model3d->vertices[i].x;
		model3d->processedVerticies[i].y = model3d->vertices[i].y;
		model3d->processedVerticies[i].z = model3d->vertices[i].z;
		
		multMatrixPoint(model3d->rotateMatrixY, &model3d->processedVerticies[i]);

		model3d->processedVerticies[i].x = model3d->processedVerticies[i].x + model3d->center.x;
		model3d->processedVerticies[i].y = model3d->processedVerticies[i].y + model3d->center.y;
		model3d->processedVerticies[i].z = model3d->processedVerticies[i].z + model3d->center.z;

		//printf("x = %d; y = %d; z = %d\n", model3d->processedVerticies[model3d->edges[i].src].x, model3d->processedVerticies[model3d->edges[i].src].y, model3d->processedVerticies[model3d->edges[i].src].z);
	}
}

void drawModel3D(struct Model3D * model3d) {
	if (model3d == NULL)
		return;		

	for (int i = 0; i < model3d->edgesCount; i++) {
		int xs, ys, xe, ye;

		//printf("x = %d; y = %d; z = %d\n", model3d->processedVerticies[model3d->edges[i].src].x, model3d->processedVerticies[model3d->edges[i].src].y, model3d->processedVerticies[model3d->edges[i].src].z);
	
		xs = HALF_SCREEN_WIDTH + SCREEN_DEPTH * model3d->processedVerticies[model3d->edges[i].src].x / model3d->processedVerticies[model3d->edges[i].src].z;
		ys = HALF_SCREEN_HEIGHT + SCREEN_DEPTH * model3d->processedVerticies[model3d->edges[i].src].y / model3d->processedVerticies[model3d->edges[i].src].z;
		
		xe = HALF_SCREEN_WIDTH + SCREEN_DEPTH * model3d->processedVerticies[model3d->edges[i].dst].x / model3d->processedVerticies[model3d->edges[i].dst].z;
		ye = HALF_SCREEN_HEIGHT + SCREEN_DEPTH * model3d->processedVerticies[model3d->edges[i].dst].y / model3d->processedVerticies[model3d->edges[i].dst].z;

		drawLine(xs, ys, xe, ye);

		//printf("xs = %d; ys = %d; xe = %d; ye = %d\n", xs, ys, xe, ye);
	}
}

void initContext() {
#ifdef LOW_RESOLUTION_MODE
	cclg(0);
#else
	clg();
#endif	
}

void clearScreen() {
#ifdef LOW_RESOLUTION_MODE
	cclgbuffer(0);
#else
	clg();
#endif	
}

void paintBuffer() {
#ifdef LOW_RESOLUTION_MODE
	ccopybuffer();
#endif	
}
