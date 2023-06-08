#include <stdio.h>
#include <stdlib.h>
#include "sobel.h"
#include "defines.h"

int save_greyscale(ppm_greyscale_t *greyscale, char *path)
{
    FILE *file = fopen(path, "w");
    if (file == NULL)
        return RETURN_FAILURE;
    fprintf(file, "P3\n");
    fprintf(file, "%d %d\n", greyscale->width, greyscale->height);
    fprintf(file, "%d\n", greyscale->max_value);
    for (int y = 0; y < greyscale->height; y++) {
        for (int x = 0; x < greyscale->width; x++) {
            fprintf(file, "%d\n%d\n%d\n", greyscale->pixels[y][x], greyscale->pixels[y][x], greyscale->pixels[y][x]);
        }
    }
    fclose(file);
    return RETURN_SUCCESS;
}