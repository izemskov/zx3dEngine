/* This Source Code Form is subject to the terms of the Mozilla
 * Public License, v. 2.0. If a copy of the MPL was not distributed
 * with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2021 Ilya Zemskov */

/*
	Compile program cmd:
		zcc +zx -lndos -lmzx -v -create-app -o zx3dEngine main.c engine.c point.c vector.c model3d.c linear_alg.c
			+zx - Target
			-v - Verbose
			-lndos - Link with library ndos

		zcc +zx -lndos -lmzx -v -create-app -DLOW_RESOLUTION_MODE -o zx3dEngine main.c engine.c point.c vector.c model3d.c linear_alg.c
*/

#ifdef LOW_RESOLUTION_MODE
#define bufferedgfx 1

#include <zxlowgfx.h>
#endif

#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "engine.h"
#include "linear_alg.h"

long heap;

int main() {
	mallinit();
	sbrk(30000, 6000);

	initContext();	

	struct Model3D * model = createCube();	

#ifndef LOW_RESOLUTION_MODE
	model->center.z = 15;
#endif

	//model->angleY += 10;
	//processModel(model);

	model->angleX = 0;
	model->angleY = 0;

	int i = 0;
	while (1) {	
		processModel2(model);
		clearScreen();
		drawModel3D(model);

		//csleep(4);

		model->angleY += 10;
		if (model->angleY >= 360) 
			model->angleY = model->angleY - 360;

		model->angleX += 10;
		if (model->angleX >= 360) 
			model->angleX = model->angleX - 360;
		
		paintBuffer();		
	}
	deleteModel(model);	

	//double a = -0.01;

	//printf("%f\n", a);
	//printf("%f\n", fabs(a));

	//printf("ok\n");

	/*struct Point * point1 = newPoint(1, 2, 1);
	struct Point * point2 = newPoint(0, 4, 4);
	struct Vector * vector1 = newVector(2, 0, 0);
	struct Vector * vector2;	

	drawPoint(point1);
	drawPoint(point2);

	vector2 = subtractPointFromPoint(point1, point2);

	addVectorToVector(vector1, vector2);

	addVectorToPoint(point1, vector1);

	drawPoint(point1);

	subtractVectorFromPoint(point2, vector2);

	drawPoint(point2);*/	

	return 0;
}
