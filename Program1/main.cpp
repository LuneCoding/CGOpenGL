#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"

using namespace std;

void keyboardHandler(unsigned char key, int a, int b)
{
    if (key == 27)
        glutExit();
}

const char * fragshader_name = "fragmentshader.fsh";
const char * vertexshader_name = "vertexshader.vsh";

GLuint shaderID;

void Render()
{
    const glm::vec4 blue = glm::vec4(0.0f, 0.0f, 0.4f, 1.0f);
    glClearBufferfv(GL_COLOR, 0, glm::value_ptr(blue));

    glUseProgram(shaderID);

    glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}

int main(int argc, char ** argv)
{
#pragma region << * * * * * * Setup GLut & GLew * * * * * >>

	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Hello OpenGL");
	glutDisplayFunc(Render);
    glutKeyboardFunc(keyboardHandler);

	glewInit();

#pragma endregion

#pragma region << * * * * * * Shader Stuff * * * * * >>
    char * fragshader = glsl::readFile(fragshader_name);
    GLuint fshID = glsl::makeFragmentShader(fragshader);

    char * vertexshader = glsl::readFile(vertexshader_name);
    GLuint vshID = glsl::makeVertexShader(vertexshader);

    shaderID = glsl::makeShaderProgram(vshID, fshID);

#pragma endregion

	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	glutMainLoop();

	return 0;
}