#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cbmp.h"
#include <time.h>
#include "variables.h"
#include "prototypes.h"

//Wall = warning all
//To compile: gcc cbmp.c pattern.c Algorithm.c -o .\Algorithm.exe -std=c99 -Wall -O2
/*To run: 

.\Algorithm.exe .\samples\easy\1EASY.bmp .\samples\tests\1EASYOutErosionTest.bmp e

.\Algorithm.exe .\samples\hard\4HARD.bmp .\samples\hard\4HARDOutErosionTest.bmp e

.\Algorithm.exe .\samples\impossible\1Impossible.bmp .\samples\impossible\1ImpossibleOutErosionTest.bmp e

    If you want pattern search: 

.\Algorithm.exe .\samples\easy\1EASY.bmp .\samples\easy\1EASYOutPattern.bmp p

*/

/*int structuring_element[3][3] = {
    {0, 1, 0},
    {1, 1, 1},
    {0, 1, 0}};*/
char neighbours[neighbourColumn][neighbourRow] = {
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0}};

void increment_cell_count()
{
    countedCells++;
}

void grey_scale_image(unsigned char image[BMP_WIDTH][BMP_HEIGTH], unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS])
{
    for (int x = 0; x < BMP_WIDTH; x++)
    {
        for (int y = 0; y < BMP_HEIGTH; y++)
        {
            image[x][y] = (input_image[x][y][0] + input_image[x][y][1] + input_image[x][y][2]) / 3;
        }
    }
}

void binary_threshold(unsigned char image[BMP_WIDTH][BMP_HEIGTH])
{
    for (int x = 0; x < BMP_WIDTH; x++)
    {
        for (int y = 0; y < BMP_HEIGTH; y++)
        {
            if (image[x][y] <= treshold_value)
            {
                image[x][y] = 0;
            }
            else
            {
                image[x][y] = 1;
            }
        }
    }
}

