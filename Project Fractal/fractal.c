#include "complexlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BMP_HEADER_SIZE 14
#define DIB_HEADER_SIZE 40
#define MAX_COLORS 256

typedef struct {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} RGB;

void create_bmp(const char *filename, RGB *image, int width, int height) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open BMP file");
        exit(EXIT_FAILURE);
    }

    int row_padded = (width * 3 + 3) & (~3);
    int image_size = row_padded * height;
    int file_size = BMP_HEADER_SIZE + DIB_HEADER_SIZE + image_size;

    unsigned char bmp_header[BMP_HEADER_SIZE] = {
        0x42, 0x4D,          // Signature 'BM'
        file_size & 0xFF, (file_size >> 8) & 0xFF, (file_size >> 16) & 0xFF, (file_size >> 24) & 0xFF,  // File size
        0, 0,  // Reserved
        0, 0,  // Reserved
        BMP_HEADER_SIZE + DIB_HEADER_SIZE, 0, 0, 0  // Offset to pixel data
    };

    unsigned char dib_header[DIB_HEADER_SIZE] = {
        DIB_HEADER_SIZE, 0, 0, 0, 0, // DIB header size
        width & 0xFF, (width >> 8) & 0xFF, (width >> 16) & 0xFF, (width >> 24) & 0xFF,  // Image width
        height & 0xFF, (height >> 8) & 0xFF, (height >> 16) & 0xFF, (height >> 24) & 0xFF,  // Image height
        1, 0,  // Number of color planes
        24, 0, // Bits per pixel
        0, 0, 0, 0, // Compression (none)
        image_size & 0xFF, (image_size >> 8) & 0xFF, (image_size >> 16) & 0xFF, (image_size >> 24) & 0xFF,  // Image size
        0x13, 0x0B, 0, 0, // Horizontal resolution (2835 pixels/meter)
        0x13, 0x0B, 0, 0, // Vertical resolution (2835 pixels/meter)
        0, 0, 0, 0, // Number of colors in palette
        0, 0, 0 // Important colors
    };

    fwrite(bmp_header, 1, BMP_HEADER_SIZE, file);
    fwrite(dib_header, 1, DIB_HEADER_SIZE, file);

    unsigned char *row = calloc(row_padded, sizeof(unsigned char));
    if (!row) {
        perror("Failed to allocate memory for BMP row");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    for (int y = height - 1; y >= 0; y--) {
        memcpy(row, &image[y * width], width * 3);
        fwrite(row, sizeof(unsigned char), row_padded, file);
    }

    free(row);
    fclose(file);
}

RGB get_color(int iter, int max_iter) {
    double t = (double)iter / max_iter;
    RGB color;
    color.red = (unsigned char)(9 * (1 - t) * t * t * t * 255);
    color.green = (unsigned char)(15 * (1 - t) * (1 - t) * t * t * 255);
    color.blue = (unsigned char)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
    return color;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s inputfile [-g output.bmp]\n", argv[0]);
        return 1;
    }

    char *input_file = argv[1];
    char *output_file = NULL;

    if (argc == 4 && strcmp(argv[2], "-g") == 0) {
        output_file = argv[3];
    } else if (argc > 2 && strcmp(argv[2], "-g") != 0) {
        fprintf(stderr, "Invalid arguments\n");
        return 1;
    }

    double *coeffs;
    int degree;
    Complex min, max;
    double step;

    parse_input(input_file, &coeffs, &degree, &min, &max, &step);

    int width = (int)((max.real - min.real) / step) + 1;
    int height = (int)((max.imag - min.imag) / step) + 1;

    RGB *image = calloc(width * height, sizeof(RGB));
    if (!image) {
        perror("Failed to allocate memory for image");
        free(coeffs);
        return 1;
    }

    for (double real = min.real; real <= max.real; real += step) {
        for (double imag = min.imag; imag <= max.imag; imag += step) {
            Complex z = {real, imag};
            Complex z_next = z;
            int iter;

            for (iter = 0; iter < MAX_ITER; iter++) {
                z_next = newton_raphson_step(z, coeffs, degree);
                if (isnan(z_next.real) || isnan(z_next.imag)) {
                    break;
                }
                if (complex_abs(complex_sub(z_next, z)) < TOLERANCE) {
                    break;
                }
                z = z_next;
            }

            int x = (int)((real - min.real) / step);
            int y = (int)((max.imag - imag) / step);

            image[y * width + x] = get_color(iter, MAX_ITER);
        }
    }

    if (output_file) {
        create_bmp(output_file, image, width, height);
        printf("Fractal saved to %s\n", output_file);
    } else {
        find_roots(coeffs, degree, min, max, step);
    }

    free(coeffs);
    free(image);
    return 0;
}