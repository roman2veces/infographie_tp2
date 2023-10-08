
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "./window.h"
#include "shader_program.h"
#include "vertices_data.h"
#include "shapes.h"
#include "./model.h"


void printGLInfo();

#define GL_CHECK_ERROR checkGLError(__LINE__)
void checkGLError(int line);

std::string readFile(const char *path);

// CONSTANTS
const int POSITION_ATTRIBUT_INDEX = 0, COLOR_ATTRIBUT_INDEX = 1;
const int POSITION_ATTRIBUT_OFFSET = 0, COLOR_ATTRIBUT_OFFSET = 3;
const int THREE_COMPONENTS = 3, SIX_COMPONENTS = 6;
const char *MVP_NAME = "mvp";

// Define RGBA background colors
const int R = 1.0;
const int G = 1.0;
const int B = 1.0;
const int A = 0.0;

void shadersSetup(ShaderProgram &shaderProgram, std::string vertexShaderPath, std::string fragmentShaderPath)
{
    // Get shader string code
    std::string vertexShaderCode = readFile(vertexShaderPath.c_str());
    std::string fragmentShaderCode = readFile(fragmentShaderPath.c_str());

    // Create shaders
    Shader vertexShader(GL_VERTEX_SHADER, vertexShaderCode.c_str());
    Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentShaderCode.c_str());

    // Attach, link and use shaders
    shaderProgram.attachShader(vertexShader);
    shaderProgram.attachShader(fragmentShader);
    shaderProgram.link();
}

void createFloor() {

}

void calculateMVP(float angleDeg, float windowWidth, float windowHeight, GLint mvpLocation)
{
    // Utiliser glm pour les calculs de matrices.
    glm::mat4 matrix;
    // Initialiser les matrices modele, de vue et de projection à l'identité
    glm::mat4 modelMatrix(1.0);
    glm::mat4 viewMatrix(1.0);
    glm::mat4 projectionMatrix(1.0);
    glm::vec3 observation(0.0, 0.5, 2);

    modelMatrix = glm::rotate(modelMatrix, GLfloat(glm::radians(angleDeg)), glm::vec3(0.1, 1.0, 0.1));
    viewMatrix = glm::lookAt(observation, glm::vec3(0.0), glm::vec3(0.0, 1.0, 0.0));

    float ratio = windowWidth / windowHeight;
    projectionMatrix = glm::perspective(glm::radians(70.0f), ratio, 0.1f, 10.0f);

    matrix = projectionMatrix * viewMatrix * modelMatrix;
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

//void initialization() {
//
//   
//}

int main(int argc, char* argv[])
{
    Window w;
    if (!w.init())
        return -1;

    GLenum rev = glewInit();
    if (rev != GLEW_OK)
    {
        std::cout << "Could not initialize glew! GLEW_Error: " << glewGetErrorString(rev) << std::endl;
        return -2;
    }

    // Initialization
    const int N_ROWS = 7;
    const int N_GROUPS = N_ROWS * N_ROWS;

    glm::mat4 groupsTransform[N_GROUPS];

    glm::mat4 treeTransform[N_GROUPS];
    glm::mat4 rockTransform[N_GROUPS];
    glm::mat4 shroomTransform[N_GROUPS];

    // ...

    glm::vec3 playerPosition = glm::vec3(0);
    glm::vec2 playerOrientation = glm::vec2(0);

    // ...

    bool isFirstPersonCam = false;
    
    // Création des models
    Model mushroomModel("../models/mushroom.obj");
    Model rockModel("../models/rock.obj");
    Model suzanneModel("../models/suzanne.obj");
    Model treeModel("../models/tree.obj");


    // TODO Partie 2: Shader program de transformation.
    // ... transform;
    ShaderProgram modelShaderProgram;
    shadersSetup(modelShaderProgram, "shaders/model.vs.glsl", "shaders/model.fs.glsl");
    // ... location;
    GLint mvpLocation = modelShaderProgram.getUniformLoc(MVP_NAME);

    // Variables pour la mise à jour, ne pas modifier.
    float cx = 0, cy = 0;
    float dx = 0.019;
    float dy = 0.0128;

    float angleDeg = 0.0f;

    // TODO Partie 2: Instancier le cube ici.
    // ...
    
    BasicShapeElements cube(cubeVertices, sizeof(cubeVertices), cubeIndexes, sizeof(cubeIndexes));
    cube.enableAttribute(POSITION_ATTRIBUT_INDEX, THREE_COMPONENTS, SIX_COMPONENTS * sizeof(float), POSITION_ATTRIBUT_OFFSET);
    cube.enableAttribute(COLOR_ATTRIBUT_INDEX, THREE_COMPONENTS, SIX_COMPONENTS * sizeof(float), COLOR_ATTRIBUT_OFFSET);

    // TODO Partie 1: Donner une couleur de remplissage aux fonds.
    // Couleur de fond blanche
    glClearColor(R, G, B, A);

    // TODO Partie 2: Activer le depth test.
    glEnable(GL_DEPTH_TEST);

    int selectShape = 0;
    bool isRunning = true;

    while (isRunning)
    {
        if (w.shouldResize())
            glViewport(0, 0, w.getWidth(), w.getHeight());

        // TODO Partie 1: Nettoyer les tampons appropriées.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            modelShaderProgram.use();
            treeModel.draw();
            suzanneModel.draw();
            rockModel.draw();
            mushroomModel.draw();
            //calculateMVP(angleDeg, (float)w.getWidth(), (float)w.getHeight(), mvpLocation);

        w.swap();
        w.pollEvent();
        isRunning = !w.shouldClose() && !w.getKeyPress(Window::Key::ESC);
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

std::string readFile(const char *path)
{
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
