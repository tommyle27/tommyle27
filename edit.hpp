//============================================================================
// Name        : edit.hpp
// Author      : Tommy Le
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#ifndef EDIT_HPP_
#define EDIT_HPP_

#include <GL/glut.h>

extern int selected;
extern int selection;

GLint min(GLint x, GLint y);

GLint max(GLint x, GLint y);

NODE* select(GLint x, GLint y);

void Delete(NODE **pp);

void moveFront(NODE *p);

void moveBack(NODE *p);

void moveAround(NODE *p);

void printNode(NODE * p);

#endif /* EDIT_HPP_ */
