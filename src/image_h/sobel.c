#include <math.h>
#include <stdlib.h>
#include "defines.h"
#include "sobel.h"
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

#define THREAD_COUNT 12

typedef struct thread_data_t {
    ppm_image_t *greyscale;
    ppm_image_t *tmp;
    int start_row;
    int end_row;
} thread_data_t;

void* sobel_row(void* arg) {
    thread_data_t* data = (thread_data_t*) arg;
    for (int x = data->start_row; x < data->end_row; x++) {
        data->tmp->pixels[x] = malloc(sizeof(int) * data->tmp->width);
        for (int y = 0; y < data->greyscale->width; y++) {
            int gx = 0;
            int gy = 0;
            if (y == 0 || x == data->greyscale->height - 1 || x == 0 || y == data->greyscale->width - 1) {
                data->greyscale->pixels[x][y] = 0;
                continue;
            }
            gx += data->greyscale->pixels[x - 1][y - 1] * -1;
            gx += data->greyscale->pixels[x - 1][y] * -2;
            gx += data->greyscale->pixels[x - 1][y + 1] * -1;
            gx += data->greyscale->pixels[x + 1][y - 1];
            gx += data->greyscale->pixels[x + 1][y] * 2;
            gx += data->greyscale->pixels[x + 1][y + 1];
            gy += data->greyscale->pixels[x - 1][y - 1] * -1;
            gy += data->greyscale->pixels[x][y - 1] * -2;
            gy += data->greyscale->pixels[x + 1][y - 1] * -1;
            gy += data->greyscale->pixels[x - 1][y + 1];
            gy += data->greyscale->pixels[x][y + 1] * 2;
            gy += data->greyscale->pixels[x + 1][y + 1];
            data->tmp->pixels[x][y] = (int) sqrt(gx * gx + gy * gy);
            data->tmp->proc_sobel = rdtsc();
            data->tmp->proc_grey = data->greyscale->proc_grey;
        }
    }
    return NULL;
}

int sobel_filter(ppm_image_t *greyscale)
{
    ppm_image_t tmp;
    tmp.height = greyscale->height;
    tmp.width = greyscale->width;
    tmp.max_value = greyscale->max_value;
    tmp.pixels = malloc(sizeof(int *) * tmp.height);

    pthread_t threads[THREAD_COUNT];
    thread_data_t thread_data[THREAD_COUNT];

    int rows_per_thread = greyscale->height / THREAD_COUNT;

    for(int t = 0; t < THREAD_COUNT; t++) {
        thread_data[t].greyscale = greyscale;
        thread_data[t].tmp = &tmp;
        thread_data[t].start_row = t * rows_per_thread;
        thread_data[t].end_row = (t == THREAD_COUNT - 1) ? greyscale->height : (t + 1) * rows_per_thread;
        pthread_create(&threads[t], NULL, sobel_row, &thread_data[t]);
    }
    for(int t = 0; t < THREAD_COUNT; t++) {
        pthread_join(threads[t], NULL);
    }
    save_greyscale(&tmp, "sobel_output.ppm");
    save_vizualizer(&tmp, "sobel_filter_visualizer.myppm");
    return RETURN_SUCCESS;
}
