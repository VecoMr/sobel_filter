#pragma once

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
int sobel_filter(int ac, char **av);