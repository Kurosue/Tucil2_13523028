// main.c
// 13523028 - Muhammad Aditya Rahmadeni
#include <stdlib.h>
#include <string.h>
#include "header/imageprocessor.h"
#include "header/errorcalculations.h"

char* absolPath;
uint32_t* image;
int width, height;

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
            getHeader(&width, &height, file);
            image = extractImage(width, height, file);
            break;
        }   
    }

    // [Input] Metode perhitungan error & Threshold
    chooseErrorMethod();

    // [Input] ukuran blok mimi
}
int main()
{
    // Inisialisasi dan persiapan data
    inputHandler();

    // Testing : test input berhsail atau tidak
    printf("Width : %d\n", width);
    printf("Height : %d\n", height);
    printf("Image : %p\n", image);
    printf("Choice : %d\n", choice);
    printf("Threshold : %d\n", threshold);
    printf("MinSize : %d\n", minSize);
}

