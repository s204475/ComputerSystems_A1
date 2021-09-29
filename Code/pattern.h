#ifndef PROTOTYPES
#define PROTOTYPES
#include "cbmp.h"
/* ^^ these are the include guards */

/* Prototypes for the functions */

void grey_scale_image(unsigned char image[BMP_WIDTH][BMP_HEIGTH], unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]);

void binary_threshold(unsigned char image[BMP_WIDTH][BMP_HEIGTH]);

char inside_bounds(int x, int y);

void increment_cell_count();

void add_coordinates__to_array(int x, int y);

void print_coordinates();

void mark_cell(int x, int y);

void remove_cell(int x, int y, char given_layer, unsigned char image[BMP_WIDTH][BMP_HEIGTH]);

char check_width(unsigned char image[BMP_WIDTH][BMP_HEIGTH], int x, int y, char currentLayer);

char check_height(unsigned char image[BMP_WIDTH][BMP_HEIGTH], int x, int y, char currentLayer);

char not_too_close(int x, int y);

void find_white_neighbours(unsigned char image[BMP_WIDTH][BMP_HEIGTH], int x, int y, char currentLayer);

void capture_cells(unsigned char image[BMP_WIDTH][BMP_HEIGTH]);

/*
    Erosion
*/

/*
    Pattern search
*/
double get_templateLength(double templateLength);


double use_pattern(unsigned char image[BMP_WIDTH][BMP_HEIGTH], int x, int y);


void remove_pattern_cell(int x, int y, unsigned char image[BMP_WIDTH][BMP_HEIGTH]);


void pattern_search(unsigned char image[BMP_WIDTH][BMP_HEIGTH]);


#endif