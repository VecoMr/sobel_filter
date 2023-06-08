#include <math.h>
#include <stdlib.h>
#include "defines.h"
#include "sobel.h"

int sobel_filter(ppm_greyscale_t *greyscale)
{
    ppm_greyscale_t tmp;
    tmp.height = greyscale->height;
    tmp.width = greyscale->width;
    tmp.max_value = greyscale->max_value;
    tmp.pixels = malloc(sizeof(int *) * tmp.width);
    for (int x = 0; x < greyscale->width; x++) {
        tmp.pixels[x] = malloc(sizeof(int) * tmp.height);
        for (int y = 0; y < greyscale->height; y++) {
            int gx = 0;
            int gy = 0;
            if (y == 0 || x == greyscale->width - 1 || x == 0 || y == greyscale->width - 1) {
                greyscale->pixels[x][y] = 0;
                continue;
            }
            gx += greyscale->pixels[x - 1][y - 1] * -1;
            gx += greyscale->pixels[x - 1][y] * -2;
            gx += greyscale->pixels[x - 1][y + 1] * -1;
            gx += greyscale->pixels[x + 1][y - 1];
            gx += greyscale->pixels[x + 1][y] * 2;
            gx += greyscale->pixels[x + 1][y + 1];
            gy += greyscale->pixels[x - 1][y - 1] * -1;
            gy += greyscale->pixels[x][y - 1] * -2;
            gy += greyscale->pixels[x + 1][y - 1] * -1;
            gy += greyscale->pixels[x - 1][y + 1];
            gy += greyscale->pixels[x][y + 1] * 2;
            gy += greyscale->pixels[x + 1][y + 1];
            (&tmp)->pixels[x][y] = (int) sqrt(gx * gx + gy * gy);
        }
    }
    save_greyscale(&tmp, "tmp.ppm");
    return RETURN_SUCCESS;
}