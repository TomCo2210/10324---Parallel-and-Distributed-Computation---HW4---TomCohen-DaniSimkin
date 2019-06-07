#ifndef __PIXEL_H
#define __PIXEL_H

#include "mpi.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define FILENAME "C:\\Users\\Tomco\\source\\repos\\HW_4-Parallel and Distributed TomCohen DaniSimkin\\InitialMPIproject\\pixel.txt"
#define ASCENDING 0
#define DESCENDING 1
#define MASTER_TAG 0

struct Pixel{
	int id;
	int x;
	int y;
	float rgb[3];
};

struct Pixel getMaximalValuedPixel(struct Pixel pixel, struct Pixel otherPixel);
struct Pixel getMinimalValuedPixel(struct Pixel pixel, struct Pixel otherPixel);
struct Pixel getPixelValue(struct Pixel* pixel, struct Pixel* receive_pixel, int evenOrOdd, int order);
void printPixelsArray(struct Pixel* arr, int size);
int distanceFromZero(int x, int y);
void createCartesianGroup(int n, MPI_Comm* comm);
bool areBothBlack(struct Pixel pixel, struct Pixel otherPixel);
#endif // !__PIXEL_H