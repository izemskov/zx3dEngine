/* This Source Code Form is subject to the terms of the Mozilla
 * Public License, v. 2.0. If a copy of the MPL was not distributed
 * with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2021 Ilya Zemskov */

/*
	Compile program cmd:
		zcc +zx -lndos -v -create-app -o zx3dEngine main.c engine.c point.c vector.c
			+zx - Target
			-v - Verbose
			-lndos - Link with library ndos
*/

#include <malloc.h>
#include <stdio.h>

#include "engine.h"
#include "vector.h"
#include "point.h"

long heap;

int main() {
	mallinit();
	sbrk(30000, 2000);

	struct Point * point1 = newPoint(1, 2, 1);
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

	drawPoint(point2);

	/*int * a = (int *) malloc(20 * sizeof(int));

	a[0] = 20;
	a[1] = 20;
	a[2] = 30;
	a[3] = 40;

	initContext();

	drawLine(a[0], a[1], a[2], a[3]);

	free(a);*/

	return 0;
}
