#ifndef PATTERN
#define PATTERN
/* ^^ these are the include guards */

/* Prototypes for the functions */

double get_templateLength(double templateLength);


double use_pattern(unsigned char image[BMP_WIDTH][BMP_HEIGTH], int x, int y, double templateLength);


void remove_pattern_cell(int x, int y, unsigned char image[BMP_WIDTH][BMP_HEIGTH]);


void pattern_search(unsigned char image[BMP_WIDTH][BMP_HEIGTH]);


#endif