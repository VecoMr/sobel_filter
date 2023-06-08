#include "defines.h"
#include "sobel.h"

int main(int ac, char **av) {
    ppm_t image;
    ppm_greyscale_t greyscale;

    if (get_image(ac, av, &image) == RETURN_FAILURE)
        return EXIT_FAILURE;
    if (greyscale_convert(&image, &greyscale) == RETURN_FAILURE)
        return EXIT_FAILURE;
    if (sobel_filter(ac, av) == RETURN_FAILURE)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}