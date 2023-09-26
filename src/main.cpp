
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "window.h"
#include "shader_program.h"
#include "vertices_data.h"
#include "shapes.h"

void printGLInfo();

#define GL_CHECK_ERROR checkGLError(__LINE__)
void checkGLError(int line);

void changeRGB(GLfloat *color);
void changePos(GLfloat *pos, float &cx, float &cy, float &dx, float &dy);

std::string readFile(const char *path);

GLint vertexLocalization;
GLint modelMatrixLocalization;
GLint visualMatrixLocalization;
GLint projectionMatrixLocalization;
GLint colorLocalization;

const int N_COMPONENTS = 3;
const char *MVP_NAME = "mvp";

// Define RGBA background colors
const int R = 1.0;
const int G = 1.0;
const int B = 1.0;
const int A = 0.0;

int main()
{
    // Window w;
    // if (!w.init())
    //     return -1;

    GLenum rev = glewInit();
    if (rev != GLEW_OK)
    {
        std::cout << "Could not initialize glew! GLEW_Error: " << glewGetErrorString(rev) << std::endl;
        return -2;
    }

    ShaderProgram shaderProgram;
    {
        // Les accolades vont permettre de détruire le code des shaders plus rapidement
        // Vous devez lire le code des shaders dans "shaders/"
        // avec la fonction "readFile".
        std::string vertexShaderCode = readFile("shaders/basic.vs.glsl");
        std::string fragmentShaderCode = readFile("shaders/basic.fs.glsl");

        // Create shaders
        Shader vertexShader(GL_VERTEX_SHADER, vertexShaderCode.c_str());
        Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentShaderCode.c_str());

        // Attach, link and use shaders
        shaderProgram.attachShader(vertexShader);
        shaderProgram.attachShader(fragmentShader);
        shaderProgram.link();
        // shaderProgram.use();
    }

    ShaderProgram colorShaderProgram;
    {
        // Les accolades vont permettre de détruire le code des shaders plus rapidement
        // Vous devez lire le code des shaders dans "shaders/"
        // avec la fonction "readFile".
        std::string vertexShaderCode = readFile("shaders/color.vs.glsl");
        std::string fragmentShaderCode = readFile("shaders/color.fs.glsl");

        // Create shaders
        Shader vertexShader(GL_VERTEX_SHADER, vertexShaderCode.c_str());
        Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentShaderCode.c_str());

        // Attach, link and use shaders
        colorShaderProgram.attachShader(vertexShader);
        colorShaderProgram.attachShader(fragmentShader);
        colorShaderProgram.link();
    }

    // ... color;
    {
        // ...
    }

    ShaderProgram transformShaderProgram;
    {
        // Les accolades vont permettre de détruire le code des shaders plus rapidement
        // Vous devez lire le code des shaders dans "shaders/"
        // avec la fonction "readFile".
        std::string vertexShaderCode = readFile("shaders/transform.vs.glsl");
        std::string fragmentShaderCode = readFile("shaders/transform.fs.glsl");

        // Create shaders
        Shader vertexShader(GL_VERTEX_SHADER, vertexShaderCode.c_str());
        Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentShaderCode.c_str());

        // Attach, link and use shaders
        transformShaderProgram.attachShader(vertexShader);
        transformShaderProgram.attachShader(fragmentShader);
        transformShaderProgram.link();
    }

    // ... location;

    // Variables pour la mise à jour, ne pas modifier.
    float cx = 0, cy = 0;
    float dx = 0.019;
    float dy = 0.0128;

    float angleDeg = 0.0f;

    // Tableau non constant de la couleur
    GLfloat onlyColorTriVertices[] = {
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f};

    BasicShapeArrays firstTriangle(triVertices, sizeof(triVertices));
    firstTriangle.enableAttribute(0, N_COMPONENTS, N_COMPONENTS * sizeof(float), 0);

    BasicShapeArrays firstSquare(squareVertices, sizeof(squareVertices));
    firstSquare.enableAttribute(0, N_COMPONENTS, N_COMPONENTS * sizeof(float), 0);

    BasicShapeArrays colorTriangle(colorTriVertices, sizeof(colorTriVertices));
    colorTriangle.enableAttribute(0, 3, 6 * sizeof(float), 0);
    colorTriangle.enableAttribute(1, 3, 6 * sizeof(float), 3);

    BasicShapeArrays colorSquare(colorSquareVertices, sizeof(colorSquareVertices));
    colorSquare.enableAttribute(0, 3, 6 * sizeof(float), 0);
    colorSquare.enableAttribute(1, 3, 6 * sizeof(float), 3);

    BasicShapeMultipleArrays multiArrayTriangle(triVertices, sizeof(triVertices), onlyColorTriVertices, sizeof(onlyColorTriVertices));
    multiArrayTriangle.enablePosAttribute(0, 3, 3 * sizeof(float), 0);
    multiArrayTriangle.enableColorAttribute(1, 3, 3 * sizeof(float), 3);

    BasicShapeElements elementsSquare(colorSquareVerticesReduced, sizeof(colorSquareVerticesReduced), indexes, sizeof(indexes));
    elementsSquare.enableAttribute(0, 3, 6 * sizeof(float), 0);
    elementsSquare.enableAttribute(1, 3, 6 * sizeof(float), 3);

    BasicShapeElements cube(cubeVertices, sizeof(cubeVertices), cubeIndexes, sizeof(cubeIndexes));
    cube.enableAttribute(0, 3, 6 * sizeof(float), 0);
    cube.enableAttribute(1, 3, 6 * sizeof(float), 3);

    glClearColor(R, G, B, A);

    glEnable(GL_DEPTH_TEST);

    int selectShape = 0;
    bool isRunning = true;

    while (isRunning)
    {
        // if (w.shouldResize())
        //     glViewport(0, 0, w.getWidth(), w.getHeight());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // if (w.getKey(Window::Key::T))
        // {
        //     selectShape = ++selectShape < 7 ? selectShape : 0;
        //     std::cout << "Selected shape: " << selectShape << std::endl;
        // }

        changeRGB(&onlyColorTriVertices[0]);
        changeRGB(&onlyColorTriVertices[3]);
        changeRGB(&onlyColorTriVertices[6]);

        GLfloat *multiArrayTrianglePosition = multiArrayTriangle.mapPosData();
        changePos(multiArrayTrianglePosition, cx, cy, dx, dy);
        multiArrayTriangle.unmapPosData();

        // TODO: modify camera somewhere here

        switch (selectShape)
        {
        case 0:
        case 1:
            shaderProgram.use();
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            colorShaderProgram.use();
            break;
        case 6:
            transformShaderProgram.use();
            break;
        default:
            shaderProgram.use();
        }

        if (selectShape == 6)
        {
            // angleDeg += 0.5f;
            // // Utiliser glm pour les calculs de matrices.
            // GLint mvpLocation = transformShaderProgram.getUniformLoc(MVP_NAME);
            // glm::mat4 matrix;
            // glm::mat4 modelMatrix(1.0);
            // glm::mat4 viewMatrix(1.0);
            // glm::mat4 projectionMatrix(1.0);
            // glm::vec3 observation(0.0, 0.5, 2);

            // modelMatrix = glm::rotate(modelMatrix, GLfloat(glm::radians(angleDeg)), glm::vec3(0.1, 1.0, 0.1));
            // viewMatrix = glm::lookAt(observation, glm::vec3(0.0), glm::vec3(0.0, 1.0, 0.0));

            // float ratio = (float)w.getWidth() / (float)w.getHeight();
            // projectionMatrix = glm::perspective(glm::radians(70.0f), ratio, 0.1f, 10.0f);

            // matrix = projectionMatrix * viewMatrix  * modelMatrix;
            // glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(matrix));

            angleDeg += 0.5f;
            // Utiliser glm pour les calculs de matrices.

            // Initialiser les matrices avec la matrices identité
            glm::mat4 mvpMtr(glm::mat4(1.0));
            glm::mat4 matrModel(glm::mat4(1.0)), matrVisu(glm::mat4(1.0)), matrProj(glm::mat4(1.0));
            glm::mat4 rotationMatrix(glm::mat4(1.0)), translationMatrix(glm::mat4(1.0));

            // dernier paramètre axes de rotation
            rotationMatrix = glm::rotate(rotationMatrix, GLfloat(glm::radians(angleDeg)), glm::vec3(0.1f, 1.0f, 0.1f));

            matrModel = rotationMatrix * translationMatrix; // pas de translation dans cet exemple
            // ordre pour lookat position de la camera, target de la camera, direction vers le haut
            matrVisu = glm::lookAt(glm::vec3(0.0f, 0.5f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            // float ratio = (float)w.getWidth() / (float)w.getHeight();
            // matrProj = glm::perspective(glm::radians(70.0f), ratio, 0.1f, 10.0f);

            mvpMtr = matrProj * matrVisu * matrModel;
            // afficher le modèle on get la position du cube et on l'update
            glUniformMatrix4fv(transformShaderProgram.getUniformLoc(MVP_NAME), 1, GL_FALSE, glm::value_ptr(mvpMtr));
        }

        switch (selectShape)
        {
        case 0:
            firstTriangle.draw(GL_TRIANGLES, 3);
            break;

        case 1:
            firstSquare.draw(GL_TRIANGLE_STRIP, 4);
            break;

        case 2:
            colorTriangle.draw(GL_TRIANGLES, 3);
            break;

        case 3:
            colorSquare.draw(GL_TRIANGLE_STRIP, 4);
            break;

        case 4:
            multiArrayTriangle.updateColorData(onlyColorTriVertices, sizeof(onlyColorTriVertices));
            multiArrayTriangle.draw(GL_TRIANGLES, 3);
            break;

        case 5:
            elementsSquare.draw(GL_TRIANGLES, 6);
            break;

        case 6:
            cube.draw(GL_TRIANGLES, 36);
            break;

        default:
            firstTriangle.draw(GL_TRIANGLES, 3);
        }

        // w.swap();
        // w.pollEvent();
        // isRunning = !w.shouldClose() && !w.getKey(Window::Key::ESC);
    }

    return 0;
}

void checkGLError(int line)
{
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "Line " << line << ": ";
        switch (error)
        {
        case GL_INVALID_ENUM:
            std::cerr << "GL_INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            std::cerr << "GL_INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            std::cerr << "GL_INVALID_OPERATION";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
        case GL_OUT_OF_MEMORY:
            std::cerr << "GL_OUT_OF_MEMORY";
            break;
        case GL_STACK_UNDERFLOW:
            std::cerr << "GL_STACK_UNDERFLOW";
            break;
        case GL_STACK_OVERFLOW:
            std::cerr << "GL_STACK_OVERFLOW";
            break;
        default:
            std::cerr << "Unknown gl error occured!";
            break;
        }
        std::cerr << std::endl;
    }
}

void printGLInfo()
{
    std::cout << "OpenGL info:" << std::endl;
    std::cout << "    Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "    Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "    Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "    Shading version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void changeRGB(GLfloat *color)
{
    unsigned char r = color[0] * 255;
    unsigned char g = color[1] * 255;
    unsigned char b = color[2] * 255;

    if (r > 0 && b == 0)
    {
        r--;
        g++;
    }
    if (g > 0 && r == 0)
    {
        g--;
        b++;
    }
    if (b > 0 && g == 0)
    {
        r++;
        b--;
    }
    color[0] = r / 255.0f;
    color[1] = g / 255.0f;
    color[2] = b / 255.0f;
}

void changePos(GLfloat *pos, float &cx, float &cy, float &dx, float &dy)
{
    if ((cx < -1 && dx < 0) || (cx > 1 && dx > 0))
        dx = -dx;
    pos[0] += dx;
    pos[3] += dx;
    pos[6] += dx;
    cx += dx;
    if ((cy < -1 && dy < 0) || (cy > 1 && dy > 0))
        dy = -dy;
    pos[1] += dy;
    pos[4] += dy;
    pos[7] += dy;
    cy += dy;
}

std::string readFile(const char *path)
{
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
