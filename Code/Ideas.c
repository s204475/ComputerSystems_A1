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



*/
