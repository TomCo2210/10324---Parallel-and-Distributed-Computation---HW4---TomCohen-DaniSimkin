#include "Pixel.h"


struct Pixel getPixelValue(struct Pixel* pixel, struct Pixel* receive_pixel, int evenOrOdd, int order) {
	//order:	ASCENDING: 0
	//			DESCENDIN: 1

	if (evenOrOdd == 0) { //odd in odd || even in even
		return order == ASCENDING ? getMinimalValuedPixel(*pixel, *receive_pixel) : getMaximalValuedPixel(*pixel, *receive_pixel);
	}
	else {
		return order == ASCENDING ? getMaximalValuedPixel(*pixel, *receive_pixel) : getMinimalValuedPixel(*pixel, *receive_pixel);
	}
}

struct Pixel getMaximalValuedPixel(struct Pixel pixel, struct Pixel otherPixel) {
	return areBothBlack(pixel, otherPixel) ?
		(distanceFromZero(pixel.x, pixel.y) > distanceFromZero(otherPixel.x, otherPixel.y) ? pixel : otherPixel) :
		((pixel.rgb[0] + pixel.rgb[1] + pixel.rgb[2]) > (otherPixel.rgb[0] + otherPixel.rgb[1] + otherPixel.rgb[2]) ? pixel : otherPixel);
}
struct Pixel getMinimalValuedPixel(struct Pixel pixel, struct Pixel otherPixel) {
	return areBothBlack(pixel, otherPixel) ?
		(distanceFromZero(pixel.x, pixel.y) < distanceFromZero(otherPixel.x, otherPixel.y) ? pixel : otherPixel) :
		((pixel.rgb[0] + pixel.rgb[1] + pixel.rgb[2]) < (otherPixel.rgb[0] + otherPixel.rgb[1] + otherPixel.rgb[2]) ? pixel : otherPixel);
}

int distanceFromZero(int x, int y) {
	return (int)sqrt(pow(x, 2) + pow(y, 2));
}

bool areBothBlack(struct Pixel pixel, struct Pixel otherPixel) {
	return ((pixel.rgb[0] + pixel.rgb[1] + pixel.rgb[2]) == 0.0 && ((otherPixel.rgb[0] + otherPixel.rgb[1] + otherPixel.rgb[2])) == 0.0);
}

void createCartesianGroup(int n, MPI_Comm* comm) {
	int dim[2] = { n,n }, period[2] = { 0 };
	MPI_Cart_create(MPI_COMM_WORLD, 2, dim, period, 1, comm);
}


void printPixelsArray(struct Pixel* arr, int size) {
	int loop;
	for (loop = 0; loop < size; loop++) {
		printf("\n Pixel ID: %d, RGB[0]: %.2f , RGB[1]: %.1f , RGB[2]: %.1f , X: %d , Y: %d ", arr[loop].id, arr[loop].rgb[0], arr[loop].rgb[1], arr[loop].rgb[2], arr[loop].x, arr[loop].y);
		fflush(stdout);
	}
	printf("\n");
}
