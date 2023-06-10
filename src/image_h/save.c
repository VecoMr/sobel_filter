#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sobel.h"
#include "defines.h"

int save_vizualizer(ppm_image_t *image, char *path)
{
    write(1, "SAVE VISUALIZE START\n", 22);
    FILE *file = fopen(path, "w");

    if (file == NULL)
        return RETURN_FAILURE;
    fprintf(file, "P3\n");
    fprintf(file, "%d %d\n", image->width, image->height);
    fprintf(file, "%d\n", image->max_value);
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            fprintf(file, "%d %d %d %lld %lld\n", image->pixels[y][x], image->pixels[y][x], image->pixels[y][x], image->proc_grey, image->proc_sobel);
        }
    }
    fclose(file);
    write(1, "SAVE VISUALIZER END\n", 21);
    return RETURN_SUCCESS;
}

int save_greyscale(ppm_image_t *image, char *path)
{
    write(1, "SAVE START\n", 12);
    FILE *file = fopen(path, "w");
    if (file == NULL)
        return RETURN_FAILURE;
    fprintf(file, "P3\n");
    fprintf(file, "%d %d\n", image->width, image->height);
    fprintf(file, "%d\n", image->max_value);
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            fprintf(file, "%d\n%d\n%d\n", image->pixels[y][x], image->pixels[y][x], image->pixels[y][x]);
        }
    }
    fclose(file);
    write(1, "SAVE END\n", 10);
    return RETURN_SUCCESS;
}