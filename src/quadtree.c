#include "header/quadtree.h"

void normalizeSubImage(Image* im, int startX, int endX, int startY, int endY) {
    uint64_t sum[3] = {0, 0, 0};
    int total = 0;

    for (int y = startY; y < endY; y++) {
        for (int x = startX; x < endX; x++) {
            int idx = (y * im->width + x) * 3;
            for (int c = 0; c < 3; c++) {
                sum[c] += im->data[idx + c];
            }
            total++;
        }
    }

    uint8_t avg[3] = {
        sum[0] / total,
        sum[1] / total,
        sum[2] / total
    };

    for (int y = startY; y < endY; y++) {
        for (int x = startX; x < endX; x++) {
            int idx = (y * im->width + x) * 3;
            for (int c = 0; c < 3; c++) {
                im->data[idx + c] = avg[c];
            }
        }
    }
}


void divideNConquer(Image* im, double threshold, int startX, int endX, int startY, int endY, int minSize) {
    // Hitung eror sesuai metoed yang sudah dipilih
    double error = calculateError(im->data, im->width, im->height, startX, endX, startY, endY);

    // Cek apakah ukuran sesuai batas yang ditentukan atau eror masih diatas batasan threshold 
    if ((endX - startX) <= minSize || (endY - startY) <= minSize || error <= threshold) {
        // Jika iya maka normalisasi sub blok gambar
        normalizeSubImage(im, startX, endX, startY, endY);
        return;
    }


    int midX = (startX + endX) / 2;
    int midY = (startY + endY) / 2;

    // Buat "Anak" 
    divideNConquer(im, threshold, startX, midX, startY, midY, minSize); 
    divideNConquer(im, threshold, midX+1, endX, startY, midY, minSize); 
    divideNConquer(im, threshold, startX, midX, midY+1, endY, minSize); 
    divideNConquer(im, threshold, midX+1, endX, midY+1, endY, minSize); 
}