
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mpi.h"
#include "Pixel.h"
#include "FileReadWrite.h"
#include "ShearSort.h"

int main(int argc, char *argv[])
{
	struct Pixel pixel;
	int rank, numberOfPixels;

	MPI_Datatype PixelMPIType;
	MPI_Datatype dataTypes[4] = { MPI_INT, MPI_INT, MPI_INT, MPI_FLOAT };
	int blocksLength[4] = { 1, 1, 1, 3 };
	MPI_Aint disp[4];
	MPI_Comm comm;

	int coord[2];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numberOfPixels);

	int n = (int)sqrt(numberOfPixels);

	disp[0] = (char *)&pixel.id - (char *)&pixel;
	disp[1] = (char *)&pixel.x - (char *)&pixel;
	disp[2] = (char *)&pixel.y - (char *)&pixel;
	disp[3] = (char *)&pixel.rgb - (char *)&pixel;

	MPI_Type_create_struct(4, blocksLength, disp, dataTypes, &PixelMPIType);
	MPI_Type_commit(&PixelMPIType);

	createCartesianGroup(n, &comm);
	MPI_Cart_coords(comm, rank, 2, coord);

	struct Pixel* pixelsArray = (struct Pixel*) calloc(numberOfPixels, sizeof(struct Pixel));

	if (!pixelsArray) {
		printf("Memory Allocation Error!");
		exit(EXIT_FAILURE);
	}

	if (rank == MASTER_TAG) {
		readFromFile(pixelsArray);
		printf("The original array is: \n");
		printPixelsArray(pixelsArray, numberOfPixels);
	}

	MPI_Scatter(pixelsArray, 1, PixelMPIType, &pixel, 1, PixelMPIType, MASTER_TAG, MPI_COMM_WORLD);

	shearSort(n, comm, coord, &pixel, PixelMPIType);

	MPI_Gather(&pixel, 1, PixelMPIType, pixelsArray, 1, PixelMPIType, MASTER_TAG, MPI_COMM_WORLD);

	if (rank == MASTER_TAG) {
		printf("The sorted array is: \n");
		printPixelsArray(pixelsArray, numberOfPixels);
	}

	free(pixelsArray);
	MPI_Finalize();
	return 0;

}