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