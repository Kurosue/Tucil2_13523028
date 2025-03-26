#include "header/imageprocessor.h"

uint32_t* extractImage(int width, int height, FILE* file)
{
    uint32_t* image;
    image = (uint32_t*)malloc(width * height * sizeof(uint32_t));
    fread(image, sizeof(uint32_t), width * height, file);
    return image;
}

void getHeader(int *width, int *height, FILE* file)
{
    fread(width, sizeof(int), 1, file);
    fread(height, sizeof(int), 1, file);
}