/* This Source Code Form is subject to the terms of the Mozilla
 * Public License, v. 2.0. If a copy of the MPL was not distributed
 * with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2021 Ilya Zemskov */

#include <stdlib.h>

#include "vector.h"
#include "point.h"
#include "edge.h"
#include "linear_alg.h"
#include "model3d.h"

struct Model3D * createOctahedron() {
    struct Model3D * model3D = (struct Model3D *) malloc(sizeof(struct Model3D));

    model3D->verticesCount = 6;
    model3D->vertices = (struct Point *) malloc(model3D->verticesCount * sizeof(struct Point));

    model3D->vertices[0].x = 10;
    model3D->vertices[0].y = 10;
    model3D->vertices[0].z = 0;

    model3D->vertices[1].x = 10;
    model3D->vertices[1].y = 30;
    model3D->vertices[1].z = 0;

    model3D->vertices[2].x = 30;
    model3D->vertices[2].y = 30;
    model3D->vertices[2].z = 0;

    model3D->vertices[3].x = 30;
    model3D->vertices[3].y = 10;
    model3D->vertices[3].z = 0;

    model3D->vertices[4].x = 20;
    model3D->vertices[4].y = 20;
    model3D->vertices[4].z = 10;

    model3D->vertices[5].x = 20;
    model3D->vertices[5].y = 20;
    model3D->vertices[5].z = 50;

    model3D->edgesCount = 12;
    model3D->edges = (struct Edge *) malloc(model3D->edgesCount * sizeof(struct Edge));

    model3D->edges[0].src = 0;
    model3D->edges[0].dst = 1;

    model3D->edges[1].src = 1;
    model3D->edges[1].dst = 2;

    model3D->edges[2].src = 2;
    model3D->edges[2].dst = 3;

    model3D->edges[3].src = 3;
    model3D->edges[3].dst = 0;

    model3D->edges[4].src = 4;
    model3D->edges[4].dst = 0;

    model3D->edges[5].src = 4;
    model3D->edges[5].dst = 1;

    model3D->edges[6].src = 4;
    model3D->edges[6].dst = 2;

    model3D->edges[7].src = 4;
    model3D->edges[7].dst = 3;

    model3D->edges[8].src = 5;
    model3D->edges[8].dst = 0;

    model3D->edges[9].src = 5;
    model3D->edges[9].dst = 1;

    model3D->edges[10].src = 5;
    model3D->edges[10].dst = 2;

    model3D->edges[11].src = 5;
    model3D->edges[11].dst = 3;

    model3D->center.x = 0;
    model3D->center.y = 0;
    model3D->center.z = 50;

    return model3D;
}

struct Model3D * createCube() {    
    struct Model3D * model3D = (struct Model3D *) malloc(sizeof(struct Model3D));                

    model3D->verticesCount = 8;
    model3D->vertices = (struct Point *) malloc(model3D->verticesCount * sizeof(struct Point));
    model3D->processedVerticies = (struct Point *) malloc(model3D->verticesCount * sizeof(struct Point));        

    model3D->vertices[0].x = -5;
    model3D->vertices[0].y = -5;
    model3D->vertices[0].z = -5;

    model3D->vertices[1].x = -5;
    model3D->vertices[1].y = 5;
    model3D->vertices[1].z = -5;

    model3D->vertices[2].x = 5;
    model3D->vertices[2].y = 5;
    model3D->vertices[2].z = -5;

    model3D->vertices[3].x = 5;
    model3D->vertices[3].y = -5;
    model3D->vertices[3].z = -5;

    model3D->vertices[4].x = -5;
    model3D->vertices[4].y = -5;
    model3D->vertices[4].z = 5;

    model3D->vertices[5].x = -5;
    model3D->vertices[5].y = 5;
    model3D->vertices[5].z = 5;

    model3D->vertices[6].x = 5;
    model3D->vertices[6].y = 5;
    model3D->vertices[6].z = 5;

    model3D->vertices[7].x = 5;
    model3D->vertices[7].y = -5;
    model3D->vertices[7].z = 5;

    model3D->edgesCount = 12;
    model3D->edges = (struct Edge *) malloc(model3D->edgesCount * sizeof(struct Edge));

    model3D->edges[0].src = 0;
    model3D->edges[0].dst = 1;

    model3D->edges[1].src = 1;
    model3D->edges[1].dst = 2;

    model3D->edges[2].src = 2;
    model3D->edges[2].dst = 3;

    model3D->edges[3].src = 3;
    model3D->edges[3].dst = 0;

    model3D->edges[4].src = 4;
    model3D->edges[4].dst = 5;

    model3D->edges[5].src = 5;
    model3D->edges[5].dst = 6;

    model3D->edges[6].src = 6;
    model3D->edges[6].dst = 7;

    model3D->edges[7].src = 7;
    model3D->edges[7].dst = 4;

    model3D->edges[8].src = 0;
    model3D->edges[8].dst = 4;

    model3D->edges[9].src = 1;
    model3D->edges[9].dst = 5;

    model3D->edges[10].src = 2;
    model3D->edges[10].dst = 6;

    model3D->edges[11].src = 3;
    model3D->edges[11].dst = 7;

    model3D->center.x = 0;
    model3D->center.y = 0;
    model3D->center.z = 35;

    model3D->angleX = 0;
    model3D->oldAngleX = model3D->angleX;
    model3D->angleY = 0;
    model3D->oldAngleY = model3D->angleY;

    /*model3D->rotateMatrixX = (struct Matrix4x4 *) malloc(sizeof(struct Matrix4x4));
    getRotateOXMatrix(model3D->rotateMatrixX, model3D->angleX);

    model3D->rotateMatrixY = (struct Matrix4x4 *) malloc(sizeof(struct Matrix4x4));
    getRotateOYMatrix(model3D->rotateMatrixY, model3D->angleY);*/

    model3D->rotateMatrix = (struct Matrix3x3 *) malloc(sizeof(struct Matrix3x3));
    getRotateMatrix(model3D->rotateMatrix, model3D->angleX, model3D->angleY);

    return model3D;
}

void deleteModel(struct Model3D * model3d) {
    free(model3d->vertices);
    free(model3d->edges);
    free(model3d->processedVerticies);
    free(model3d->rotateMatrixY);
    free(model3d);
}
