// main.c
// 13523028 - Muhammad Aditya Rahmadeni

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "header/quadtree.h"
#include <time.h>

char* absolPath;
Image image;
Image res;

void inputHandler()
{
    // [Input] Absolut Path dari file
    while(true)
    {
        printf("\033[1;33m[Input]\033[0m Masukkan nama file gambar yang ingin diproses ( \033[1;33mCATATAN : PASTIKAN FILE ADA DALAM FOLDER TEST ATAU PATH LENGKAP FILE ADA\033[0m ) \n> ");
        char* fileName = (char*)malloc(300 * sizeof(char));
        absolPath = (char*)malloc(500 * sizeof(char));

        strcpy(absolPath, "./test/");
        scanf("%300s", fileName);
        strcat(absolPath, fileName);
        
        FILE* file = fopen(absolPath, "r");
        if(file == NULL)
        {
            file = fopen(fileName, "r");
            if(file == NULL)
            {
                printf("\033[1;31m[ERROR]\033[0m File pada \033[1;34m%s\033[0m ataupun \033[1;34m%s\033[0m tidak ditemukan, silahkan coba lagi.\n", fileName, absolPath);
                continue;
            }
            else
            {
                printf("\033[1;32m[Success]\033[0m File ditemukan !\n\n");
                extractImage(file, &image);
                break;
            }
        }
        else
        {
            printf("\n\033[1;32m[Success]\033[0m File ditemukan !\n\n");
            extractImage(file, &image);
            break;
        } 
    }
    // [Input] Metode perhitungan error & Threshold
    chooseErrorMethod();
}



void processImage(Image* im) {
    printf("\033[1;32m[INFO]\033[0m Gambar akan mulai diproses...\n\n");
    
    // Timer Mulai
    clock_t start = clock();
    divideNConquer(im, threshold, 0, im->width, 0, im->height, minSize, 0);
    clock_t end = clock();
    // Timer Selesai

    double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\033[1;32m[INFO]\033[0m Ukuran Original Gambar: \033[1;34m%d\033[0m\n", im->height * im->width * 3);
    printf("\033[1;32m[INFO]\033[0m Kedalaman pohon: \033[1;34m%d\033[0m\n", nodeCount * 19);
    printf("\033[1;32m[INFO]\033[0m Kompresi: \033[1;34m%.2f\033[0m\n", 100.0 * (1.0 - (double)(nodeCount * 19)) / (im->height * im->width * 3));
    printf("\033[1;32m[INFO]\033[0m Gambar berhasil diproses dalam waktu \033[1;34m%.2f detik\033[0m\n", timeTaken);
    printf("\033[1;32m[INFO]\033[0m Kedalaman pohon: \033[1;34m%d\033[0m\n", maxDepth);
    printf("\033[1;32m[INFO]\033[0m Banyak simpul pada pohon: \033[1;34m%d\033[0m\n", nodeCount);
}

int main() 
{
    inputHandler();

    // Copy image ke res untuk membandingkan nanti
    res.width = image.width;
    res.height = image.height;
    res.data = (uint8_t*)malloc(res.width * res.height * 3);
    memcpy(res.data, image.data, res.width * res.height * 3);
    
    // Proses gambar
    processImage(&res);

    char fullpath[300] = "./test/";
    saveImage(fullpath, &res);

    // Bersih bersih cihuy
    free(image.data);
    free(res.data);
}

