#include "../header/nonMaxSup.hpp"

using namespace std;

unsigned char* computeGradientDirection(unsigned char* sobelX, unsigned char* sobelY, int width, int height) {
    /*
    Calculate the direction of each pixel by
    arctan(Y/X)
    * 180 / M_PI just converts from radian to degree
    */
    float angle;
    unsigned char* output = new unsigned char[width * height];

    //Same idea, don't need to get the neigbhoring pixels
    for (int i = 0; i < height * width; i++) {
        angle = atan2(sobelY[i], sobelX[i]) * 180 / M_PI;
            
        // Since we don't want arctan to go past 180 degrees (no negative number) we add the 180 
        if (angle < 0) {
            angle += 180;
        } 

        output[i] = angle;
    }
    return output;
}

unsigned char* nonMaxSuppression(unsigned char* image, unsigned char* direction, int width, int height) {
    /*
    We get the angle/direction of pixel and use that to determine which neighbor to check
    0/180, 45, 90, 135
    0/180: left, right
    45: top-right, bottom-left
    90: top, bottom
    135: top-left, bottom-right
    */
    int imageIndex;
    float angle;
    int left, right;

    unsigned char *output = new unsigned char[width * height];

    //Starting at [1][1] and ending at [y-1][x-1] we are missing some neigbhors at [0][x] and [y][0]
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            imageIndex = (y * width + x);
            angle = direction[imageIndex];
            
            /*
            We don't use the exact degrees because well it's going to be really rare for pixel to have those exact degree
            Instead we have a range and use 22.5 (half of 45) as our spread
            */

            // We check 0 and 180 because both are considered left and right or "fully horizontal"
            if ((0 <= angle < 22.5) || 157.5 <= angle < 180) {
                right = image[imageIndex + 1];
                left = image[imageIndex - 1];
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

            // This just compares the neighbors to see which one should remain
            if (image[imageIndex] >= right && image[imageIndex] >= left) {
                output[imageIndex] = image[imageIndex];
            }
            else {
                output[imageIndex] = 0;
            }

        }
    }

    //This is just border control, removing pixels from the border of the image (optional)
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == 0 || y == 0 || x == width - 1 || y == height - 1) {
                output[y * width + x] = 0;
            }
        }
    }

    return output;
}