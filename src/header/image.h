// Header image
// !3523028 - Muhammad Aditya Rahmadeni

#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>
#include <string.h>
#include <math.h>
#include <jpeglib.h>

// enum untuk mempermudah pengelompokan tipe file
typedef enum {
    IMAGE_UNKNOWN,
    IMAGE_JPEG,
    IMAGE_PNG,
    IMAGE_BMP
} ImageFormat;

// Strcut dari image yang akan diproses
typedef struct Image {
    uint8_t* data;
    int width;
    int height;
} Image;


#pragma pack(push, 1)
typedef struct {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
} BMPHeader;

typedef struct {
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitCount;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
} BMPInfoHeader;
#pragma pack(pop)

/**
 * @brief Membaca 16 bit dari file
 * 
 * @param file Pointer ke file yang ingin dibaca
 * @return uint16_t Nilai 16 bit yang dibaca dari file
 */
void extractImage(FILE* file, Image* im);

/**
 * @brief extract gambar dari file BMP
 * 
 * @param file Pointer ke file yang ingin diperiksa
 * @param im Pointer ke struktur Image yang akan diisi
 * @return ImageFormat Format gambar yang terdeteksi
 */
void extractBMP(FILE* file,Image* im);

/**
 * @brief extract gambar dari file JPEG
 * 
 * @param file Pointer ke file yang ingin diperiksa
 * @param im Pointer ke struktur Image yang akan diisi
 */
void extractJPEG(FILE* file,Image* im);

/**
 * @brief extract gambar dari file PNG
 * 
 * @param file Pointer ke file yang ingin diperiksa
 * @param im Pointer ke struktur Image yang akan diisi
 */
void extractPNG(FILE* file, Image* im);

/**
 * @brief Menyimpan gambar ke file JPEG
 * 
 * @param path Nama file untuk menyimpan gambar
 * @param im Pointer ke struktur Image yang akan disimpan
 */
void saveJPEG(char* path, Image* im);

/**
 * @brief Mengambil format gambar dari file
 * 
 * @param file Pointer ke file yang ingin diperiksa
 * @return ImageFormat Format gambar yang terdeteksi
 */
ImageFormat detectImageFormat(FILE* file);

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

#endif // IMAGE_H
