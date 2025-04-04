#ifndef ERRORCALCULATIONS_H
#define ERRORCALCULATIONS_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>     
#include <math.h>

extern int choice;
extern int threshold;
extern int minSize;

/** 
 * @brief Pilih metode perhitungan error dari 1 - 5
 */ 
void chooseErrorMethod();

/**
* @brief Menghitung Variance dari blok data gambar
* @param data Pointer ke data gambar
* @param width Lebar gambar
* @param height Tinggi gambar
* @param startX Koordinat X awal blok
* @param endX Koordinat X akhir blok
* @param startY Koordinat Y awal blok
* @param endY Koordinat Y akhir blok
* @return Variance dari blok data gambar
*/
double calculateVariance(uint8_t *data, int width, int height, int startX, int endX, int startY, int endY);


double calculateMAD();
double calculateMaxPixelDifferences();
double calculateEntropy();
double calculateSSI();

#endif // ERRORCALCULATIONS_H