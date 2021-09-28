//For each loop over array. Courtesy of https://stackoverflow.com/a/400970/16341756
//Can't get it to work
/*
#define foreach(item, array) \
    for(int keep = 1, \
            count = 0,\
            size = sizeof (array) / sizeof *(array); \
        keep && count != size; \
        keep = !keep, count++) \
      for(item = (array) + count; keep; keep = !keep)

#define array_elements(arr) ( sizeof(arr) / sizeof(arr[0]) )
#define array_for(item, array)	for(unsigned int cont=1, i=0; i<array_elements(array); cont=1, i++) for(item=&(array)[i]; cont; cont=0) /*

/*this is in the cbmp.h file, but listed here for reference
void read_bitmap(char *input_file_path,
                 unsigned char output_image_array[BMP_WIDTH]
                                                 [BMP_HEIGTH][BMP_CHANNELS]);*/

//Median filter to remove noise

/*
for (y = Radius; y < (M - Radius); y = y + 1)
{
  for (x = Radius; x < (N - Radius); x = x + 1)
  {
    GetPixelValues(x, y);
    SortPixelValues();
    value = FindMedian();
    SetPixel(output, x, y, value);
  }
}

Here M is the height of the image, N is the width of the image and Radius is
the radius of the filter. 3*3 pixels would have radius = 1

To identify the pattern of a cell:
Normalized Cross Correlation from Medical Image Analysis chapter 5

*/
/*
Books structuring element fit : Implementation of the fit operation

Temp = 0;
for (j = y - 1; j < (y + 2); j = j + 1)
{
  for (i = x - 1; i < (x + 2); i = i + 1)
  {
    if (GetPixel(input, i, j) == 1)
      Temp = Temp + 1;
  }
}
if (Temp == 9)
  SetPixel(output, x, y, 1);
else
  SetPixel(output, x, y, 0);

Here (x,y) is the position of the pixel being processed.

*/

/*
  Pattern rego
*/

