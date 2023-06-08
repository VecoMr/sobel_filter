#include <stdlib.h>
#include "defines.h"
#include "sobel.h"

// TODO: paralaliser cette fonction avec openmp et sans / ajout possible de cache et/ou memoization
int greyscale_convert(ppm_t *image, ppm_greyscale_t *greyscale)
{
    greyscale->width = image->width;
    greyscale->height = image->height;
    greyscale->max_value = image->max_value;
    greyscale->pixels = malloc(sizeof(int *) * greyscale->width);
    for (int i = 0; i < greyscale->width; i++) {
        greyscale->pixels[i] = malloc(sizeof(int) * greyscale->height);
        for (int j = 0; j < greyscale->height; j++) {
            greyscale->pixels[i][j] = (image->pixels[i][j].r + image->pixels[i][j].g + image->pixels[i][j].b) / 3;
        }
    }
    return RETURN_SUCCESS;
}
