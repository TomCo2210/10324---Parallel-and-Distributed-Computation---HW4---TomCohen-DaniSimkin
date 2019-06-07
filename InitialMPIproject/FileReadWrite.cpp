#include "FileReadWrite.h"

void readFromFile(struct Pixel* pixelsArray) {

	FILE *file;
	file = fopen(FILENAME, "r");
	if (!file)
	{
		printf("ERROR opening file!");
		exit(EXIT_FAILURE);
	}
	int numberOfPixelsToRead;
	fscanf(file, "%d", &numberOfPixelsToRead);

	if (numberOfPixelsToRead < 0) {
		printf("ERROR reading file!");
		exit(EXIT_FAILURE);
	}

	int i = 0;
	while (i < numberOfPixelsToRead && !feof(file))
	{

		fscanf(file, "%d %d %d %f %f %f", &(pixelsArray[i].id), &(pixelsArray[i].x), &(pixelsArray[i].y),
			&(pixelsArray[i].rgb[0]), &(pixelsArray[i].rgb[1]), &(pixelsArray[i].rgb[2]));
		i++;
	}

	fclose(file);
}