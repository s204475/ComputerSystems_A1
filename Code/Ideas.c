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