/*

double NCCRequirement = 0.295;

//pattern recognition element
//alternative pattern could be less of a circle or 20 by 20
int ARRAY_CELL_SIZE = 21;
int cell_pattern[21][21] = {
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
};

int grey_cell_pattern[23][23] = {
	{62, 55, 53, 55, 58, 61, 69, 90, 108, 131, 140, 142, 134, 116, 96, 73, 61, 61, 57, 58, 61, 59, 57}, 
  {60, 55, 58, 63, 76, 95, 115, 134, 163, 186, 198, 201, 192, 176, 142, 111, 88, 68, 62, 61, 59, 60, 60}, 
  {62, 58, 64, 86, 117, 167, 196, 212, 219, 225, 230, 235, 233, 226, 212, 187, 142, 90, 66, 64, 60, 60, 60}, 
  {65, 65, 85, 116, 164, 209, 236, 242, 245, 246, 247, 251, 252, 250, 242, 226, 193, 139, 100, 77, 65, 61, 57}, 
  {64, 76, 111, 166, 203, 228, 240, 247, 247, 246, 244, 249, 251, 252, 249, 243, 233, 215, 175, 106, 70, 60, 58}, 
  {74, 100, 144, 193, 221, 233, 240, 244, 245, 244, 245, 249, 251, 251, 251, 251, 249, 248, 217, 142, 94, 70, 59}, 
  {81, 123, 167, 200, 218, 227, 235, 242, 240, 238, 241, 247, 249, 249, 247, 247, 249, 251, 233, 195, 138, 84, 60}, 
  {94, 149, 180, 202, 214, 221, 229, 233, 234, 233, 237, 244, 247, 243, 241, 245, 246, 251, 242, 224, 178, 105, 69}, 
  {100, 154, 182, 196, 208, 219, 223, 221, 227, 231, 237, 241, 242, 236, 237, 239, 243, 246, 244, 238, 201, 128, 86}, 
  {99, 153, 183, 194, 203, 215, 218, 215, 218, 224, 229, 238, 239, 239, 237, 237, 240, 246, 248, 245, 214, 150, 97}, 
  {96, 148, 178, 190, 200, 208, 215, 213, 212, 218, 223, 232, 237, 241, 240, 237, 240, 249, 252, 250, 219, 151, 96}, 
  {87, 134, 162, 181, 198, 205, 212, 209, 211, 214, 219, 227, 234, 240, 240, 237, 242, 248, 252, 249, 213, 135, 89}, 
  {78, 107, 144, 171, 188, 197, 205, 210, 214, 214, 221, 229, 233, 233, 239, 242, 246, 248, 248, 242, 207, 122, 80}, 
  {71, 92, 126, 162, 182, 189, 198, 208, 215, 213, 218, 225, 229, 233, 235, 241, 246, 248, 243, 228, 184, 106, 67}, 
  {68, 73, 104, 153, 181, 188, 197, 203, 208, 213, 218, 227, 231, 233, 235, 243, 247, 247, 232, 203, 149, 92, 64}, 
  {65, 63, 86, 134, 167, 179, 190, 199, 204, 207, 212, 223, 226, 227, 230, 236, 238, 238, 219, 170, 116, 78, 59}, 
  {62, 56, 70, 103, 137, 166, 184, 193, 197, 202, 206, 212, 217, 219, 221, 221, 224, 223, 190, 125, 80, 61, 52}, 
  {58, 54, 63, 79, 105, 141, 166, 179, 190, 195, 197, 201, 206, 209, 206, 202, 197, 188, 154, 96, 65, 54, 51}, 
  {57, 51, 54, 63, 77, 104, 134, 158, 172, 178, 184, 193, 197, 196, 191, 175, 156, 136, 104, 77, 64, 58, 58}, 
  {54, 51, 53, 57, 64, 77, 97, 125, 145, 153, 165, 169, 173, 174, 166, 141, 113, 90, 72, 63, 58, 60, 59}, 
  {55, 56, 55, 57, 59, 63, 71, 82, 94, 118, 131, 138, 138, 139, 126, 100, 82, 68, 62, 56, 57, 63, 60}, 
  {59, 54, 56, 58, 56, 57, 57, 58, 67, 85, 95, 98, 101, 99, 90, 73, 65, 58, 59, 56, 56, 61, 58}, }, 
  {57, 57, 58, 55, 57, 59, 57, 59, 63, 71, 74, 73, 72, 72, 67, 62, 60, 60, 58, 56, 57, 60, 59}, 
};

// **** Pattern search start
double get_templateLength(double templateLength)
{
    for (int cellx = 0; cellx < ARRAY_CELL_SIZE; cellx++)
    {
        for (int celly = 0; celly < ARRAY_CELL_SIZE; celly++)
        {
            templateLength += (cell_pattern[cellx][celly]) ^ 2;
        }
    }
    templateLength = sqrt(templateLength);
    return templateLength;
}

double use_pattern(unsigned char image[BMP_WIDTH][BMP_HEIGTH], int x, int y, double templateLength)
{
    int sum = 0;
    double patchLength = 0;
    for (int cellx = 0; cellx < ARRAY_CELL_SIZE; cellx++)
    {
        for (int celly = 0; celly < ARRAY_CELL_SIZE; celly++)
        {
            if (inside_bounds(x + cellx, y + celly) && image[x + cellx][y + celly] == 1)
            {
                sum += image[x + cellx][y + celly] * cell_pattern[cellx][celly];
                patchLength += (image[x + cellx][y + celly]) ^ 2;
            }
        }
    }
    patchLength = sqrt(patchLength);

    double NCC = sum / (patchLength * templateLength);
    return NCC;
}

void pattern_search(unsigned char image[BMP_WIDTH][BMP_HEIGTH])
{
    double templateLength = 0;
    templateLength = get_templateLength(templateLength);

    for (int x = 0; x < BMP_WIDTH; x++)
    {
        for (int y = 0; y < BMP_HEIGTH; y++)
        {
            if (use_pattern(image, x, y, templateLength) > NCCRequirement)
            {
                countedCells++;

                //mark it blue for pattern marked
                output_image[x][y][0] = 0;
                output_image[x][y][1] = 0;
                output_image[x][y][2] = 255;
            }
        }
    }
}
// *** Pattern serach end




//unneccesary
/*
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
*/



/*int all_neighbours[8][2] = {
    {-1, -1},
    {0, -1},
    {1, -1},
    {-1, 0},
    {1, 0},
    {-1, 1},
    {0, 1},
    {1, 1}};
    
    */
