/* This Source Code Form is subject to the terms of the Mozilla
 * Public License, v. 2.0. If a copy of the MPL was not distributed
 * with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2021 Ilya Zemskov */

/*
	Compile program cmd:
		zcc +zx -v -create-app -o zx3dEngine main.c engine.c point.c
*/

#include <malloc.h>
#include <stdio.h>

#include "engine.h"

long heap;

int main() {
	mallinit();
	sbrk(30000, 2000);

	int * a = (int *) malloc(20 * sizeof(int));

	a[0] = 20;
	a[1] = 20;
	a[2] = 30;
	a[3] = 40;

	initContext();

	drawLine(a[0], a[1], a[2], a[3]);

	free(a);		

	return 0;
}