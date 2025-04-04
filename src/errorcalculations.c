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

double calculateError(uint8_t *data, int width, int height, int startX, int endX, int startY, int endY)
{
    switch (choice) {
        case 1:
            return calculateVariance(data, width, height, startX, endX, startY, endY);
        case 2:
            return calculateMAD(data, width, height, startX, endX, startY, endY);
        case 3:
            return calculateMaxPixelDifferences(data, width, height, startX, endX, startY, endY);
        case 4:
            return calculateEntropy(data, width, height, startX, endX, startY, endY);
        case 5:
            return calculateSSI(data, width, height, startX, endX, startY, endY);
        default:
            printf("\033[1;31m[ERROR]\033[0m Pilihan tidak valid >:(, silahkan coba lagi.\n");
            exit(1);
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

double calculateMAD(uint8_t *data, int width, int height, int startX, int endX, int startY, int endY) {
    double mean[3] = {0, 0, 0};
    double mad[3] = {0, 0, 0};
    int count = (endX - startX) * (endY - startY);

    if (count == 0) return 0.0;

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

    for (int y = startY; y < endY; y++) {
        for (int x = startX; x < endX; x++) {
            int idx = (y * width + x) * 3;
            for (int c = 0; c < 3; c++) {
                mad[c] += fabs(data[idx + c] - mean[c]);
            }
        }
    }

    return (mad[0] + mad[1] + mad[2]) / (3.0 * count);
}

double calculateMaxPixelDifferences(uint8_t *data, int width, int height, int startX, int endX, int startY, int endY)
{
    double maxDiff = 0.0;
    int count = (endX - startX) * (endY - startY);

    if (count == 0) return 0.0;

    for (int y = startY; y < endY; y++) {
        for (int x = startX; x < endX; x++) {
            int idx = (y * width + x) * 3;
            for (int c = 0; c < 3; c++) {
                double diff = fabs(data[idx + c] - data[idx + c]);
                if (diff > maxDiff) {
                    maxDiff = diff;
                }
            }
        }
    }

    return maxDiff / count;
}

double compute_entropy(int *hist, int count) {
    if (count == 0) return 0.0; 

    double entropy = 0.0;
    for (int i = 0; i < 256; i++) {
        if (hist[i] > 0) {
            double p = (double)hist[i] / count;
            entropy -= p * log2(p);
        }
    }
    return entropy;
}

double calculateEntropy(uint8_t *data, int width, int height, 
                        int startX, int endX, int startY, int endY) {
    int histogram[3][256] = {0};
    int count = (endX - startX) * (endY - startY);

    if (count == 0) return 0.0;

    for (int y = startY; y < endY; y++) {
        for (int x = startX; x < endX; x++) {
            int idx = (y * width + x) * 3;
            for (int c = 0; c < 3; c++) {
                histogram[c][data[idx + c]]++;
            }
        }
    }

    double entropy[3] = {0.0, 0.0, 0.0};
    for (int c = 0; c < 3; c++) {
        entropy[c] = compute_entropy(histogram[c], count);
    }

    return (entropy[0] + entropy[1] + entropy[2]) / 3.0;
}

double calculateSSI();
