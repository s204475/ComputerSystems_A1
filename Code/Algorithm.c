#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cbmp.h"
//Wall = warning all
//To compile: gcc cbmp.c Algorithm.c -o .\Algorithm.exe -std=c99 -Wall
/*To run: 

.\Algorithm.exe .\samples\easy\5EASY.bmp .\samples\easy\5EASYOutErosionTest.bmp

.\Algorithm.exe .\samples\hard\4HARD.bmp .\samples\hard\4HARDOutErosionTest.bmp

*/

//Array to store the image (unsigned char = unsigned 8 bit)
unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char coordinates[BMP_WIDTH][BMP_HEIGTH];
int treshold_value = 100;
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

int all_neighbours[8][2] = {
    {-1, -1},
    {0, -1},
    {1, -1},
    {-1, 0},
    {1, 0},
    {-1, 1},
    {0, 1},
    {1, 1}};

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

void mark_cell(int x, int y)
{
    coordinates[x][y] = 1;

    output_image[x][y][0] = 255;

    //marks the pixels around in a cross
    for (int i = 0; i < 4; i++)
    {
        if (inside_bounds(x + neighbours[i][0], y + neighbours[i][1]) == 1)
        {
            output_image[x + neighbours[i][0]][y + neighbours[i][1]][0] = 255;
        }
    }
}

//remove the found cell and replaces it with black pixels
void remove_cell(int x, int y, int given_layer,unsigned char image[BMP_WIDTH][BMP_HEIGTH])
{
    for(int x = 0;x<BMP_WIDTH;x++)
    {
        for(int y = 0; y<BMP_HEIGTH;y++)
        {
            for(int layer = 0;layer<given_layer;given_layer++)
            {
                for(int i = 0; i<8;i++)
                {
                    if (inside_bounds(x + all_neighbours[i][0] * layer, y + all_neighbours[i][1] * layer))
                    {
                        image[x + all_neighbours[i][0] * layer][y + all_neighbours[i][1] * layer] = 0;
                    }
                }
            }
        }
    }
}

int find_white_neighbours(unsigned char image[BMP_WIDTH][BMP_HEIGTH], int x, int y)
{
    for (int layer = 1; layer <= 12; layer++)
    {
        char found = 0;
        for (int i = 0; i < 8; i++)
        {
            if (inside_bounds(x + all_neighbours[i][0] * layer, y + all_neighbours[i][1] * layer) && image[x + all_neighbours[i][0] * layer][y + all_neighbours[i][1] * layer] == 1)
            {
                found = 1;
                break; //tries next layer
            }
        }
        if (found == 0){
            remove_cell(x,y,layer,image);
            return layer;
        }
    }

    return 0;
}

void capture_cells(unsigned char image[BMP_WIDTH][BMP_HEIGTH])
{
    //mark the cell
    for (int x = 0; x < BMP_WIDTH; x++)
    {
        for (int y = 0; y < BMP_HEIGTH; y++)
        {
            if (image[x][y] == 1 && find_white_neighbours(image, x, y) == 0)
            {
                mark_cell(x, y);
                countedCells++;
            }
        }
    }
}

//Iterates over the image. If it finds a white pixel, it checks the four neighbours directly above, below, left and right
//and if any are black, it itself becomes black. It then increments if there are no other sorrounding white pixels at all.
void erosion(unsigned char image[BMP_WIDTH][BMP_HEIGTH])
{
    unsigned char nextImage[BMP_WIDTH][BMP_HEIGTH];
    int erosionsTics = 1;
    while (totalErosions < 8)
    {
        totalErosions++;
        //erosionsTics = 0;
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
                        //edits image for next iterations
                        nextImage[x][y] = 0;
                        erosionsTics += 1;
                    }
                    else
                    {
                        nextImage[x][y] = 1;
                    }
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

        //desperate fix
        for (int x = BMP_WIDTH - 3; x < BMP_WIDTH; x++)
        {
            for (int y = 0; y < BMP_HEIGTH; y++)
            {
                image[x][y] = 0;
            }
        }

        capture_cells(image);
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

char *get_coordinates()
{
    char *coordinates_string = "";
    for (int x = 0; x < BMP_WIDTH; x++)
    {
        for (int y = 0; y < BMP_HEIGTH; y++)
        {
            if (coordinates[x][y] == 1)
            {
                sprintf(coordinates_string, "%s %d", coordinates_string, x);
                strcat(coordinates_string, ",");
                sprintf(coordinates_string, "%s %d", coordinates_string, y);
                strcat(coordinates_string, " ");
            }
        }
        strcat(coordinates_string, "\n");
    }
    return coordinates_string;
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

    fprintf(stderr, "Cell count using erosion: %d \n", countedCells);

    fprintf(stderr, "Total erosions: %d \n", totalErosions);

    //fprintf(stderr, "Coordinates: \n", get_coordinates);

    return 0;
}
