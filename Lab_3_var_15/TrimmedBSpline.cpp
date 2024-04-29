#include "TrimmedBSpline.h"

TrimmedBSpline::TrimmedBSpline(const SPLINE_TYPE type)
	:BSpline(type)
{
}

void TrimmedBSpline::display()
{
    GLfloat knots[8] = { 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 };
    GLfloat edgePt[5][2] = { {0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}, {0.0, 0.0} };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(330.0, 1., 0., 0.);
    glScalef(0.5, 0.5, 0.5);

    gluBeginSurface(this->nurbs);
    gluNurbsSurface(this->nurbs, 8, knots, 8, knots,
        4 * 3, 3, **this->controlPoints,
        4, 4, GL_MAP2_VERTEX_3);

    gluBeginTrim(this->nurbs);
    gluPwlCurve(this->nurbs, 5, *edgePt, 2,
        GLU_MAP1_TRIM_2);
    gluEndTrim(this->nurbs);

    gluBeginTrim(this->nurbs);

    GLfloat ctrlPoints1[4][3] = {
    {0.2, 0.2, 1.0},
    {0.5, 0.866, 1.0},
    {1.0, 0.0, 1.0},
    {0.2, 0.2, 1.0}
    };

    gluNurbsCurve(this->nurbs, 8, knots, 3, *ctrlPoints1, 4, GLU_MAP1_TRIM_3);
    gluEndTrim(this->nurbs);

    gluEndSurface(this->nurbs);

    glPopMatrix();

	glutPostRedisplay();
}
