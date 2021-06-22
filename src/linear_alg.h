/* This Source Code Form is subject to the terms of the Mozilla
 * Public License, v. 2.0. If a copy of the MPL was not distributed
 * with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2021 Ilya Zemskov */

#ifndef LINEAR_ALG__H
#define LINEAR_ALG__H

struct Matrix4x4 {
    int values[4][4];   
    char isFloat[4][4];
};

void getRotateOYMatrix(struct Matrix4x4 * res, int angle);
void multMatrixPoint(const struct Matrix4x4 * matrix, struct Point * point);
void rotateModel(const struct Matrix4x4 * matrix, struct Model3D * model3d);

#endif
