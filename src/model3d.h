/* This Source Code Form is subject to the terms of the Mozilla
 * Public License, v. 2.0. If a copy of the MPL was not distributed
 * with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2021 Ilya Zemskov */

#ifndef MODEL3D__H
#define MODEL3D__H

struct Model3D {
    int verticesCount;
    struct Point * vertices;
    struct Point * processedVerticies;    

    int edgesCount;
    struct Edge * edges;

    struct Point center;

    int angleX, oldAngleX;
    int angleY, oldAngleY;

    struct Matrix3x3 * rotateMatrix;
};

struct Model3D * createOctahedron();
struct Model3D * createCube();

#endif