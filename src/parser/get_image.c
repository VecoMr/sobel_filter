#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "sobel.h"
#include "defines.h"

static int read_ppm(char *path, ppm_t *image)
{
    FILE *file = fopen(path, "r");
    if (!file) {
        return RETURN_FAILURE;
    }
    fscanf(file, "P3\n%d %d\n%d\n", &image->width, &image->height, &image->max_value);
    image->pixels = malloc(sizeof(pixels_t) * image->height);
    for (int i = 0; i < image->height; i++) {
        image->pixels[i] = malloc(sizeof(pixels_t) * image->width);
        for (int j = 0; j < image->width; j++) {
            fscanf(file, "%d\n", &(image->pixels[i][j].r));
            fscanf(file, "%d\n", &(image->pixels[i][j].g));
            fscanf(file, "%d\n", &(image->pixels[i][j].b));
        }
    }
    fclose(file);
    return RETURN_SUCCESS;
}

int get_image(int ac, char **av, ppm_t *image)
{
    write(1, "LOAD START\n", 12);
    if (ac != 2) {
        print_help();
        return RETURN_FAILURE;
    }
    if (read_ppm(av[1], image) == RETURN_FAILURE) {
        fprintf(stderr, "Error: could not read %s\n", av[1]);
        return RETURN_FAILURE;
    }
    write(1, "LOAD END\n", 10);
    return RETURN_SUCCESS;
}
