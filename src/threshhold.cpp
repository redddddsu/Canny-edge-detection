#include "../header/threshhold.hpp"
#include <iostream>

using namespace std;

unsigned char* applyThreshhold(unsigned char* image, int width, int height) {
    unsigned char* output = new unsigned char[width * height];    
    float sum = 0;
    float sumAll = 0;

    for (int i = 0; i < width * height; i++) {
        sum += image[i];
        if (image[i] != 0) {
            sumAll++;
        }
    }
    float averageIntensity = sum / sumAll;

    std::cout << averageIntensity * 2.5 << std::endl;

    for (int i = 0; i < width * height; i++) {
        if (image[i] >= averageIntensity * 2.5) {
            output[i] = 255;
        }
        else if (image[i] >= averageIntensity) {
            output[i] = 20;
        }
        else {
            output[i] = 0;
        }
    }
    return output;
}

unsigned char* edgeLinking(unsigned char* image, int width, int height) {
    unsigned char* output = new unsigned char[width * height];
    int nx, ny;
    int pixelIndex;

    memcpy(output, image, width * height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixelIndex = (y * width + x);
            if (image[pixelIndex] == 20) {
                
                for (int edgeY = -1; edgeY <= 1; edgeY++) {
                    for (int edgeX = -1; edgeX <= 1; edgeX++) {
                        nx = edgeX + x;
                        ny = edgeY + y;    

                        if (edgeX == 0 && edgeY == 0) continue;

                        if (nx >= 0 && ny >= 0 && nx < width && ny < height) {
                            if (image[ny * width + nx] == 255) {
                                output[pixelIndex] = 255;
                                break;
                            }
                            else {
                                output[pixelIndex] = 0;
                            }
                        }
                    }
                    if (output[pixelIndex] == 255) {
                        break;
                    }
                }
            }
        }
    }

    return output;
}