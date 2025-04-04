// Implementasi dari Image
// 13523028 - Muhammad Aditya Rahmadeni

#include "header/image.h"

uint16_t read16(FILE* file) {
    uint8_t bytes[2];
    fread(bytes, 1, 2, file);

    return (bytes[0] << 8) | bytes[1];
}

uint32_t read32(FILE* file) {
    uint8_t bytes[4];
    fread(bytes, 1, 4, file);
    return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}

ImageFormat detectImageFormat(FILE* file) {
    uint8_t signature[8];
    fread(signature, 1, 8, file);
    rewind(file);

    if (signature[0] == 0xFF && signature[1] == 0xD8) {
        return IMAGE_JPEG;
    } else if (signature[0] == 0x89 && signature[1] == 0x50 && signature[2] == 0x4E && signature[3] == 0x47) {
        return IMAGE_PNG;   
    } else if (signature[0] == 0x42 && signature[1] == 0x4D) {
        return IMAGE_BMP;
    }
    return IMAGE_UNKNOWN;
}

void extractJPEG(FILE* file, Image* im) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, file);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);
    
    im->width = (uint32_t)cinfo.output_width;
    im->height = (uint32_t)cinfo.output_height;
    int channels = 3;
    
    printf("\033[1;32m[INFO]\033[0m Dimensi Gambar JPEG: \033[1;34m%d x %d\033[0m\n", im->width, im->height);
      // Store channels
    im->data = (uint8_t*)malloc(im->width * im->height * channels);
    uint8_t* row_pointer[1];
    
    while (cinfo.output_scanline < cinfo.output_height) {
        row_pointer[0] = im->data + cinfo.output_scanline * im->width * channels;
        jpeg_read_scanlines(&cinfo, row_pointer, 1);
    }
    
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(file);
    
    printf("\033[1;32m[INFO]\033[0m Gambar JPEG berhasil diekstrak\n\n");
}

void saveJPEG(char* path, Image* im) {
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    // Minta input nama file
    printf("\033[1;33m[Input]\033[0m Masukkan nama file untuk menyimpan gambar JPEG (DENGAN ekstensi): ");
    char filename[100];
    scanf("%99s", filename); // Limit input to avoid overflow
    snprintf(path, 256, "%s%s", path, filename); // Safely concatenate strings
    printf("\n\n\033[1;32m[INFO]\033[0m Menyimpan gambar JPEG sebagai %s\n", path);
    
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("\033[1;31m[ERROR]\033[0m Gagal menyimpan gambar JPEG\n");
        return;
    }
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, file);
    
    cinfo.image_width = im->width;
    cinfo.image_height = im->height;
    if (im->data == NULL) {
        printf("\033[1;31m[ERROR]\033[0m Data gambar tidak valid\n");
        fclose(file);
        return;
    }
    cinfo.input_components = 3;  // Assuming RGB format
    cinfo.in_color_space = JCS_RGB;
    int channels = 3;
    
    jpeg_set_defaults(&cinfo);

    // Set quality to 100 to avoid compression
    jpeg_set_quality(&cinfo, 100, TRUE);

    jpeg_start_compress(&cinfo, TRUE);
    
    uint8_t* row_pointer[1];
    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = &im->data[cinfo.next_scanline * im->width * channels];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }
    
    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(file);
    
    printf("\033[1;32m[INFO]\033[0m Gambar JPEG berhasil disimpan sebagai %s\n\n", filename);
}

void paethFilter(uint8_t* scanline, uint8_t* prevScanline, int stride, int filterType) {
    for (int x = 0; x < stride; x++) {
        uint8_t a = (x >= 4) ? scanline[x - 4] : 0;
        uint8_t b = (prevScanline) ? prevScanline[x] : 0;
        uint8_t c = (prevScanline && x >= 4) ? prevScanline[x - 4] : 0;
        
        int p = a + b - c;
        int pa = abs(p - a);
        int pb = abs(p - b);
        int pc = abs(p - c);
        
        if (pa <= pb && pa <= pc) scanline[x] += a;
        else if (pb <= pc) scanline[x] += b;
        else scanline[x] += c;
    }
}

