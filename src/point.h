/* This Source Code Form is subject to the terms of the Mozilla
 * Public License, v. 2.0. If a copy of the MPL was not distributed
 * with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2021 Ilya Zemskov */

#ifndef POINT__H
#define POINT__H

struct Point {
	int x;
	int y;
	int z;
};

void addVectorToPoint(struct Point * point, const struct Vector * vector);
void subtractVectorFromPoint(struct Point * point, const struct Vector * vector);
struct Vector * subtractPointFromPoint(const struct Point * begin, const struct Point * end);
struct Point * newPoint(int x, int y, int z);

#endif
