#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include "defines.h"
#include "sobel.h"

#define THREAD_COUNT 12

typedef struct thread_data_t {
    ppm_t *image;
    ppm_image_t *greyscale;
    int start_row;
    int end_row;
} thread_data_t;

void* convert_row(void* arg) {
    thread_data_t* data = (thread_data_t*) arg;
    for (int i = data->start_row; i < data->end_row; i++) {
        data->greyscale->pixels[i] = malloc(sizeof(int) * data->greyscale->width);
        for (int j = 0; j < data->greyscale->width; j++) {
            data->greyscale->pixels[i][j] = (data->image->pixels[i][j].r + data->image->pixels[i][j].g + data->image->pixels[i][j].b) / 3;
            data->greyscale->proc_grey = rdtsc();
        }
    }
    return NULL;
}

int greyscale_convert(ppm_t *image, ppm_image_t *greyscale)
{
    // uint64_t end = 0;
    // uint64_t start = rdtsc();
    greyscale->width = image->width;
    greyscale->height = image->height;
    greyscale->max_value = image->max_value;
    greyscale->pixels = malloc(sizeof(int *) * greyscale->width);

    pthread_t threads[THREAD_COUNT];
    thread_data_t thread_data[THREAD_COUNT];

    int rows_per_thread = greyscale->height / THREAD_COUNT;
    printf("Rows {%d} {%ld}\n", rows_per_thread, time(NULL));

    for(int t = 0; t < THREAD_COUNT; t++) {
        thread_data[t].image = image;
        thread_data[t].greyscale = greyscale;
        thread_data[t].start_row = t * rows_per_thread;
        thread_data[t].end_row = (t == THREAD_COUNT - 1) ? greyscale->height : (t + 1) * rows_per_thread;
        pthread_create(&threads[t], NULL, convert_row, &thread_data[t]);
    }

    for(int t = 0; t < THREAD_COUNT; t++) {
        pthread_join(threads[t], NULL);
    }
    // end = rdtsc();
    // printf("START = [%lld] END = [%lld] ELAPSED = [%lld]\n", start, end, end - start);
    return RETURN_SUCCESS;
}
