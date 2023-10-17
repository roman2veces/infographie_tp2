#ifndef VERTICES_DATA_H
#define VERTICES_DATA_H

// Vous pouvez merge ce fichier avec celui du tp1

// Dimensions du plan carr�
const GLfloat planeSize = 60.0f;
const GLfloat streamLength = 20.0f;

GLfloat rectangleVertices[] = {
    // Position             // Couleur
    -planeSize / 2.0f, -1.0f, -streamLength - planeSize / 2.0f,
    -planeSize / 2.0f, -1.0f, -planeSize / 2.0f,
    planeSize / 2.0f, -1.0f, -planeSize / 2.0f,
    planeSize / 2.0f, -1.0f, -streamLength - planeSize / 2.0f};

GLfloat squarePlaneVertices[] = {
    // Position             // Couleur
    -planeSize / 2.0f,
    -1.0f,
    -planeSize / 2.0f,
    -planeSize / 2.0f,
    -1.0f,
    planeSize / 2.0f,
    planeSize / 2.0f,
    -1.0f,
    planeSize / 2.0f,
    planeSize / 2.0f,
    -1.0f,
    -planeSize / 2.0f,
};

// Indices pour dessiner le carr� comme deux triangles
GLuint squarePlaneIndices[] = {
    0, 1, 2,
    0, 2, 3};

// Indice pour le Hud
GLfloat quadVertices[] = {
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 0.0f, 1.0f, 0.0f };

const GLfloat cubeVertices[] = {
    // +z
    -0.5f,
    -0.5f,
    0.5f,
    1.0f,
    0.0f,
    0.0f,
    0.5f,
    -0.5f,
    0.5f,
    1.0f,
    0.0f,
    0.0f,
    -0.5f,
    0.5f,
    0.5f,
    1.0f,
    0.0f,
    0.0f,
    0.5f,
    0.5f,
    0.5f,
    1.0f,
    0.0f,
    0.0f,
    // -z
    -0.5f,
    -0.5f,
    -0.5f,
    1.0f,
    1.0f,
    0.0f,
    0.5f,
    -0.5f,
    -0.5f,
    1.0f,
    1.0f,
    0.0f,
    -0.5f,
    0.5f,
    -0.5f,
    1.0f,
    1.0f,
    0.0f,
    0.5f,
    0.5f,
    -0.5f,
    1.0f,
    1.0f,
    0.0f,
    // +x
    0.5f,
    -0.5f,
    -0.5f,
    0.0f,
    1.0f,
    0.0f,
    0.5f,
    -0.5f,
    0.5f,
    0.0f,
    1.0f,
    0.0f,
    0.5f,
    0.5f,
    -0.5f,
    0.0f,
    1.0f,
    0.0f,
    0.5f,
    0.5f,
    0.5f,
    0.0f,
    1.0f,
    0.0f,
    // -x
    -0.5f,
    -0.5f,
    -0.5f,
    0.0f,
    1.0f,
    1.0f,
    -0.5f,
    -0.5f,
    0.5f,
    0.0f,
    1.0f,
    1.0f,
    -0.5f,
    0.5f,
    -0.5f,
    0.0f,
    1.0f,
    1.0f,
    -0.5f,
    0.5f,
    0.5f,
    0.0f,
    1.0f,
    1.0f,
    // +y
    -0.5f,
    0.5f,
    -0.5f,
    0.0f,
    0.0f,
    1.0f,
    0.5f,
    0.5f,
    -0.5f,
    0.0f,
    0.0f,
    1.0f,
    -0.5f,
    0.5f,
    0.5f,
    0.0f,
    0.0f,
    1.0f,
    0.5f,
    0.5f,
    0.5f,
    0.0f,
    0.0f,
    1.0f,
    // -y
    -0.5f,
    -0.5f,
    -0.5f,
    1.0f,
    0.0f,
    1.0f,
    0.5f,
    -0.5f,
    -0.5f,
    1.0f,
    0.0f,
    1.0f,
    -0.5f,
    -0.5f,
    0.5f,
    1.0f,
    0.0f,
    1.0f,
    0.5f,
    -0.5f,
    0.5f,
    1.0f,
    0.0f,
    1.0f,
};

const GLuint cubeIndexes[] = {
    0,
    1,
    2,
    1,
    3,
    2,

    4,
    5,
    6,
    5,
    7,
    6,

    8,
    9,
    10,
    9,
    11,
    10,

    12,
    13,
    14,
    13,
    15,
    14,

    16,
    17,
    18,
    17,
    19,
    18,

    20,
    21,
    22,
    21,
    23,
    22,
};

const GLfloat skyboxVertices[] = {
    -1.0f, 1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    -1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f};

const GLfloat grassPosition[] = {
    0.433013f,
    0.0f,
    -0.25f,
    -0.433013f,
    0.75f,
    0.25f,
    0.433013f,
    0.75f,
    -0.25f,

    0.433013f,
    0.0f,
    -0.25f,
    -0.433013f,
    0.0f,
    0.25f,
    -0.433013f,
    0.75f,
    0.25f,

    0.0f,
    0.0f,
    -0.5f,
    0.0f,
    0.75f,
    0.5f,
    0.0f,
    0.0f,
    0.5f,

    0.0f,
    0.0f,
    -0.5f,
    0.0f,
    0.75f,
    -0.5f,
    0.0f,
    0.75f,
    0.5f,

    -0.433013f,
    0.0f,
    -0.25f,
    0.433013f,
    0.75f,
    0.25f,
    0.433013f,
    0.0f,
    0.25f,

    -0.433013f,
    0.0f,
    -0.25f,
    -0.433013f,
    0.75f,
    -0.25f,
    0.433013f,
    0.75f,
    0.25f,
};

const GLfloat grassTexCoords[] = {
    0.0f,
    0.0f,
    1.0f,
    1.0f,
    0.0f,
    1.0f,

    0.0f,
    0.0f,
    1.0f,
    0.0f,
    1.0f,
    1.0f,

    1.0f,
    0.0f,
    0.0f,
    1.0f,
    0.0f,
    0.0f,

    1.0f,
    0.0f,
    1.0f,
    1.0f,
    0.0f,
    1.0f,

    1.0f,
    0.0f,
    0.0f,
    1.0f,
    0.0f,
    0.0f,

    1.0f,
    0.0f,
    1.0f,
    1.0f,
    0.0f,
    1.0f,
};

#endif // VERTICES_DATA_H