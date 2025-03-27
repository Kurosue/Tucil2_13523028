#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Ekstrak file gambar menjadi array of uint32_t
 * 
 * @param file Pointer ke file yang ingin diekstrak
 * @return uint32_t* Pointer ke array of uint32_t hasil ekstrak
 */
uint32_t* extractImage(int width, int height, FILE* file);

/**
 * @brief Mendapatkan header dari file gambar spesifik untuk mendapatkan data tinggi dan lebar gambar.
 * 
 * @param width Pointer ke width dari file gambar
 * @param height Pointer ke height dari file gambar
 * @param file Pointer ke file gambar
 */
void getHeader(int *width, int *height, FILE* file);


#endif // IMAGEPROCESSOR_H