#include <stdio.h>
#include <stdlib.h>
#include "cbmp.h"

//To compile: gcc cbmp.c Algorithm.c -o .\Algorithm.exe -std=c99
//To run: .\Algorithm.exe .\samples\easy\1EASY.bmp .\samples\easy\1EASYout.bmp

//Array to store the image (unsigned char = unsigned 8 bit)
unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];

/*this is in the cbmp.h file, but listed here for reference
void read_bitmap(char *input_file_path,
                 unsigned char output_image_array[BMP_WIDTH]
                                                 [BMP_HEIGTH][BMP_CHANNELS]);*/

void grey_scale_image(unsigned char grey_image[BMP_WIDTH][BMP_HEIGTH],unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS])
{
    for (int x = 0; x < BMP_WIDTH; x++)
    {
        for (int y = 0; y < BMP_HEIGTH; y++)
        {
            grey_image[x][y] = (input_image[x][y][0] + input_image[x][y][1] + input_image[x][y][2]) / 3;
        }
    }
}

void test(int testInt)
{
    testInt++;
}

int main(int nPassedArguments, char **args)
{

    if (nPassedArguments != 3)
    {
        fprintf(stderr, "Needs 3 arguments: %s <input file path> <output file path>\n", args[0]);
        exit(1);
    }

    //for ease of reading. Strictly, it's inefficient
    char **inputPath = args[1];
    char **outputPath = args[2];

    //read file
    read_bitmap(inputPath, input_image);

    //greyscale image
    unsigned char grey_image[BMP_WIDTH][BMP_HEIGTH];
    grey_scale_image(grey_image,input_image); 
    

    //create bmp file
    //write_bitmap(output_image, outputPath);
    return 0;
}


