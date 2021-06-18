/* This Source Code Form is subject to the terms of the Mozilla
 * Public License, v. 2.0. If a copy of the MPL was not distributed
 * with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2021 Ilya Zemskov */

#include <malloc.h>
#include <stdio.h>

#include "vector.h"

#include "point.h"

void addVectorToPoint(struct Point * point, const struct Vector * vector) {
	if (point == NULL || vector == NULL)
		return;

	point->x += vector->x;
	point->y += vector->y;
	point->z += vector->z;
}

void subtractVectorFromPoint(struct Point * point, const struct Vector * vector) {
	if (point == NULL || vector == NULL)
		return;

	point->x -= vector->x;
	point->y -= vector->y;
	point->z -= vector->z;
}

struct Vector * subtractPointFromPoint(const struct Point * begin, const struct Point * end) {
	if (begin == NULL || end == NULL)
		return NULL;

	struct Vector * vector = (struct Vector *) malloc(sizeof(struct Vector));

	if (vector == NULL)
		return NULL;

	vector->x = end->x - begin->x;
	vector->y = end->y - begin->y;
	vector->z = end->z - begin->z;

	return vector;
}

struct Point * newPoint(int x, int y, int z) {
	struct Point * point = (struct Point *) malloc(sizeof(struct Point));

	if (point == NULL)
		return NULL;

	point->x = x;
	point->y = y;
	point->z = z;

	return point;
}

