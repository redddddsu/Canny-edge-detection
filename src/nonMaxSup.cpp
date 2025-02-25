#include "../header/nonMaxSup.hpp"
#include <cmath>

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

unsigned char* nonMaxSuppression(unsigned char* direction, int width, int height) {
    int pixelIndex;
    int maxIntensity;

    unsigned char *output = new unsigned char[width * height];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixelIndex = (y * width + x);
            if (direction[pixelIndex] < 40) {
                direction[pixelIndex] = 0;
            }
            output[pixelIndex] = direction[pixelIndex];
        } 
    }
    return output;
}