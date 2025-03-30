// main.c
// 13523028 - Muhammad Aditya Rahmadeni
#include <stdlib.h>
#include <string.h>
#include "header/image.h"
#include "header/errorcalculations.h"

char* absolPath;
Image image;
Image res;

void inputHandler()
{
    // [Input] Absolut Path dari file
    while(true)
    {
        printf("Masukkan nama file gambar yang ingin diproses ( \033[1;33mCATATAN : PASTIKAN FILE ADA DALAM FOLDER TEST\033[0m ) \n> ");
        char* fileName = (char*)malloc(100 * sizeof(char));
        absolPath = (char*)malloc(200 * sizeof(char));

        strcpy(absolPath, "./test/");
        scanf("%s", fileName);
        strcat(absolPath, fileName);
        
        FILE* file = fopen(absolPath, "r");
        if(file == NULL)
        {
            printf("\033[1;31m[ERROR]\033[0m File pada \033[1;34m%s\033[0m tidak ditemukan, silahkan coba lagi.\n", absolPath);
            continue;
        }
        else
        {
            printf("File ditemukan !\n\n");
            extractImage(file, &image);
            break;
        }   
    }

    // [Input] Metode perhitungan error & Threshold
    chooseErrorMethod();
}
void normalizeImage(Image* im)
{
    for (int i = 0; i < im->width * im->height; i++)
    {
        uint32_t pixel = im->data[i];
        uint8_t r = (pixel >> 16) & 0xFF;
        uint8_t g = (pixel >> 8) & 0xFF;
        uint8_t b = pixel & 0xFF;

        // Normalize the pixel values
        r = (r > 255) ? 255 : r;
        g = (g > 255) ? 255 : g;
        b = (b > 255) ? 255 : b;

        im->data[i] = (r << 16) | (g << 8) | b;
    }
}

void divideNConquer(Image im, double threshold, Image* res)
{
    double error = calculateVariance(im.data, im.width, im.height);

    if (error > threshold)
    {
        int newWidth = im.width / 2;
        int newHeight = im.height / 2;

        if (newWidth == 0 || newHeight == 0) return;

        Image subImages[4];

        for (int i = 0; i < 4; i++)
        {
            subImages[i].width = newWidth;
            subImages[i].height = newHeight;
            subImages[i].data = (uint8_t*)malloc(newWidth * newHeight * sizeof(uint8_t));
        }

        // Copy pixels into sub-images
        for (int y = 0; y < im.height; y++)
        {
            for (int x = 0; x < im.width; x++)
            {
                int subIndex = (y >= newHeight) * 2 + (x >= newWidth);
                int newX = x % newWidth;
                int newY = y % newHeight;
                subImages[subIndex].data[newY * newWidth + newX] = im.data[y * im.width + x];
            }
        }

        // Recursive calls
        for (int i = 0; i < 4; i++)
        {
            divideNConquer(subImages[i], threshold, res);
            free(subImages[i].data);
        }
    }
    else
    {
        // Store the result into `res`
        memcpy(res->data, im.data, im.width * im.height * sizeof(uint8_t));
        normalizeImage(res);
    }
}


// Updated `main()` function to store the result
int main() 
{
    // Initialize & prepare data
    inputHandler();

    // Allocate memory for the result image
    res.width = image.width;
    res.height = image.height;
    res.data = (uint8_t*)malloc(image.width * image.height * sizeof(uint8_t));

    divideNConquer(image, 50.0, &res);

    // Save image
    saveJPEG("test/output.jpeg", &res);
    printf("\033[1;32m[INFO]\033[0m Gambar berhasil disimpan sebagai output.jpeg\n");
    // Free allocated memory
    free(image.data);
    free(res.data);
}

