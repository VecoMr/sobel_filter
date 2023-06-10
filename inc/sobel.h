#pragma once

    #include <stdint.h>

    typedef struct pixels_s{
        int r;
        int g;
        int b;
    } pixels_t;

    typedef struct ppm_s{
        int width;
        int height;
        int max_value;
        pixels_t **pixels;
    } ppm_t;

     typedef struct ppm_image_s{
        int width;
        int height;
        int max_value;
        unsigned char **pixels;
        uint64_t proc_grey;
        uint64_t proc_sobel;
    } ppm_image_t;

// --- MAIN ---
// main.c
int main(int ac, char **av);

// --- ERROR_H ---
// print_help.c
void print_help(void);

// --- PARSER ---
// get_image.c
int get_image(int ac, char **av, ppm_t *image);

// --- IMAGE_H ---
// sobel.c
int sobel_filter(ppm_image_t *greyscale);

// greyscale.c
int greyscale_convert(ppm_t *image, ppm_image_t *greyscale);

// save.c
int save_vizualizer(ppm_image_t *image, char *path);
int save_greyscale(ppm_image_t *greyscale, char *path);

// --- UTILS ---
// cycle.c
uint64_t rdtsc(void);
