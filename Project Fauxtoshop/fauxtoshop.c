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

int main() {
    // Read BMP header
    BMPHeader header;
    if (fread(&header, sizeof(BMPHeader), 1, stdin) != 1 || header.type != 0x4D42) {
        fprintf(stderr, "Error: Not a valid BMP file.\n");
        return 1;
    }

    // Read BMP info header
    BMPInfoHeader info_header;
    if (fread(&info_header, sizeof(BMPInfoHeader), 1, stdin) != 1) {
        fprintf(stderr, "Error: Unable to read BMP info header.\n");
        return 1;
    }

    // Check if the image is 24-bit BMP
    if (info_header.bit_count != 24) {
        fprintf(stderr, "Error: Only 24-bit BMP images are supported.\n");
        return 1;
    }

    // Write headers to output
    fwrite(&header, sizeof(BMPHeader), 1, stdout);
    fwrite(&info_header, sizeof(BMPInfoHeader), 1, stdout);

    // Compute padding
    int padding = (4 - (info_header.width * 3) % 4) % 4;

    // Allocate memory for pixel data
    uint8_t *pixels = (uint8_t *)malloc((info_header.width * 3 + padding) * info_header.height);
    if (!pixels) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 1;
    }

    // Read pixel data
    if (fread(pixels, sizeof(uint8_t), (info_header.width * 3 + padding) * info_header.height, stdin) !=
        (info_header.width * 3 + padding) * info_header.height) {
        fprintf(stderr, "Error: Unable to read pixel data.\n");
        free(pixels);
        return 1;
    }

    // Rotate image 90 degrees clockwise
    for (int y = 0; y < info_header.height; y++) {
        for (int x = info_header.width - 1; x >= 0; x--) {
            fwrite(&pixels[(x * 3 + padding) * info_header.height + y * 3], sizeof(uint8_t), 3, stdout);
        }
        // Write padding
        for (int i = 0; i < padding; i++) {
            fputc(0x00, stdout);
        }
    }

    free(pixels);
    return 0;
}
