// main.c
// 13523028 - Muhammad Aditya Rahmadeni
#include <stdlib.h>
#include <string.h>
#include "header/imageprocessor.h"

char* absolPath = "./";
uint32_t* image;
int width, height;

int main()
{
    // Inisialisasi dan persiapan data
    inputHandler();

}

void inputHandler()
{
    // [Input] Absolut Path dari file
    while(true)
    {
        printf("Masukkan nama file gambar yang ingin diproses dan ada di dalam folder test: ");
        char* fileName = (char*)malloc(100 * sizeof(char));
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
            printf("File ditemukan !");
            getHeader(&width, &height, file);
            image = extractImage(file);
            break;
        }   
    }
}
