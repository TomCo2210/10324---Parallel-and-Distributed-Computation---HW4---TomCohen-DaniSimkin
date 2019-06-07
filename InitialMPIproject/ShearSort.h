#ifndef __SHEARSORT_H
#define __SHEARSORT_H
#include "Pixel.h"
#include "mpi.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void oddEvenSort(int location, int order, int left, int right, struct Pixel* pixel, int size, MPI_Datatype* PixelMPIType, MPI_Comm comm);
void shearSort(int n, MPI_Comm comm, int* coord, struct Pixel* pixel, MPI_Datatype PixelMPIType);
#endif