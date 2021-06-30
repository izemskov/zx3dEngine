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

		zcc +zx -lndos -lmzx -v -create-app -DORTHOGONAL_MODE -o zx3dEngine main.c engine.c point.c vector.c model3d.c linear_alg.c
		zcc +zx -lndos -lmzx -v -create-app -DLOW_RESOLUTION_MODE -o zx3dEngine main.c engine.c point.c vector.c model3d.c linear_alg.c
		zcc +zx -lndos -lmzx -v -create-app -DLOW_RESOLUTION_MODE -DORTHOGONAL_MODE -o zx3dEngine main.c engine.c point.c vector.c model3d.c linear_alg.c
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
	sbrk(25000, 25000);

	initContext();	

	struct Model3D * model = createCube();	
	struct Model3D * model2 = createOctahedron();	

#ifndef LOW_RESOLUTION_MODE
	model->center.z = 15;
#else	
	model->center.y = -10;
	model->center.z = 40;

	model2->center.y = -10;
	model2->center.z = 45;
#endif

	setAngleX(model, 0);
	setAngleY(model, 0);

	setAngleX(model2, 0);
	setAngleY(model2, 0);

	int i = 0;
	while (1) {	
		processModel(model);
		//processModel(model2);
		clearScreen();
		drawModel3D(model);
		//drawModel3D(model2);

		csleep(4);

		setAngleY(model, model->angleY + 10);	
		setAngleY(model2, model2->angleY + 10);		

		paintBuffer();
	}
	deleteModel(model);	
	deleteModel(model2);	

	return 0;
}
