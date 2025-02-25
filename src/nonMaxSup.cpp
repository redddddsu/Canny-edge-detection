#include "../header/nonMaxSup.hpp"

using namespace std;

unsigned char* computeGradientDirection(unsigned char* sobelX, unsigned char* sobelY, int width, int height) {
    int pixelIndex;
    float angle;

    unsigned char* output = new unsigned char[width * height];


    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixelIndex = (y * width + x);   
            angle = atan2(sobelY[pixelIndex], sobelX[pixelIndex]) * 180 / M_PI;
            
            if (angle < 0) {
                angle += 180;
            } 


            output[pixelIndex] = angle;
        }
    }
    return output;
}

unsigned char* nonMaxSuppression(unsigned char* image, unsigned char* direction, int width, int height) {
    int pixelIndex;
    float angle;
    int left, right;

    unsigned char *output = new unsigned char[width * height];

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            pixelIndex = (y * width + x);
            angle = direction[pixelIndex];
            
            if ((0 <= angle < 22.5) || 157.5 <= angle < 180) {
                right = image[pixelIndex + 1];
                left = image[pixelIndex - 1];
            }
            else if (22.5 <= angle < 67.5) {
                right = image[(y + 1) * width + (x - 1)];
                left = image[(y - 1) * width + (x + 1)];
            }
            else if (67.5 <= angle < 112.5) {
                right = image[(y + 1) * width + x];
                left = image[(y - 1) * width + x];
            }
            else if (112.5 <= angle < 157.5) {
                right = image[(y + 1) * width + (x + 1)];
                left = image[(y - 1) * width + (x - 1)];
            }

            if (image[pixelIndex] >= right && image[pixelIndex] >= left) {
                output[pixelIndex] = image[pixelIndex];
            }
            else {
                output[pixelIndex] = 0;
            }

        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == 0 || y == 0 || x == width - 1 || y == height - 1) {
                output[y * width + x] = 0;
            }
        }
    }

    return output;
}