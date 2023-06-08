#include "defines.h"
#include "sobel.h"

int main(int ac, char **av) {
    ppm_t image;
    ppm_greyscale_t greyscale;

    if (get_image(ac, av, &image) == RETURN_FAILURE)
        return EXIT_FAILURE;
    if (greyscale_convert(&image, &greyscale) == RETURN_FAILURE)
        return EXIT_FAILURE;
    save_greyscale(&greyscale, "output.ppm");
    if (sobel_filter(&greyscale) == RETURN_FAILURE)
        return EXIT_FAILURE;
    save_greyscale(&greyscale, "foutput.ppm");

    return EXIT_SUCCESS;
}