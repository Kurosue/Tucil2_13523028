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

extern ImageFormat format;

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

// untuk save png file
extern uint32_t crc_table[256];
extern int crc_table_computed;

/**
 * @brief Membaca 16 bit dari file
 * 
 * @param file Pointer ke file yang ingin dibaca
 * @return uint16_t Nilai 16 bit yang dibaca dari file
 */
void extractImage(FILE* file, Image* im);

/**
 * @brief Menyimpan gambar ke file
 * 
 * @param path Path file untuk menyimpan gambar
 * @param im Pointer ke struktur Image yang akan disimpan
 * @return void
 * @note Fungsi ini akan menyimpan gambar ke file dengan format yang sesuai
 * @note Format yang didukung: JPEG, PNG, BMP
 */
void saveImage(char* path, Image *im);

#endif // IMAGE_H
