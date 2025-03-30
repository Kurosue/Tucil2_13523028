#include "header/errorcalculations.h"

int choice;
int threshold;
int minSize;

void chooseErrorMethod()
{
    while(true)
    {
        printf("Pilih metode perhitungan error : \n");
        printf("1. Metode Variance\n");
        printf("2. Metode Mean Absoulte Deviation (MAD)\n");
        printf("3. Metode Max Pixel Differences\n");
        printf("4. Metode Entropy\n");
        printf("5. Metode Structural Similarity Index (SSI) [ NOTE : TBA ]]\n");
        printf("> ");
        scanf("%d", &choice);
        if(choice < 1 || choice > 5)
        {
            printf("\033[1;31m[ERROR]\033[0m Pilihan tidak valid >:(, silahkan coba lagi.\n");
            continue;
        }
        else
        {
            printf("Masukkan Threshold : ");
            scanf("%d", &threshold);
            printf("Masukkan ukuran blok minimum : ");
            scanf("%d", &minSize);
            break;
        }
    }
}

double calculateVariance(uint8_t* data, int width, int height)
{
    uint64_t sumSqR = 0, sumSqG = 0, sumSqB = 0;
    uint64_t sumR = 0, sumG = 0, sumB = 0;
    int size = width * height;

    for (int i = 0; i < size; i++) {
        uint8_t r = data[i * 3];
        uint8_t g = data[i * 3 + 1];
        uint8_t b = data[i * 3 + 2];

        sumR += r;
        sumG += g;
        sumB += b;
        sumSqR += (uint64_t)r * r;
        sumSqG += (uint64_t)g * g;
        sumSqB += (uint64_t)b * b;
    }

    double meanR = (double)sumR / size;
    double meanG = (double)sumG / size;
    double meanB = (double)sumB / size;

    double varR = (double)sumSqR / size - meanR * meanR;
    double varG = (double)sumSqG / size - meanG * meanG;
    double varB = (double)sumSqB / size - meanB * meanB;

    return (varR + varG + varB) / 3.0;
}