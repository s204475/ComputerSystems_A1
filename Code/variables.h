#ifndef VARIABLES
#define VARIABLES
#include "cbmp.h"
//Array to store the image (unsigned char = unsigned 8 bit)
unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];



#define treshold_value 90
#define REMOVE_CELL_SIZE 10

int performanceCheck = 0;

int countedCells = 0;
int totalErosions = 0;
char *string_coordinate;
struct COORDINATES
{
    unsigned int x;
    unsigned int y;
};

struct COORDINATES coordinatesArray[950];

#define allowedProximity 10 //Should have low values for images with many cells on top of one another
#define neighbourColumn 4
#define neighbourRow 2

int nextCor = 0;

#endif