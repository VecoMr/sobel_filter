#include <stdio.h>

void print_help(void)
{
    printf("Usage: ./sobel_filter PATH\n");
    printf("DESCRIPTION: apply the sobel filter to the image at PATH\n");
    printf("\tPATH: path to the ppm (P3) image to process\n");
}