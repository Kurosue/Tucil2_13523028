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