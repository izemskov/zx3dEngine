/* This Source Code Form is subject to the terms of the Mozilla
 * Public License, v. 2.0. If a copy of the MPL was not distributed
 * with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2021 Ilya Zemskov */

#ifndef LINEAR_ALG__H
#define LINEAR_ALG__H

struct Matrix3x3 {
    int values[3][3];
};

struct Matrix4x4 {
    int values[4][4];
};

#define ROUND_COEFF 2000

void getRotateMatrix(const struct Matrix3x3 * res, int angleX, int angleY);
void multMatrixPoint(const struct Matrix3x3 * matrix, struct Point * point);
void multMatrixPoint4x4(const struct Matrix4x4 * matrix, struct Point * point);
void getTranslateMatrix(const struct Matrix4x4 * res, int x, int y, int z);

#endif