char inside_bounds(int x, int y)
{
    if (x > BMP_WIDTH - 1 || y > BMP_HEIGTH - 1 || x < 0 || y < 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void add_coordinates__to_array(int x, int y)
{
    coordinatesArray[nextCor].x = x;
    coordinatesArray[nextCor].y = y;
    nextCor++;
}

void print_coordinates()
{
    for (int i = 0; i < 950; i++)
    {
        if (coordinatesArray[i].x == 0 && coordinatesArray[i].y == 0)
        {
            //printf("%d",i);
            //return;
        }
        else
        {
            printf("{%d,%d}\n", coordinatesArray[i].x, coordinatesArray[i].y);
        }
    }
}

void mark_cell(int x, int y)
{
    add_coordinates__to_array(x, y);

    for (char cross = -8; cross <= 8; cross++)
    {
        for (char thickness = -1; thickness <= 1; thickness++)
        {
            if (inside_bounds(x + cross, y + thickness) == 1)
            {
                input_image[x + cross][y + thickness][0] = 255;
                input_image[x + cross][y + thickness][1] = 0;
                input_image[x + cross][y + thickness][2] = 0;
            }

            if (inside_bounds(x + thickness, y + cross) == 1)
            {
                input_image[x + thickness][y + cross][0] = 255;
                input_image[x + thickness][y + cross][1] = 0;
                input_image[x + thickness][y + cross][2] = 0;
            }
        }
    }
}

//remove the found cell and replaces it with black pixels
void remove_cell(int x, int y, char given_layer, unsigned char image[BMP_WIDTH][BMP_HEIGTH])
{
    for (char width = -given_layer; width <= given_layer; width++)
    {
        for (char height = -given_layer; height <= given_layer; height++)
        {
            if (inside_bounds(x + width, y + height))
            {
                image[x + width][y + height] = 0;
            }
        }
    }
}

char check_width(unsigned char image[BMP_WIDTH][BMP_HEIGTH], int x, int y, char currentLayer)
{
    for (char width = 0; width < currentLayer; width++)
    {
        if (inside_bounds(x + width, y - currentLayer) && image[x + width][y - currentLayer] == 1)
        {
            return 1;
        }

        if (inside_bounds(x + width, y + currentLayer) && image[x + width][y + currentLayer] == 1)
        {
            return 1;
        }
    }

    return 0;
}

char check_height(unsigned char image[BMP_WIDTH][BMP_HEIGTH], int x, int y, char currentLayer)
{

    for (char height = 0; height < currentLayer; height++)
    {
        if (inside_bounds(x - currentLayer, y + height) && image[x - currentLayer][y + height] == 1)
        {
            return 1;
        }

        if (inside_bounds(x + currentLayer, y + height) && image[x + currentLayer][y + height] == 1)
        {
            return 1;
        }
    }

    return 0;
}

char not_too_close(int x, int y)
{
    if (nextCor == 0)
    {
        return 1;
    }

    for (int i = 0; i < nextCor; i++)
    {
        int distance = (x - coordinatesArray[i].x) * (x - coordinatesArray[i].x) + (y - coordinatesArray[i].y) * (y - coordinatesArray[i].y);
        if (sqrt(distance) < allowedProximity)
        {
            return 0;
        }
    }

    return 1;
}

void find_white_neighbours(unsigned char image[BMP_WIDTH][BMP_HEIGTH], int x, int y, char currentLayer)
{
    if (currentLayer <= 1)
    {
        return;
    }

    char found = 0;
    found = check_width(image, x, y, currentLayer); //width

    if (found == 0)
    {
        found = check_height(image, x, y, currentLayer); //height
    }

    if (found == 1)
    {
        find_white_neighbours(image, x, y, currentLayer - 1);
    }
    else
    {
        remove_cell(x, y, REMOVE_CELL_SIZE, image);

        if (not_too_close(x, y) == 1) //only marks and counts the cell, if it is more than a few pixels from the last recorded cell
        {
            mark_cell(x, y);
            countedCells++;
        }
    }
}

void capture_cells(unsigned char image[BMP_WIDTH][BMP_HEIGTH])
{
    //capture and mark potential cells

    for (int x = 0; x < BMP_WIDTH; x++)
    {
        for (int y = 0; y < BMP_HEIGTH; y++)
        {
            if (image[x][y] == 1)
            {
                find_white_neighbours(image, x, y, REMOVE_CELL_SIZE); //starts marking and removing captured cells
            }
        }
    }
}

//Iterates over the image. If it finds a white pixel, it checks the four neighbours directly above, below, left and right
//and if any are black, it itself becomes black. It then increments if there are no other sorrounding white pixels in 12 by 12 at all.
void erosion(unsigned char image[BMP_WIDTH][BMP_HEIGTH])
{
    unsigned char nextImage[BMP_WIDTH][BMP_HEIGTH];
    char erosionsTics = 1;
    while (erosionsTics > 0)
    {
        totalErosions++;
        erosionsTics = 0;
        for (int x = 0; x < BMP_WIDTH; x++)
        {
            for (int y = 0; y < BMP_HEIGTH; y++)
            {
                if (image[x][y] == 1)
                {
                    char count = 0;

                    for (int i = 0; i < 4; i++)
                    {
                        if (inside_bounds(x + neighbours[i][0], y + neighbours[i][1]) == 1 && image[x + neighbours[i][0]][y + neighbours[i][1]] == 1)
                        {
                            count++;
                        }
                    }

                    if (count != 4)
                    {
                        //edits image for next iterations
                        nextImage[x][y] = 0;
                        erosionsTics = 1;
                    }
                    else
                    {
                        nextImage[x][y] = 1;
                    }
                }
                else
                {
                    nextImage[x][y] = 0;
                }
            }
        }

        //This should be made faster.
        for (int x = 0; x < BMP_WIDTH; x++)
        {
            for (int y = 0; y < BMP_HEIGTH; y++)
            {
                image[x][y] = nextImage[x][y];
            }
        }
        
        capture_cells(image);
        
    }
}

/*
    Main
*/

int main(int nPassedArguments, char **args)
{
    if (nPassedArguments != 4)
    {
        fprintf(stderr, "Needs 4 arguments: %s <input file path> <output file path> erosion = e, pattern = p\n", args[0]);
        exit(1);
    }

    //  read file
    read_bitmap(args[1], input_image);

    clock_t start, end;
    double cpu_time_used;

    start = clock();

    //outputEqualsInput();

    //  greyscale image
    unsigned char grey_image[BMP_WIDTH][BMP_HEIGTH];
    grey_scale_image(grey_image, input_image);

    // Pattern or erosion

    if (strcmp(args[3], "p") == 0)
    {
        pattern_search(grey_image);
    }else{
        binary_threshold(grey_image);
        
        erosion(grey_image);
    }

    end = clock();

    //image_to_3d(grey_image);

    //  create bmp file
    write_bitmap(input_image, args[2]);

    print_coordinates();

    printf("Cells counted: %d \n", countedCells);

    printf("Total erosions: %d \n", totalErosions);

    cpu_time_used = end - start;
    printf("Total time: %f ms\n", cpu_time_used * 1000.0 / CLOCKS_PER_SEC);

    return 0;
}
