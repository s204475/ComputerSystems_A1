#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cbmp.h"
//Wall = warning all
//To compile: gcc cbmp.c Algorithm.c -o .\Algorithm.exe -std=c99 -Wall
//To run: .\Algorithm.exe .\samples\easy\3EASY.bmp .\samples\easy\3EASYOutErosionTest.bmp

//Array to store the image (unsigned char = unsigned 8 bit)
unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
int treshold_value = 110;
int countedCells = 0;
int totalErosions = 0;
/*int structuring_element[3][3] = {
    {0, 1, 0},
    {1, 1, 1},
    {0, 1, 0}};*/
int neighbours[4][2] = {
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0}};

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

//unused right now. Output_image is directly modified in increment cell count
void image_to_3d(unsigned char image[BMP_WIDTH][BMP_HEIGTH])
{
    for (int x = 0; x < BMP_WIDTH; x++)
    {
        for (int y = 0; y < BMP_HEIGTH; y++)
        {
            for (int rgb = 0; rgb < 3; rgb++)
            {
                if (image[x][y] == 0)
                {
                    output_image[x][y][rgb] = 0;
                }
                else
                {
                    output_image[x][y][rgb] = 255;
                }
            }
        }
    }
}

int inside_bounds(int x, int y)
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

int increment_cell_count(unsigned char image[BMP_WIDTH][BMP_HEIGTH], int x, int y)
{

    //checking all neighbours
    for (int xx = -3; xx < 4; xx++)
    {
        for (int yy = -3; yy < 4; yy++)
        {
            if (output_image[x][y][0] == 255 || (inside_bounds(x + xx, y + yy) == 1 && image[x + xx][y + yy] == 1))
            {
                return 0;
            }
        }
    }

    //mark the cell
    for (int rgb = 0; rgb < 3; rgb++)
    {
        output_image[x][y][rgb] = 255;
    }

    //marks the pixels around
    for (int xx = -3; xx < 4; xx++)
    {
        for (int yy = -3; yy < 4; yy++)
        {
            if (inside_bounds(x + xx, y + yy))
            {
                output_image[x + xx][y + yy][0] = 244;
            }
        }
    }

    return 1;
}

//Iterates over the image. If it finds a white pixel, it checks the four neighbours directly above, below, left and right
//and if any are black, it itself becomes black. It then increments if there are no other sorrounding white pixels at all.
void erosion(unsigned char image[BMP_WIDTH][BMP_HEIGTH])
{
    int erosionsTics = 1;
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
                    int count = 0;
                    for (int i = 0; i < 4; i++)
                    {
                        if (inside_bounds(x + neighbours[i][0], y + neighbours[i][1]) == 1 && image[x + neighbours[i][0]][y + neighbours[i][1]] == 1)
                        {
                            count++;
                        }
                    }

                    if (count != 4)
                    {
                        image[x][y] = 0;
                        erosionsTics++;
                        countedCells += increment_cell_count(image, x, y);
                    }
                }
            }
        }
    }
}

void outputEqualsInput()
{
    for (int x = 0; x < BMP_WIDTH; x++)
    {
        for (int y = 0; y < BMP_HEIGTH; y++)
        {
            for (int rgb = 0; rgb < 3; rgb++)
            {
                output_image[x][y][rgb] = input_image[x][y][rgb];
            }
        }
    }
}

int main(int nPassedArguments, char **args)
{

    if (nPassedArguments != 3)
    {
        fprintf(stderr, "Needs 3 arguments: %s <input file path> <output file path>\n", args[0]);
        exit(1);
    }

    //read file
    read_bitmap(args[1], input_image);
    outputEqualsInput();

    //greyscale image
    unsigned char grey_image[BMP_WIDTH][BMP_HEIGTH];
    grey_scale_image(grey_image, input_image);

    binary_threshold(grey_image);

    erosion(grey_image);

    //image_to_3d(grey_image);

    //set output path by removing .bmp from the input, adding counted cells and .bmp again
    //char **outputPath = "";
    //strncpy(outputPath,args[1],strlen(args[1])-4);
    //int intLength = snprintf( NULL, 0, "%d", countedCells);
    //snprintf(outputPath, intLength, "%d", countedCells);
    //strncat(outputPath, ".bmp", 4);

    //create bmp file
    write_bitmap(output_image, args[2]);

    fprintf(stderr, "Cell count: %d \n", countedCells);
    fprintf(stderr, "Total erosions: %d", totalErosions);

    return 0;
}
