#include "DiskDrawingService.h"

void DiskDrawingService::DrawFillDisk()
{
	glPushMatrix();
	glTranslatef(3, 2, 0);
	glRotatef(90, 0.0, 0.9, 0.9);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	gluDisk(gluNewQuadric(), 0, 1.5, 20, 20);
	glPopMatrix();
}

void DiskDrawingService::DrawWireDisk()
{
	glPushMatrix();
	glTranslatef(3, 2, 0);
	glRotatef(90, 0.0, 0.9, 0.9);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	gluDisk(gluNewQuadric(), 0, 1.5, 20, 20);
	glPopMatrix();
}
