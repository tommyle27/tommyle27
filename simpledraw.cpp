//============================================================================
// Name        : SimpleDraw.cpp
// Author      : Tommy Le
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <stdio.h>
#include <GL/glut.h>
#include "object.hpp"
#include "menu.hpp"
#include "edit.hpp"
#include "file.hpp"

// global variables
// display window size
GLsizei winWidth = 800, winHeight = 600;

// Operation controls/variables
GLint oprMode = 0,       // 0 for drawing, 1 for editing
	  isInDraw = 0,      // 1 is in drawing mode
	  isInMenu = 0,      // 1 is menu operation mode
	  isInMove = 0,      // 1 for move around mode
	  xbegin, ybegin;    // used as beginning point of translate vector for moving

// object
TYPE objType = RECTANGLE;
GLfloat fillred = 1.0, fillgreen = 0.0, fillblue = 0.0, // fill color
		sred = 1.0, sgreen = 0.0, sblue = 0.0;          // stroke color
GLint strokeWidth = 1;
LIST objlist = {0}; // object list and initialization
NODE *selectNode;   // pointing to selected node
SHAPE tempObj;      // variable to store temp object data when drawing.

void init(void) {
	glutInitDisplayMode(GLUT_DOUBLE);  // GLUT_DOUBLE for double frame buffer
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("SimpleDraw Tommy Le");
	glClearColor(1.0, 1.0, 1.0, 0.0); // Set display-window color to white
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, winHeight, 0.0); // set top left as origin
}

void drawObjectList() {
	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

	if (objlist.start != NULL)
		drawList(&objlist);

	// draw temp object when dragging an object
	if (oprMode == 0 && isInDraw == 1)
		drawShape(&tempObj);

	// draw the high light of selected object in edit mode
	if (oprMode == 1 && isInMove == 0 && selectNode != NULL)
		drawShapeHighLight(selectNode->object);

	glFlush();
	glutSwapBuffers();
}

void mouseActionFcn(GLint button, GLint action, GLint xMouse, GLint yMouse) {

	if (oprMode == 0 && isInMenu == 0) {
		if (button == GLUT_LEFT_BUTTON) {

			// drawing mode
			if (action == GLUT_DOWN) {
				tempObj.type = objType;
				tempObj.fr = fillred;
				tempObj.fg = fillgreen;
				tempObj.fb = fillblue;
				tempObj.sr = sred;
				tempObj.sg = sgreen;
				tempObj.sb = sblue;
				tempObj.swidth = strokeWidth;

				tempObj.x1 = xMouse;
				tempObj.y1 = yMouse;


				isInDraw = 1; // start dragging
				if (objType == RECTANGLE) {
				   tempObj.x2 = xMouse;
				   tempObj.y2 = yMouse;
				}
				else if (objType == CIRCLE) {
					// ... initialize the property of circle
					 tempObj.x2 = xMouse;
					 tempObj.y2 = yMouse;

				}

			} else if (action == GLUT_UP && isInDraw == 1) {

				isInDraw = 0; // end of dragging
				if (objType == RECTANGLE) {
				   tempObj.x2 = xMouse;
				   tempObj.y2 = yMouse;
				}
				else if (objType == CIRCLE) {
					// ... finalize the property of circle
					 tempObj.x2 = xMouse;
					 tempObj.y2 = yMouse;
				}


				// create a new shape object, copy the tempObj values to the new object,
				// and the new object to the object list
				SHAPE *shapeObj = (SHAPE*) malloc(sizeof(SHAPE));
				shapeObj->type = tempObj.type;
				shapeObj->fr = tempObj.fr;
				shapeObj->fg = tempObj.fg;
				shapeObj->fb = tempObj.fb;
				shapeObj->sr = tempObj.sr;
				shapeObj->sg = tempObj.sg;
				shapeObj->sb = tempObj.sb;
				shapeObj->swidth = tempObj.swidth;
				shapeObj->x1 = tempObj.x1;
				shapeObj->y1 = tempObj.y1;
				shapeObj->x2 = tempObj.x2;
				shapeObj->y2 = tempObj.y2;

				insert(&objlist, shapeObj);
				shapeObj = NULL;

			}
		}

	}

	// select mode
	else if (isInMove == 0) {
		if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
			selectNode = select(xMouse, yMouse);
		}
	}

   // edit move mode
	else if (isInMove == 1) {
		if (button == GLUT_LEFT_BUTTON) {

			if (action == GLUT_DOWN) {
				// select node and copy the select node data to temp node for drawing
				// set mouse postion to xbegin, and ybegin
				selectNode = select(xMouse, yMouse);
				if (selectNode != NULL) {
					tempObj = *(selectNode->object);
					xbegin = xMouse;
					ybegin = yMouse;

				}

			} else if (action == GLUT_UP) {

				// get the vector from (xbegin, ybegin) to the new mouse position
				// use the vector to update the properties of moving object.
				GLint vx = xMouse - xbegin;
				GLint vy = yMouse - ybegin;

				if (selectNode != NULL) {
					selectNode->object->x1 = tempObj.x1 + vx;
					selectNode->object->y1 = tempObj.y1 + vy;
					selectNode->object->x2 = tempObj.x2 + vx;
					selectNode->object->y2 = tempObj.y2 + vy;
					selectNode = NULL;
				}

			}
		}
	}

	glutPostRedisplay();
	glFlush();
}

void mouseMotionFcn(GLint xMouse, GLint yMouse) {
	// in drawing mode, use xMouse and yMouse value to update the tempObj
	// in edit move mode, use (xbegin, ybegin) and (xMouse, yMouse) to update the selected object
	if (oprMode == 0) {
		tempObj.x2 = xMouse;
		tempObj.y2 = yMouse;
	} else if (oprMode == 1 && isInMove == 1 && selectNode != NULL) {
		GLint vx = xMouse - xbegin;
		GLint vy = yMouse - ybegin;
		selectNode->object->x1 = tempObj.x1 + vx;
		selectNode->object->y1 = tempObj.y1 + vy;
		selectNode->object->x2 = tempObj.x2 + vx;
		selectNode->object->y2 = tempObj.y2 + vy;
	}

	glutPostRedisplay();
	glFlush();
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	/*  Reset viewport and projection parameters  */
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(newWidth), GLdouble(newHeight), 0.0);
	/*  Reset display-window size parameters.  */
	winWidth = newWidth;
	winHeight = newHeight;
	drawObjectList();
}

int main(int argc, char** argv) {
	setvbuf(stdout, NULL, _IONBF, 0); // For Eclipse stdout debugging
	setvbuf(stderr, NULL, _IONBF, 0);

	glutInit(&argc, argv);
	addMenu();
	init();
	glutDisplayFunc(drawObjectList);
	glutReshapeFunc(winReshapeFcn);
	glutMouseFunc(mouseActionFcn);
	glutMotionFunc(mouseMotionFcn);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}

