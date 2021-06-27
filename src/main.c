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
	sbrk(30000, 6000);

	initContext();	

	struct Model3D * model = createCube();	

#ifndef LOW_RESOLUTION_MODE
	model->center.z = 15;
#else
	model->center.y = -10;
	model->center.z = 40;
#endif

	model->angleX = 0;
	model->angleY = 0;

	int i = 0;
	while (1) {	
		processModel(model);
		clearScreen();
		drawModel3D(model);

		csleep(4);

		model->angleY += 10;
		if (model->angleY >= 360) 
			model->angleY = model->angleY - 360;

		model->angleX += 10;
		if (model->angleX >= 360) 
			model->angleX = model->angleX - 360;
		
		paintBuffer();		
	}
	deleteModel(model);	

	return 0;
}
