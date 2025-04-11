#ifndef ERRORCALCULATIONS_H
#define ERRORCALCULATIONS_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>     
#include <math.h>
#include <stdlib.h>

extern int choice;
extern int threshold;
extern int minSize;

/** 
 * @brief Pilih metode perhitungan error dari 1 - 5
 */ 
void chooseErrorMethod();

/**
* @brief Menghitung Eror dari blok gambar berdasarkan metode yang dipilih
* @param data Pointer ke data gambar
* @param width Lebar gambar
* @param height Tinggi gambar
* @param startX Koordinat X awal blok
* @param endX Koordinat X akhir blok
* @param startY Koordinat Y awal blok
* @param endY Koordinat Y akhir blok
* @return Error value dari blok data gambar
*/
double calculateError(uint8_t *data, int width, int height, int startX, int endX, int startY, int endY);

#endif // ERRORCALCULATIONS_H