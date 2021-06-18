/* This Source Code Form is subject to the terms of the Mozilla
 * Public License, v. 2.0. If a copy of the MPL was not distributed
 * with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2021 Ilya Zemskov */

#ifndef VECTOR__H
#define VECTOR__H

struct Vector {
	int x;
	int y;
	int z;
};

void addVectorToVector(struct Vector * src, const struct Vector * vector);
void aubtractVectorFromVector(struct Vector * src, const struct Vector * vector);
struct Vector * newVector(int x, int y, int z);

#endif
