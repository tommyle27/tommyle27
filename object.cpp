//============================================================================
// Name        : object.cpp
// Author      : Tommy Le
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "object.hpp"


void insert(LIST *list, SHAPE *object) {
// ...
	if (object == NULL) return;

	NODE *p = (NODE*) malloc(sizeof(NODE));
	p->object = object;
	p->prev = NULL;
	p->next = NULL;

	if (list->start == NULL) {
		list->start = p;
		list->end = p;
	} else {
		list->end->next = p;
		p->prev = list->end;
		list->end = p;
	}
}

void deleteNode(LIST *list, NODE **selectp) {
// ...
	//check if list is empty
	if(list->start == NULL) return;

	NODE *p = list->start;

	if(list->start == *selectp) {
		if(p->next != NULL) {
			p->next->prev = NULL;
		} else {
		list->end = NULL;
		}
		list->start = p->next;
	} else {
		while(p->next != *selectp && p->next != NULL) {p = p->next;}

		p = p->next;
		if(p == NULL) return;

		if(p->next == NULL) {
			list->end = p->prev;
		}

		p->prev->next = p->next;

		if(p->next != NULL) p->next->prev = p->prev;

	}
	free(p);
}

void clearList(LIST *list) {
// ...
}

void drawShape(SHAPE *object) {
	if (object->type == RECTANGLE) {  // rectangle
		// draw filled rectangle
		glColor3f(object->fr, object->fg, object->fb);
		glBegin(GL_QUADS);
			glVertex2i(object->x1, object->y1);
			glVertex2i(object->x1, object->y2);
			glVertex2i(object->x2, object->y2);
			glVertex2i(object->x2, object->y1);
		glEnd();

		// draw outline

		glColor3f(object->sr, object->sg, object->sb);
		glLineWidth(object->swidth);
		glBegin(GL_LINE_LOOP);
			glVertex2i(object->x1, object->y1);
			glVertex2i(object->x1, object->y2);
			glVertex2i(object->x2, object->y2);
			glVertex2i(object->x2, object->y1);
		glEnd();


	} else if (object->type == CIRCLE) {  // circle
		// draw filled circle
		glColor3f(object->fr, object->fg, object->fb);
			circleMidpointFill(object->x1, object->y1, object->x2, object->y2);

		// draw outline
		glColor3f(object->sr, object->sg, object->sb);
		glLineWidth(object->swidth);
			circleMidpoint(object->x1, object->y1, object->x2, object->y2);

	}
}

void drawShapeHighLight(SHAPE *object) {
	// draw outline with high light color


	if(object->type == RECTANGLE) {
		glColor3f(1,1,0);
		glLineWidth(object->swidth);
			glBegin(GL_LINE_LOOP);
				glVertex2i(object->x1, object->y1);
				glVertex2i(object->x1, object->y2);
				glVertex2i(object->x2, object->y2);
				glVertex2i(object->x2, object->y1);
			glEnd();

	}

	else if(object->type == CIRCLE) {
		glColor3f(1,1,0);
		glLineWidth(object->swidth);
			circleMidpoint(object->x1, object->y1, object->x2, object->y2);
	}


}

void drawList(LIST *list) {
	NODE *p = list->start;
	while (p) {
		drawShape(p->object);
		p = p->next;
	}
}

void setPixel(GLint x, GLint y) {
	glPointSize(2.0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

// draw points on line of circle
void circlePlotPoints(const GLint& xc, const GLint& yc, const GLint& x,
		const GLint& y) {
// ...
	setPixel(xc + x, yc + y); setPixel(xc - x, yc + y);
	setPixel(xc + x, yc - y); setPixel(xc - x, yc - y);
	setPixel(xc + y, yc + x); setPixel(xc - y, yc + x);
	setPixel(xc + y, yc - x); setPixel(xc - y, yc - x);
}

// draw circle main function
void circleMidpoint(GLint x1, GLint y1, GLint x2, GLint y2) {
	// ...
	GLint r = sqrt( ( ((x1 - x2)*(x1 - x2)) + ((y1 - y2)*(y1 - y2)) ) );
	GLint p = 1 - r;
	GLint x = 0, y = r;

	circlePlotPoints(x1, y1, x, y);

	while(x < y) {
		x++;

		if(p < 0)
			p += 2 * x + 1;
		else {
			y--;
			p += 2 * (x-y) + 1;
		}

		circlePlotPoints(x1, y1, x, y);
	}
}

void circlePlotPointsFill(GLint x1, GLint y1, GLint x, GLint y) {
	// ...
	glLineWidth(2.0);

	glBegin(GL_LINES);
		glVertex2i(x1 - x, y1 + y); glVertex2i(x1 + x, y1 + y);
		glVertex2i(x1 - x, y1 - y); glVertex2i(x1 + x, y1 - y);
		glVertex2i(x1 - y, y1 + x); glVertex2i(x1 + y, y1 + x);
		glVertex2i(x1 - y, y1 - x); glVertex2i(x1 + y, y1 - x);
	glEnd();
}

void circleMidpointFill(GLint x1, GLint y1, GLint x2, GLint y2) {
	// ...
	GLint r = sqrt( ( ((x1 - x2)*(x1 - x2)) + ((y1 - y2)*(y1 - y2)) ) );
	GLint p = 1 - r;
	GLint x = 0, y = r;

	circlePlotPointsFill(x1, y1, x, y);

	while(x < y) {
		x++;

		if(p < 0)
			p += 2 * x + 1;
		else {
			y--;
			p += 2 * (x-y) + 1;
		}

		circlePlotPointsFill(x1, y1, x, y);
	}
}
