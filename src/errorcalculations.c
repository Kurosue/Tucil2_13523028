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

double calculateVariance(uint8_t *data, int width, int height, int startX, int endX, int startY, int endY) {
    double mean[3] = {0, 0, 0};
    double variance[3] = {0, 0, 0};
    int count = (endX - startX) * (endY - startY);

    if (count == 0) return 0.0;

    // First pass: Compute mean
    for (int y = startY; y < endY; y++) {
        for (int x = startX; x < endX; x++) {
            int idx = (y * width + x) * 3;
            for (int c = 0; c < 3; c++) {
                mean[c] += data[idx + c];
            }
        }
    }

    for (int c = 0; c < 3; c++) {
        mean[c] /= count;
    }

    // Second pass: Compute variance
    for (int y = startY; y < endY; y++) {
        for (int x = startX; x < endX; x++) {
            int idx = (y * width + x) * 3;
            for (int c = 0; c < 3; c++) {
                double diff = data[idx + c] - mean[c];
                variance[c] += diff * diff;
            }
        }
    }

    return (variance[0] + variance[1] + variance[2]) / (3.0 * count);
}
