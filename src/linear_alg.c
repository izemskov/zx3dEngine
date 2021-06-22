/* This Source Code Form is subject to the terms of the Mozilla
 * Public License, v. 2.0. If a copy of the MPL was not distributed
 * with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2021 Ilya Zemskov */

#include <math.h>

#include "point.h"
#include "edge.h"
#include "model3d.h"
#include "linear_alg.h"

#define PI_DIV_180 0.0174

void getRotateOYMatrix(struct Matrix4x4 * res, int angle) {
    if (res == NULL)
        return;

    double angleRad = angle * PI_DIV_180;

    int cosAngle = round(cos(angleRad) * 1000);
    int sinAngle = round(sin(angleRad) * 1000);

    res->values[0][0] = cosAngle;
    res->values[0][1] = 0;
    res->values[0][2] = sinAngle;
    res->values[0][3] = 0;

    res->values[1][0] = 0;
    res->values[1][1] = 1;
    res->values[1][2] = 0;
    res->values[1][3] = 0;

    res->values[2][0] = -1 * sinAngle;
    res->values[2][1] = 0;
    res->values[2][2] = cosAngle;
    res->values[2][3] = 0;

    res->values[3][0] = 0;
    res->values[3][1] = 0;
    res->values[3][2] = 0;
    res->values[3][3] = 1;    

    res->isFloat[0][0] = 1;
    res->isFloat[0][1] = 0;
    res->isFloat[0][2] = 1;
    res->isFloat[0][3] = 0;

    res->isFloat[1][0] = 0;
    res->isFloat[1][1] = 0;
    res->isFloat[1][2] = 0;
    res->isFloat[1][3] = 0;

    res->isFloat[2][0] = 1;
    res->isFloat[2][1] = 0;
    res->isFloat[2][2] = 1;
    res->isFloat[2][3] = 0;

    res->isFloat[3][0] = 0;
    res->isFloat[3][1] = 0;
    res->isFloat[3][2] = 0;
    res->isFloat[3][3] = 0;
}

void multMatrixPoint(const struct Matrix4x4 * matrix, struct Point * point) {
    int column[4];    
    int res[4];

    if (matrix == NULL || point == NULL)
        return;    

    column[0] = point->x;
    column[1] = point->y;
    column[2] = point->z;
    column[3] = 1;

    for (int i = 0; i < 4; i++) {
        res[i] = 0;

        for (int j = 0; j < 4; j++) {
            if (matrix->isFloat[i][j] == 0)
                res[i] = res[i] + matrix->values[i][j] * column[j];
            else
                res[i] = res[i] + (matrix->values[i][j] * column[j] / 1000);
        }
    }

    point->x = res[0];
    point->y = res[1];
    point->z = res[2];
}

void rotateModel(const struct Matrix4x4 * matrix, struct Model3D * model3d) {
    if (matrix == NULL || model3d == NULL)
        return;

    for (int i = 0; i < model3d->verticesCount; i++) {
        multMatrixPoint(matrix, &model3d->vertices[i]);
    }
}
