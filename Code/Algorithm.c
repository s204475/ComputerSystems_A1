#include <stdio.h>
#include <stdlib.h>
#include "cbmp.h"

//To compile: gcc cbmp.c Algorithm.c -o .\Algorithm.exe -std=c99
//To run: .\Algorithm.exe .\samples\easy\1EASY.bmp .\samples\easy\1EASYoutErosion2.bmp

//Array to store the image (unsigned char = unsigned 8 bit)
unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
int treshold_value = 90;
int countedCells = 0;
int structuring_element[3][3] = {
    {0, 1, 0},
    {1, 1, 1},
    {0, 1, 0}};
int neighbours[2][4] = {
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0}}
/*int alt_structuring_element[4] = {
    {1, 0},
    {0,1},
    {2,1},
    {1,2}
    };*/

/*this is in the cbmp.h file, but listed here for reference
void read_bitmap(char *input_file_path,
                 unsigned char output_image_array[BMP_WIDTH]
                                                 [BMP_HEIGTH][BMP_CHANNELS]);*/

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
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (inside_bounds(x, y) == 1)
            {
                if (image[x][y] == 1)
                {
                    return 0;
                }
            }
        }
    }

    return 1;
}

int structuring_element_check(int x, int y)
{
    if(image[x][y+1]==0 )
    {
        
    }
}

void erosion(unsigned char image[BMP_WIDTH][BMP_HEIGTH], int numberOfErosions)
{
    for (int i = 0; i < numberOfErosions; i++)
    {
        for (int x = 0; x < BMP_WIDTH; x++)
        {
            for (int y = 0; y < BMP_HEIGTH; y++)
            {
                if (image[x][y] == 1)
                {
                    /*
                    for (int structX = -1; structX < 2; structX++)
                    {
                        for (int structY = -1; structY < 2; structY++)
                        {
                            if (inside_bounds(x + structX, y + structY))
                            {
                                tempArr[x][y] = image[x][y];
                            }
                        }
                    }
                    */
                }
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

    //greyscale image
    unsigned char grey_image[BMP_WIDTH][BMP_HEIGTH];
    grey_scale_image(grey_image, input_image);

    binary_threshold(grey_image);

    erosion(grey_image, 9);

    image_to_3d(grey_image);

    //create bmp file
    write_bitmap(output_image, args[2]);

    fprintf(stderr, "Cell count: %d", countedCells);

    return 0;
}
