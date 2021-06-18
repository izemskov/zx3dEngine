/* This Source Code Form is subject to the terms of the Mozilla
 * Public License, v. 2.0. If a copy of the MPL was not distributed
 * with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2021 Ilya Zemskov */

#include <stdio.h>

#include "vector.h"

void addVectorToVector(struct Vector * src, const struct Vector * vector) {
    if (src == NULL || vector == NULL)
        return;

	src->x += vector->x;
	src->y += vector->y;
	src->z += vector->z;
}

void aubtractVectorFromVector(struct Vector * src, const struct Vector * vector) {
    if (src == NULL || vector == NULL)
        return;

	src->x -= vector->x;
	src->y -= vector->y;
	src->z -= vector->z;
}

struct Vector * newVector(int x, int y, int z) {
	struct Vector * vector = (struct Vector *) malloc(sizeof(struct Vector));

    if (vector == NULL)
        return NULL;

	vector->x = x;
	vector->y = y;
	vector->z = z;

	return vector;
}

