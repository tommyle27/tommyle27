//============================================================================
// Name        : file.cpp
// Author      : Tommy Le
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#include "file.hpp"
#include "object.hpp"

#define MaxNumObj 100
#define GL_BGR_EXT 0x80E0
#define GL_BGR     0x80E0
#define GL_BGRA    0x80E1

extern LIST objlist;

int saveBitmap(const char *ptrcFileName, int nX, int nY, int nWidth,
		int nHeight) {

  // your implementation
	FILE *fp = fopen(ptrcFileName, "wb");
		if (fp == NULL) {
			printf("fp == NULL \n");
			return 0;
		}
			printf("step 1\n");

		int bitsize = nWidth*nHeight*3 +  ((3*nWidth)%4 == 0 ? 0 : (4-(3*nWidth)%4)*nHeight);

		printf("step 0 %d\n", bitsize);

		unsigned char *ptrImage = (unsigned char*) malloc(bitsize);
		if (ptrImage == NULL) {
			printf("ptrImage == NULL \n");
			fclose(fp);
			return 0;
		}

		glReadPixels(nX, nY, nWidth, nHeight, GL_BGR, GL_UNSIGNED_BYTE, ptrImage);

		printf("step 1\n");

		BITMAPFILEHEADER bfh;
		BITMAPINFOHEADER bih;
		memset(&bfh, 0, sizeof(bfh));
		memset(&bih, 0, sizeof(bih));

		bfh.bfType = 0x4d42;
		bfh.bfSize = sizeof(bfh) + sizeof(bih) + bitsize;
		bfh.bfOffBits = sizeof(bfh) + sizeof(bih);

		bih.biSize = sizeof(bih);
		bih.biWidth = nWidth + nWidth%4;
		bih.biHeight = nHeight;
		bih.biPlanes = 1;
		bih.biBitCount = 24;
		bih.biSizeImage = bitsize;

			printf("step 2\n");
		if (fwrite(&bfh, sizeof(bfh), 1, fp) < 1) {
			free(ptrImage);
			fclose(fp);
			return 0;
		};

		if (fwrite(&bih, sizeof(bih), 1, fp)<1) {
			free(ptrImage);
			fclose(fp);
			return 0;
		}

		printf("step 3\n");

		if ( fwrite(ptrImage, 1, bitsize, fp) < bitsize ) {
			free(ptrImage);
			fclose(fp);
			return 0;
		}

		fclose(fp);
		free(ptrImage);

		printf("end of save bitmap\n");
	return 1;
}

int saveSVG(const char *filename, int winWidth, int winHeight) {
	FILE *fp = fopen(filename, "w");
	if (fp == NULL)  return EXIT_FAILURE;

	char line[255];
	int width, height; //store calculated height and width

	//write header data for SVG
	sprintf(line, "<?xml version=\"1.0\" standalone=\"no\"?>\n");
	fputs(line, fp);
	sprintf(line, "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n");
	fputs(line, fp);
	sprintf(line, "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
	fputs(line, fp);
	sprintf(line,
			"<svg width=\"%d\" height=\"%d\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n",
			winWidth, winHeight);
	fputs(line, fp);

	// traverse through object list and a line for each object
	// need to convert the rectangal/circle data to SVG rect/circle data


    // your implementation
	NODE *p = objlist.start;

	while(p != NULL) {


		if(p->object->type == RECTANGLE) {
			if(p->object->x2 < p->object->x1) {
				int tX = p->object->x2;
				p->object->x2 = p->object->x1;
				p->object->x1 = tX;
			}

			if(p->object->y2 < p->object->y1) {
						int tX = p->object->y2;
						p->object->y2 = p->object->y1;
						p->object->y1 = tX;
					}

			width = p->object->x2 - p->object->x1;
			height = p->object->y2 - p->object->y1;

			sprintf(line,
					"<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"rgb(%d,%d,%d)\" stroke=\"rgb(%d,%d,%d)\" stroke-width=\"%d\"/>",
					p->object->x1, p->object->y1, width, height, p->object->fr, p->object->fg, p->object->fb, p->object->sr, p->object->sg, p->object->sb,p->object->swidth);
			fputs(line, fp);
		} else if (p->object->type == CIRCLE) {
			GLint radius = sqrt( ((p->object->x1 - p->object->x2)*(p->object->x1 - p->object->x2)) + ((p->object->y1 - p->object->y2)*(p->object->y1 - p->object->y2)) );
			sprintf(line,
					"<circle x=\"%d\" y=\"%d\" radius=\"%d\" fill=\"rgb(%d,%d,%d)\" stroke=\"rgb(%d,%d,%d)\" stroke-width=\"%d\"/>",
					p->object->x1, p->object->y1, radius, p->object->fr, p->object->fg, p->object->fb, p->object->sr, p->object->sg, p->object->sb,p->object->swidth);
			fputs(line, fp);
		}
		p = p->next;
	}



	sprintf(line, "</svg>\n");
	fputs(line, fp);
	fclose(fp);

	return EXIT_SUCCESS;
}

int openSVG(const char *filename) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) return EXIT_FAILURE;

	int lineLength = 255;
	char line[lineLength];
	int x1, y1, w, h, fr, fg, fb, sr, sg, sb, sw, r; // variables to hold scan values

	// read line by line, if it is line of rect/circle element, retrieve the attribute values and convert them to
	// object values and create object and insert to the object list.

	while ( fgets(line, lineLength, fp)) {
		//printf("%s\n", buffer);
		SHAPE *shapeObj;
		if (line[0] == '<' && line[1] == 'r' ) { // rectangle
			sscanf(line,
					"<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"rgb(%d,%d,%d)\" stroke=\"rgb(%d,%d,%d)\" stroke-width=\"%d\"/>",
					&x1, &y1, &w, &h, &fr, &fg, &fb, &sr, &sg, &sb, &sw);

			shapeObj = (SHAPE*) malloc(sizeof(SHAPE));
			shapeObj->type = RECTANGLE;
			shapeObj->x1 = x1;
			shapeObj->y1 = y1;
			shapeObj->x2 = x1 + w;
			shapeObj->y2 = y1 + h;
			shapeObj->fr = fr / 255;
			shapeObj->fg = fg / 255;
			shapeObj->fb = fb / 255;
			shapeObj->sr = sr / 255;
			shapeObj->sg = sg / 255;
			shapeObj->sb = sb / 255;
			shapeObj->swidth = sw;
			insert(&objlist, shapeObj);

		} else if (line[0] == '<' && line[1] == 'c' )  {
			// ....
			sscanf(line,
						"<circle x=\"%d\" y=\"%d\" r=\"%d\" fill=\"rgb(%d,%d,%d)\" stroke=\"rgb(%d,%d,%d)\" stroke-width=\"%d\"/>",
						&x1, &y1, &r, &fr, &fg, &fb, &sr, &sg, &sb, &sw);

				shapeObj = (SHAPE*) malloc(sizeof(SHAPE));
				shapeObj->type = CIRCLE;
				shapeObj->x1 = x1;
				shapeObj->y1 = y1;
				shapeObj->x2 = x1 + r;
				shapeObj->y2 = y1 + r;
				shapeObj->fr = fr / 255;
				shapeObj->fg = fg / 255;
				shapeObj->fb = fb / 255;
				shapeObj->sr = sr / 255;
				shapeObj->sg = sg / 255;
				shapeObj->sb = sb / 255;
				shapeObj->swidth = sw;
				insert(&objlist, shapeObj);
		}
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

