#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
} BMPHeader;

typedef struct {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bit_count;
    uint32_t compression;
    uint32_t image_size;
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t colors_used;
    uint32_t colors_important;
} BMPInfoHeader;
#pragma pack(pop)

void print_usage(char *program_name) {
    printf("Usage: %s <input_file.bmp> <output_file.bmp>\n", program_name);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        print_usage(argv[0]);
        return 1;
    }

    char *input_filename = argv[1];
    char *output_filename = argv[2];

    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        fprintf(stderr, "Error: Cannot open input file %s\n", input_filename);
        return 1;
    }

    BMPHeader header;
    if (fread(&header, sizeof(BMPHeader), 1, input_file) != 1 || header.type != 0x4D42) {
        fprintf(stderr, "Error: Not a valid BMP file.\n");
        fclose(input_file);
        return 1;
    }

    BMPInfoHeader info_header;
    if (fread(&info_header, sizeof(BMPInfoHeader), 1, input_file) != 1) {
        fprintf(stderr, "Error: Unable to read BMP info header.\n");
        fclose(input_file);
        return 1;
    }

    if (info_header.bit_count != 24) {
        fprintf(stderr, "Error: Only 24-bit BMP images are supported.\n");
        fclose(input_file);
        return 1;
    }

    FILE *output_file = fopen(output_filename, "wb");
    if (!output_file) {
        fprintf(stderr, "Error: Cannot open output file %s\n", output_filename);
        fclose(input_file);
        return 1;
    }

    // Calculate padding for the original image
    int original_padding = (4 - (info_header.width * 3) % 4) % 4;
    int rotated_padding = (4 - (info_header.height * 3) % 4) % 4;

    // Allocate memory for pixel data of the original image
    uint8_t *pixels = (uint8_t *)malloc((info_header.width * 3 + original_padding) * info_header.height);
    if (!pixels) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        fclose(input_file);
        fclose(output_file);
        return 1;
    }

    // Read pixel data from input file
    if (fread(pixels, sizeof(uint8_t), (info_header.width * 3 + original_padding) * info_header.height, input_file) !=
        (info_header.width * 3 + original_padding) * info_header.height) {
        fprintf(stderr, "Error: Unable to read pixel data.\n");
        free(pixels);
        fclose(input_file);
        fclose(output_file);
        return 1;
    }

    // Allocate memory for rotated pixel data
    uint8_t *rotated_pixels = (uint8_t *)malloc((info_header.height * 3 + rotated_padding) * info_header.width);
    if (!rotated_pixels) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        free(pixels);
        fclose(input_file);
        fclose(output_file);
        return 1;
    }

    // Rotate image 90 degrees clockwise
    for (int y = 0; y < info_header.height; y++) {
        for (int x = 0; x < info_header.width; x++) {
            // Calculate new coordinates in rotated image
            int original_offset = (y * (info_header.width * 3 + original_padding)) + (x * 3);
            int rotated_offset = ((info_header.width - x - 1) * (info_header.height * 3 + rotated_padding)) + (y * 3);

            // Copy pixel data
            rotated_pixels[rotated_offset] = pixels[original_offset];
            rotated_pixels[rotated_offset + 1] = pixels[original_offset + 1];
            rotated_pixels[rotated_offset + 2] = pixels[original_offset + 2];
        }
    }

    // Write headers to output
    fwrite(&header, sizeof(BMPHeader), 1, output_file);
    fwrite(&info_header, sizeof(BMPInfoHeader), 1, output_file);

    // Write rotated pixel data to output file
    fwrite(rotated_pixels, sizeof(uint8_t), (info_header.height * 3 + rotated_padding) * info_header.width, output_file);

    // Clean up
    free(pixels);
    free(rotated_pixels);
    fclose(input_file);
    fclose(output_file);

    return 0;
}
