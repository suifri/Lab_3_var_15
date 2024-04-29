#pragma once
#include <GL/glut.h>

static class LightConstants
{
private:
	static const GLint lightArraysSize = 4;
public:
	static const GLfloat lightPosition[lightArraysSize];
	static const GLfloat lightAmbient[lightArraysSize];
	static const GLfloat lightDiffuse[lightArraysSize];
	static const GLfloat lightSpecular[lightArraysSize];
	static const GLfloat lightColor[lightArraysSize];
};

