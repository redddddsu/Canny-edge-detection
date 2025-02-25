#include "../header/sobel.hpp"
#include <cmath>

using namespace std;

unsigned char* sobelX(unsigned char* image, int width, int height) {
    int sobelX[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2}, 
        {-1, 0, 1}
    };

    int weightedSumX = 0;
    int imageIndex;
    int px, py;

    unsigned char* output = new unsigned char[width * height];


    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            weightedSumX = 0;

            for (int sy = -1; sy <= 1; sy++) {
                for (int sx = -1; sx <= 1; sx++) {
                    py = sy + y;
                    px = sx + x;

                    if (py >= 0 && px >= 0 && py < height && px < width) {
                        imageIndex = (py * width + px);
                        weightedSumX += image[imageIndex] * sobelX[sy + 1][sx + 1];
                        
                    }
                }
            }
            output[y * width + x] = min(255, max(0, weightedSumX));
        }
    }
    return output;

}

unsigned char* sobelY(unsigned char* image, int width, int height) {
    int sobelY[3][3] = {
        {1, 2, 1}, 
        {0, 0, 0}, 
        {-1, -2, -1}
    };

    int weightedSumY = 0;
    int imageIndex;
    int px, py;

    unsigned char* output = new unsigned char[width * height];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            weightedSumY = 0;

            for (int sy = -1; sy <= 1; sy++) {
                for (int sx = -1; sx <= 1; sx++) {
                    py = sy + y;
                    px = sx + x;

                    if (py >= 0 && px >= 0 && py < height && px < width) {
                        imageIndex = (py * width + px);

                        weightedSumY += image[imageIndex] * sobelY[sy + 1][sx + 1];
                    }
                }
            }

            output[y * width + x] = min(255, max(0, weightedSumY));
        }
    }
    return output;

}

unsigned char* computeMagnitude(unsigned char* sobelX, unsigned char* sobelY, int width, int height) {
    unsigned char* output = new unsigned char[width * height];
    int pixelIndex;
    int magnitude;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixelIndex = (y * width + x);
            magnitude = sqrt(sobelX[pixelIndex] * sobelX[pixelIndex] + sobelY[pixelIndex] * sobelY[pixelIndex]);
            magnitude /= 8;

            if (magnitude > 255) {
                magnitude = 255;
            }

            output[pixelIndex] = magnitude;
        }
    }
    return output;
}
