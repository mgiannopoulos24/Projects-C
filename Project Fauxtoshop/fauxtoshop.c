#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BITMAPINFOHEADER;
#pragma pack(pop)

typedef struct {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} RGBTRIPLE;

int main() {
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    
    // Read file header
    if (fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, stdin) != 1) {
        fprintf(stderr, "Error reading BMP file header\n");
        return 1;
    }

    // Read info header
    if (fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, stdin) != 1) {
        fprintf(stderr, "Error reading BMP info header\n");
        return 1;
    }

    // Validate BMP format
    if (fileHeader.bfType != 0x4D42 || infoHeader.biBitCount != 24 || infoHeader.biSize != 40) {
        fprintf(stderr, "Unsupported BMP format\n");
        return 1;
    }

    int width = infoHeader.biWidth;
    int height = infoHeader.biHeight;
    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    RGBTRIPLE** image = malloc(height * sizeof(RGBTRIPLE*));
    if (!image) {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }

    for (int i = 0; i < height; i++) {
        image[i] = malloc(width * sizeof(RGBTRIPLE));
        if (!image[i]) {
            fprintf(stderr, "Memory allocation error\n");
            for (int j = 0; j < i; j++) {
                free(image[j]);
            }
            free(image);
            return 1;
        }
        if (fread(image[i], sizeof(RGBTRIPLE), width, stdin) != (size_t)width) {
            fprintf(stderr, "Error reading BMP pixel data\n");
            for (int j = 0; j <= i; j++) {
                free(image[j]);
            }
            free(image);
            return 1;
        }
        fseek(stdin, padding, SEEK_CUR);
    }

    // Allocate memory for the rotated image
    RGBTRIPLE** rotatedImage = malloc(width * sizeof(RGBTRIPLE*));
    if (!rotatedImage) {
        fprintf(stderr, "Memory allocation error\n");
        for (int i = 0; i < height; i++) {
            free(image[i]);
        }
        free(image);
        return 1;
    }

    for (int i = 0; i < width; i++) {
        rotatedImage[i] = malloc(height * sizeof(RGBTRIPLE));
        if (!rotatedImage[i]) {
            fprintf(stderr, "Memory allocation error\n");
            for (int j = 0; j < i; j++) {
                free(rotatedImage[j]);
            }
            free(rotatedImage);
            for (int j = 0; j < height; j++) {
                free(image[j]);
            }
            free(image);
            return 1;
        }
    }

    // Rotate the image
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            rotatedImage[j][height - 1 - i] = image[i][j];
        }
    }

    // Free the original image memory
    for (int i = 0; i < height; i++) {
        free(image[i]);
    }
    free(image);

    // Update headers for the rotated image
    infoHeader.biWidth = height;
    infoHeader.biHeight = width;
    int newPadding = (4 - (infoHeader.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    infoHeader.biSizeImage = (infoHeader.biWidth * sizeof(RGBTRIPLE) + newPadding) * infoHeader.biHeight;
    fileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + infoHeader.biSizeImage;

    // Write file header
    if (fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, stdout) != 1) {
        fprintf(stderr, "Error writing BMP file header\n");
        for (int i = 0; i < width; i++) {
            free(rotatedImage[i]);
        }
        free(rotatedImage);
        return 1;
    }

    // Write info header
    if (fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, stdout) != 1) {
        fprintf(stderr, "Error writing BMP info header\n");
        for (int i = 0; i < width; i++) {
            free(rotatedImage[i]);
        }
        free(rotatedImage);
        return 1;
    }

    // Write pixel data for the rotated image
    for (int i = 0; i < infoHeader.biHeight; i++) {
        if (fwrite(rotatedImage[i], sizeof(RGBTRIPLE), infoHeader.biWidth, stdout) != (size_t)infoHeader.biWidth) {
            fprintf(stderr, "Error writing BMP pixel data\n");
            for (int j = 0; j < width; j++) {
                free(rotatedImage[j]);
            }
            free(rotatedImage);
            return 1;
        }
        for (int j = 0; j < newPadding; j++) {
            fputc(0x00, stdout);
        }
    }

    // Free the rotated image memory
    for (int i = 0; i < width; i++) {
        free(rotatedImage[i]);
    }
    free(rotatedImage);

    return 0;
}
