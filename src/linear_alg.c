/* This Source Code Form is subject to the terms of the Mozilla
 * Public License, v. 2.0. If a copy of the MPL was not distributed
 * with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2021 Ilya Zemskov */

#include <math.h>
#include <stdio.h>

#include "point.h"
#include "edge.h"
#include "model3d.h"
#include "linear_alg.h"

#define PI_DIV_180 0.0174

/*
              cos(y)                     0                sin(y)  
   -sin(x) * -sin(y)                cos(x)      -sin(x) * cos(y)  
    cos(x) * -sin(y)                sin(x)       cos(x) * cos(y)  
*/

/*
     cos(y) * cos(z)      sin(y) * sin(x) - cos(y) * sin(z) * cos(x)      cos(y) * sin(z) * sin(x) + sin(y) * cos(x)
              sin(z)      cos(z) * cos(x)                                 -1 * cos(z) * sin(x)
-1 * sin(y) * cos(z)      sin(y) * sin(z) * cos(x) + cos(y) * sin(x)      cos(y) * cos(x) - sin(y) * sin(z) * sin(x)
*/
void getRotateMatrix(const struct Matrix3x3 * res, int angleX, int angleY) {
    int angleZ = 0;

    double angleRadX = angleX * PI_DIV_180;

    double cosAngleX = cos(angleRadX);
    double sinAngleX = sin(angleRadX);

    double angleRadY = angleY * PI_DIV_180;

    double cosAngleY = cos(angleRadY);
    double sinAngleY = sin(angleRadY);

    double angleRadZ = angleZ * PI_DIV_180;

    double cosAngleZ = cos(angleRadZ);
    double sinAngleZ = sin(angleRadZ);

    res->values[0][0] = round((cosAngleY * cosAngleZ) * ROUND_COEFF);
    res->values[0][1] = round((sinAngleY * sinAngleX - cosAngleY * sinAngleZ * cosAngleX) * ROUND_COEFF);
    res->values[0][2] = round((cosAngleY * sinAngleZ * sinAngleX + sinAngleY * cosAngleX) * ROUND_COEFF);    

    res->values[1][0] = round((sinAngleZ) * ROUND_COEFF);
    res->values[1][1] = round((cosAngleZ * cosAngleX) * ROUND_COEFF);
    res->values[1][2] = round((-1 * cosAngleZ * sinAngleX) * ROUND_COEFF);    

    res->values[2][0] = round((-1 * sinAngleY * cosAngleZ) * ROUND_COEFF);
    res->values[2][1] = round((sinAngleY * sinAngleZ * cosAngleX + cosAngleY * sinAngleX) * ROUND_COEFF);
    res->values[2][2] = round((cosAngleY * cosAngleX - sinAngleY * sinAngleZ * sinAngleX) * ROUND_COEFF);
}

void getTranslateMatrix(const struct Matrix4x4 * res, int x, int y, int z) {
    if (res == NULL)
        return;

    res->values[0][0] = 1;
    res->values[0][1] = 0;
    res->values[0][2] = 0;
    res->values[0][3] = x;

    res->values[1][0] = 0;
    res->values[1][1] = 1;
    res->values[1][2] = 0;
    res->values[1][3] = y;

    res->values[2][0] = 0;
    res->values[2][1] = 0;
    res->values[2][2] = 1;
    res->values[2][3] = z;

    res->values[3][0] = 0;
    res->values[3][1] = 0;
    res->values[3][2] = 0;
    res->values[3][3] = 1;    
}

/*void multMatrixMatrix(const struct Matrix4x4 * matrix1, const struct Matrix4x4 * matrix2, Matrix4x4 * res) {
    for (int  i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int s = 0;
            for (int k = 0; k < 4; k++) {
                if (matrix1->isFloat[i][k] == 0 && matrix2->isFloat[k][j] == 0) {
                    s = s + matrix1->values[i][k] * matrix2->values[k][j];
                }
                else if (matrix1->isFloat[i][k] == 1 && matrix2->isFloat[k][j] == 1) {
                    double value1 = ((double) matrix1->values[i][k]) / 1000.0;
                    double value2 = ((double) matrix2->values[k][j]) / 1000.0;
                }
            }
            res[i][j] = s;
        }
    }
}*/

void multMatrixPoint(const struct Matrix3x3 * matrix, struct Point * point) {
    int column[3];    
    int res[3];

    if (matrix == NULL || point == NULL)
        return;    

    column[0] = point->x;
    column[1] = point->y;
    column[2] = point->z;    

    for (int i = 0; i < 3; i++) {
        res[i] = 0;

        for (int j = 0; j < 3; j++) {
            res[i] = res[i] + (matrix->values[i][j] * column[j] / ROUND_COEFF);
        }
    }

    point->x = res[0];
    point->y = res[1];
    point->z = res[2];
}

void multMatrixPoint4x4(const struct Matrix4x4 * matrix, struct Point * point) {
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
            res[i] = res[i] + matrix->values[i][j] * column[j];
        }
    }

    point->x = res[0];
    point->y = res[1];
    point->z = res[2];
}