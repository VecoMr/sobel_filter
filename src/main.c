#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "defines.h"
#include "sobel.h"

int main(int ac, char **av) {
    ppm_t image;
    ppm_greyscale_t greyscale;

    time_t start = time(NULL);
    sleep(5);

    if (get_image(ac, av, &image) == RETURN_FAILURE)
        return EXIT_FAILURE;
    if (greyscale_convert(&image, &greyscale) == RETURN_FAILURE)
        return EXIT_FAILURE;
    save_greyscale(&greyscale, "output.ppm");
    printf("greyscale saved in output.ppm\n");
    if (sobel_filter(&greyscale) == RETURN_FAILURE)
        return EXIT_FAILURE;
    printf("ELAPSED [%d]\n", time(NULL) - start);
    return EXIT_SUCCESS;
}