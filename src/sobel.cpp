#include "../header/sobel.hpp"
#include <cmath>

using namespace std;

unsigned char* sobelX(unsigned char* image, int width, int height) {
    /*
    Similar to the gaussian blur but the kernel is always set at 3x3
    */    
    int sobelX[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2}, 
        {-1, 0, 1}
    };

    int weightedSumX = 0;
    int neighborIndex;
    int px, py;

    unsigned char* output = new unsigned char[width * height];

    //Since its always 3x3 we can start at [1][1] and end at [y-1][x-1] and ignore boundary checks
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {

            weightedSumX = 0;

            for (int sy = -1; sy <= 1; sy++) {
                for (int sx = -1; sx <= 1; sx++) {
                    py = sy + y;
                    px = sx + x;
                    neighborIndex = (py * width + px);
                    weightedSumX += image[neighborIndex] * sobelX[sy + 1][sx + 1];
                }
            }
            //Since some number can be negative or go above 255, this just a check to not go over/under
            output[y * width + x] = min(255, max(0, weightedSumX));
        }
    }
    return output;

}

unsigned char* sobelY(unsigned char* image, int width, int height) {

    /*
    Same logic as sobel X
    */
    int sobelY[3][3] = {
        {1, 2, 1}, 
        {0, 0, 0}, 
        {-1, -2, -1}
    };

    int weightedSumY = 0;
    int neigbhorIndex;
    int px, py;

    unsigned char* output = new unsigned char[width * height];

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {

            weightedSumY = 0;

            for (int sy = -1; sy <= 1; sy++) {
                for (int sx = -1; sx <= 1; sx++) {
                    py = sy + y;
                    px = sx + x;
                    neigbhorIndex = (py * width + px);
                    weightedSumY += image[neigbhorIndex] * sobelY[sy + 1][sx + 1];
                }
            }
            output[y * width + x] = min(255, max(0, weightedSumY));
        }
    }
    return output;
}

unsigned char* computeMagnitude(unsigned char* sobelX, unsigned char* sobelY, int width, int height) {
    /*
    Now we just apply both sobel X and Y to the image by
    sqrt(X^2 + Y^2)/8
    */
    unsigned char* output = new unsigned char[width * height];
    int magnitude;

    /*
    Only use 1 for loop here because we can don't need to calculate the index of it's neighbor
    and just iterate through the whole image
    */ 
    for (int i = 0; i < width * height; i++) {
        magnitude = sqrt(sobelX[i] * sobelX[i] + sobelY[i] * sobelY[i]);
        magnitude /= 8;

        if (magnitude > 255) {
            magnitude = 255;
        }
        output[i] = magnitude;
    }
    return output;
}
