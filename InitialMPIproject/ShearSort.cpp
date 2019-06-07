#include "ShearSort.h"

void shearSort(int n, MPI_Comm comm, int* coord, struct Pixel* pixel, MPI_Datatype PixelMPIType)
{
	int phase, source, dest;
	int numOfPhases = 2 * (int)(log(n) / log(2)) + 1;
	int order;
	for (phase = 0; phase < numOfPhases; phase++) {
		if (phase % 2 == 0) { //row
			MPI_Cart_shift(comm, 1, 1, &source, &dest);
			order = coord[0] % 2 == 0 ? DESCENDING : ASCENDING;
			oddEvenSort(coord[1], order, source, dest, pixel, n, &PixelMPIType, comm);
		}
		else { //col
			MPI_Cart_shift(comm, 0, 1, &source, &dest);
			oddEvenSort(coord[0], DESCENDING, source, dest, pixel, n, &PixelMPIType, comm);
		}
	}
}

void oddEvenSort(int step, int order, int left, int right, struct Pixel* pixel, int size, MPI_Datatype* PixelMPIType, MPI_Comm comm) {

	MPI_Status status;
	struct Pixel receivedPixel;
	int sendTag = 0, receiveTag = 0;
	for (int i = 0; i < size; i++) // steps.
	{
		if (step % 2 == 0) { //even step

			if (i % 2 == 0) { //even step in even step 
				MPI_Sendrecv(pixel, 1, *PixelMPIType, right, sendTag, &receivedPixel, 1, *PixelMPIType, right, receiveTag, comm, &status);
				*pixel = getPixelValue(pixel, &receivedPixel, 0, order);
			}
			else if (step != MASTER_TAG) { // odd step in even step
				MPI_Sendrecv(pixel, 1, *PixelMPIType, left, sendTag, &receivedPixel, 1, *PixelMPIType, left, receiveTag, comm, &status);
				*pixel = getPixelValue(pixel, &receivedPixel, 1, order);
			}
		}
		else { //odd step
			if (i % 2 == 0) { // even step in odd step
				MPI_Sendrecv(pixel, 1, *PixelMPIType, left, sendTag, &receivedPixel, 1, *PixelMPIType, left, receiveTag, comm, &status);
				*pixel = getPixelValue(pixel, &receivedPixel, 1, order);
			}
			else if (step != size - 1) { //odd step in odd step != last step
				MPI_Sendrecv(pixel, 1, *PixelMPIType, right, sendTag, &receivedPixel, 1, *PixelMPIType, right, receiveTag, comm, &status);
				*pixel = getPixelValue(pixel, &receivedPixel, 0, order);
			}
		}
	}
}