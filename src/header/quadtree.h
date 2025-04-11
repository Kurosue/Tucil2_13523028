// Header Quadtree
// 13523028 Muhammad Aditya Rahmadeni

#ifndef QUADTREE_H
#define QUADTREE_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "image.h"
#include "errorcalculations.h"

/**
 * @brief Implementasi divide and conquer dari Quadtree
 * @param im Pointer ke struktur Image yang akan diproses
 * @param threshold Nilai threshold untuk pemisahan
 * @param startX Koordinat X awal
 * @param endX Koordinat X akhir
 * @param startY Koordinat Y awal
 * @param endY Koordinat Y akhir
 * @param minSize Ukuran minimum untuk pemisahan
 * @return void
 * @note Fungsi ini akan membagi gambar menjadi sub-gambar berdasarkan threshold dan ukuran minimum
 */
void divideNConquer(Image* im, double threshold, int startX, int endX, int startY, int endY, int minSize);

/**
 * @brief Mengnormalisasi sub blok gambar
 * 
 * @param im Pointer ke struktur Image yang akan diproses
 * @param startX Koordinat X awal
 * @param endX Koordinat X akhir
 * @param startY Koordinat Y awal
 * @param endY Koordinat Y akhir
 * @return void
 * @note Fungsi ini akan mengnormalisasi sub blok gambar berdasarkan nilai minimum dan maksimum
 */
void normalizeSubImage(Image* im, int startX, int endX, int startY, int endY);

#endif 