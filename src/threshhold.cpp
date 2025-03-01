#include "../header/threshhold.hpp"
#include <iostream>

unsigned char* applyThreshhold(unsigned char* image, int width, int height) {
    /*
    We first calculate the average intensity
    Since a lot of the pixel are zero
    n = pixel > 0
    */
    unsigned char* output = new unsigned char[width * height];    
    float sum = 0;
    float n = 0;

    for (int i = 0; i < width * height; i++) {
        sum += image[i];
        if (image[i] != 0) {
            n++;
        }
    }
    float averageIntensity = sum / n;

    /*
    Anything above average * 2.5 are strong pixel (255)
    Anything above average is weak (20)
    Everything else = 0
    */
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
    /*
    This is pretty much the same things with applying kernel but instead we are checking
    if the selected pixel neighbor is a strong pixel (255)
    */
    unsigned char* output = new unsigned char[width * height];
    int nx, ny;
    int imageIndex;

    memcpy(output, image, width * height);

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            imageIndex = (y * width + x);
            if (image[imageIndex] == 20) {
                
                for (int edgeY = -1; edgeY <= 1; edgeY++) {
                    for (int edgeX = -1; edgeX <= 1; edgeX++) {
                        nx = edgeX + x;
                        ny = edgeY + y;    
                        
                        //We don't want to check the selected pixel with itself
                        if (edgeX == 0 && edgeY == 0) continue;

                        //If ANY of the neighbor is a strong pixel, we can just break the loop and can check the next pixel
                        if (image[ny * width + nx] == 255) {
                            output[imageIndex] = 255;
                            break;
                        }
                        else {
                            output[imageIndex] = 0;
                        }
                    }
                    //Same thing, if any neighbor is strong, can break the loop and can check the next pixel
                    if (output[imageIndex] == 255) {
                        break;
                    }
                }
            }
        }
    }
    return output;
}