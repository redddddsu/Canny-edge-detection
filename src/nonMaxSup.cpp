#include "../header/nonMaxSup.hpp"
#include <cmath>

using namespace std;

unsigned char* computeGradientDirection(unsigned char* sobel, int width, int height) {
    int pixelIndex;
    float angle;

    unsigned char* output = new unsigned char[width * height];


    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixelIndex = (y * width + x);   
            angle = atan2(sobel[pixelIndex], sobel[pixelIndex]) * 180 / M_PI;
            
            if (angle < 0) {
                angle += 180;
            } 


            output[pixelIndex] = angle;
        }
    }
    return output;
}

unsigned char* nonMaxSuppression(unsigned char* image, int width, int height) {
    int pixelIndex;
    int maxIntensity;

    unsigned char *output = new unsigned char[width * height];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixelIndex = (y * width + x);
            if (image[pixelIndex] < 40) {
                image[pixelIndex] = 0;
            }
            output[pixelIndex] = image[pixelIndex];
        } 
    }
    return output;
}