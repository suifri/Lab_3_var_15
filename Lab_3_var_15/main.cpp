#include "LightConstants.h"
#include "DiskDrawingService.h"
#include "TrimmedBSpline.h"
#include "NURBSSurface.h"

const GLint initialWidth = 500;
const GLint initialHeight = 500;

BSpline* bSpline = new BSpline();
NURBSSurface* nurbsSurface = new NURBSSurface();
TrimmedBSpline* trimmedSpline = new TrimmedBSpline();

GLint displayChoice = 0;
GLboolean isPerspective = true;

void reshape(const GLint width, const GLint height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0, static_cast<GLfloat>(width) / static_cast<GLfloat>(height), 0.1, 100.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init(void)
{
	GLfloat matDiffuse[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat matSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat matShininess[] = { 100.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	glLightfv(GL_LIGHT0, GL_POSITION, LightConstants::lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightConstants::lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightConstants::lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightConstants::lightSpecular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightConstants::lightColor);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);

	if (isPerspective == false)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-5, 5, -5, 5, -5, 5);
	}
	else 
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45, 1, 2, 10);
		gluLookAt(0.0, 0.0, 5.0,
			0.0, 0.0, 0.0,
			0.0, 1.0, 0.0);
	}
	
	switch (displayChoice)
	{
	case 0:
		DiskDrawingService::DrawFillDisk();
		glutPostRedisplay();
		break;
	case 1:
		bSpline->display();
		break;
	case 2:
		nurbsSurface->display();
		break;
	case 3:
		trimmedSpline->display();
		break;
	case 6:
		DiskDrawingService::DrawWireDisk();
		glutPostRedisplay();
		break;
	case 7:
		DiskDrawingService::DrawInterpolatedDisk();
		glutPostRedisplay();
		break;
	default:
		break;
	}

	glutSwapBuffers();
}

void mainMenuHandler(const GLint choice)
{
	switch (choice)
	{
	case 0:
		displayChoice = 0;
		break;
	case 1:
		displayChoice = 1;//B-Spline
		break;
	case 2:
		displayChoice = 2;//NURBS-surface
		break;
	case 3:
		displayChoice = 3;
		break;
	case 4:
		isPerspective = true;
		break;
	case 5:
		isPerspective = false;
		break;
	case 6:
		displayChoice = 6;
		break;
	case 7:
		displayChoice = 7;
		break;
	default:
		break;
	}
}



void bSplineSubMenuHandler(const GLint choice)
{
	delete trimmedSpline;

	switch (choice)
	{
	case 0:
		trimmedSpline = new TrimmedBSpline();
		break;
	case 1:
		trimmedSpline = new TrimmedBSpline(SPLINE_TYPE::OUTLINE_POLYGON);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(initialWidth, initialHeight);
	glutCreateWindow(*argv);
	init();
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutDisplayFunc(display);

	GLint bSplineSubMenu = glutCreateMenu(bSplineSubMenuHandler);
	glutAddMenuEntry("Fill", 0);
	glutAddMenuEntry("Wire octahedrons", 1);

	glutCreateMenu(mainMenuHandler);
	glutAddMenuEntry("Disk Fill", 0);
	glutAddMenuEntry("Disk Wire", 6);
	glutAddMenuEntry("Disk Interpolated", 7);
	glutAddMenuEntry("B-Spline", 1);
	glutAddMenuEntry("NURBS-Surface", 2);
	glutAddMenuEntry("Trimmed B-spline", 3);
	glutAddSubMenu("Trimmed B-spline texture", bSplineSubMenu);
	glutAddMenuEntry("Perspective", 4);
	glutAddMenuEntry("Ortho", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}