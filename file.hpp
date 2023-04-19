//============================================================================
// Name        : file.hpp
// Author      : Tommy Le
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef FILE_HPP_
#define FILE_HPP_

#include "object.hpp"

int saveSVG(const char *filename, int winWidth, int  winHeight);
int openSVG(const char *filename);
int saveBitmap(const char *ptrcFileName, int nX, int nY, int nWidth, int nHeight);

#endif /* FILE_HPP_ */