void extractPNG(FILE* file, Image* im) {
    fseek(file, 8, SEEK_SET);
    char chunkType[5];
    uint32_t chunkSize;
    uint8_t* compressedData = NULL;
    size_t compressedSize = 0;

    while (!feof(file)) {
        chunkSize = read32(file);
        fread(chunkType, 1, 4, file);
        chunkType[4] = '\0';

        if (strcmp(chunkType, "IHDR") == 0) {
            im->width = (uint8_t)read32(file);
            im->height = (uint8_t)read32(file);
            fseek(file, 5, SEEK_CUR);
        } else if (strcmp(chunkType, "IDAT") == 0) {
            compressedData = (uint8_t*)realloc(compressedData, compressedSize + chunkSize);
            fread(compressedData + compressedSize, 1, chunkSize, file);
            compressedSize += chunkSize;
        } else if (strcmp(chunkType, "IEND") == 0) {
            break;
        } else {
            fseek(file, chunkSize, SEEK_CUR);
        }
        fseek(file, 4, SEEK_CUR);
    }
    
    uint8_t* decompressedData = (uint8_t*)malloc(im->width * im->height * 3 + im->height);
    uLongf decompressedSize = im->width * im->height * 3 + im->height;
    if (uncompress(decompressedData, &decompressedSize, compressedData, compressedSize) != Z_OK) {
        printf("\033[1;31m[ERROR]\033[0m Dekompresi PNG Gagal: Data mungkin rusak atau format tidak didukung\n");
        free(compressedData);
        free(decompressedData);
        return;
    }
    
    im->data = (uint8_t*)malloc(im->width * im->height * 3); // Allocate memory for RGB data
    int stride = im->width * 3;
    uint8_t* prevScanline = NULL;
    for (int y = 0; y < im->height; y++) {
        int filterType = decompressedData[y * (stride + 1)];
        uint8_t* scanline = &decompressedData[y * (stride + 1) + 1];
        if (filterType == 4) {
            paethFilter(scanline, prevScanline, stride, filterType);
        }
        for (int x = 0; x < im->width; x++) {
            uint8_t r = scanline[x * 3];
            uint8_t g = scanline[x * 3 + 1];
            uint8_t b = scanline[x * 3 + 2];
            im->data[(y * im->width + x) * 3] = r;
            im->data[(y * im->width + x) * 3 + 1] = g;
            im->data[(y * im->width + x) * 3 + 2] = b;
        }
        prevScanline = scanline;
    }
    
    free(compressedData);
    free(decompressedData);
}

void extractBMP(FILE* file, struct Image* im) {
    BMPHeader header;
    BMPInfoHeader info;
    
    fread(&header, sizeof(BMPHeader), 1, file);
    fread(&info, sizeof(BMPInfoHeader), 1, file);
    
    if (header.type != 0x4D42) {
        printf("Not a valid BMP file!\n");
        return;
    }
    
    im->width = (uint8_t)info.width;
    im->height = (uint8_t)abs(info.height);
    
    fseek(file, header.offset, SEEK_SET);
    
    int rowSize = ((info.bitCount * im->width + 31) / 32) * 4;
    uint8_t* bmpData = (uint8_t*)malloc(rowSize * im->height);
    fread(bmpData, rowSize, im->height, file);
    
    im->data = (uint8_t*)malloc(im->width * im->height * 3); // Allocate memory for RGB data
    
    for (int y = 0; y < im->height; y++) {
        for (int x = 0; x < im->width; x++) {
            int index = y * rowSize + x * 3;
            uint8_t b = bmpData[index];
            uint8_t g = bmpData[index + 1];
            uint8_t r = bmpData[index + 2];
            im->data[(y * im->width + x) * 3] = r;
            im->data[(y * im->width + x) * 3 + 1] = g;
            im->data[(y * im->width + x) * 3 + 2] = b;
        }
    }
    
    free(bmpData);
}

void extractImage(FILE* file, struct Image* im) {
    ImageFormat format = detectImageFormat(file);
    
    switch (format) {
        case IMAGE_JPEG:
            extractJPEG(file, im);
            break;
        case IMAGE_PNG:
            extractPNG(file, im);
            break;
        case IMAGE_BMP:
            extractBMP(file, im);
            break;
        default:
            printf("\033[1;31m[ERROR]\033[0m File bukan bertipe gambar (.JPG/.JPEG, .PNG, .BMP)\n");
            break;
    }
}

void normalizeSubImage(Image* im, int startX, int endX, int startY, int endY) {
    uint8_t minVal[3] = {255, 255, 255}, maxVal[3] = {0, 0, 0};

    // First pass: Get min/max per channel
    for (int y = startY; y < endY; y++) {
        int baseIdx = (y * im->width + startX) * 3;  // Move row-wise
        for (int x = startX; x < endX; x++, baseIdx += 3) {
            for (int c = 0; c < 3; c++) {
                uint8_t val = im->data[baseIdx + c];
                if (val < minVal[c]) minVal[c] = val;
                if (val > maxVal[c]) maxVal[c] = val;
            }
        }
    }

    // If all values are the same, no need to normalize
    if (minVal[0] == maxVal[0] && minVal[1] == maxVal[1] && minVal[2] == maxVal[2]) return;

    // Second pass: Apply normalization
    for (int c = 0; c < 3; c++) {
        float scale = (maxVal[c] == minVal[c]) ? 1.0f : 255.0f / (maxVal[c] - minVal[c]);
        for (int y = startY; y < endY; y++) {
            int baseIdx = (y * im->width + startX) * 3;
            for (int x = startX; x < endX; x++, baseIdx += 3) {
                im->data[baseIdx + c] = (uint8_t)((im->data[baseIdx + c] - minVal[c]) * scale);
            }
        }
    }
}


void divideNConquer(Image* im, double threshold, int startX, int endX, int startY, int endY, int minSize) {
    double error = calculateVariance(im->data, im->width, im->height, startX, endX, startY, endY);
    if ((endX - startX) <= minSize || (endY - startY) <= minSize || error <= threshold) {
        normalizeSubImage(im, startX, endX, startY, endY);
        return;
    }

    int midX = (startX + endX) / 2;
    int midY = (startY + endY) / 2;

    divideNConquer(im, threshold, startX, midX, startY, midY, minSize); 
    divideNConquer(im, threshold, midX+1, endX, startY, midY, minSize); 
    divideNConquer(im, threshold, startX, midX, midY+1, endY, minSize); 
    divideNConquer(im, threshold, midX+1, endX, midY+1, endY, minSize); 
}