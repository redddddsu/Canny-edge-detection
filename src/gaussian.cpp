#include "../header/gaussian.hpp"


void generateGaussian(float kernel[KERNEL_SIZE][KERNEL_SIZE], int kSize, float sigma) {
    /*
    The gaussian kernel is generated where the largest value is in the center
    As we move farther from the center, the values becomes smaller and smaller

    In a matrix, we can think of [0][0] as the center
    The right and left of the center would be [0][-1] and [0][1]
    */
    int center = kSize / 2;
    float value;

    for (int y = -center; y <= center; y++) {
        for (int x = -center; x <= center; x++) {
            value = expf(-(x * x + y * y) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
            kernel[y + center][x + center] = value;
        }
    }
}

unsigned char* applyGaussianKernel(float kernel[KERNEL_SIZE][KERNEL_SIZE], int kSize, unsigned char *image, int width, int height) {
    /*
    We use convolution to blur the image
    First apply the gaussian kernel
    Then find the sum of the neigbhors around it
    */
    int center = kSize / 2;
    int weightedSum = 0;
    int py, px;
    int neigbhorIndex;
    unsigned char *output = new unsigned char[width * height];

    //Literate through every pixel
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            
            weightedSum = 0;

            /*
            With the selected pixel, we are looking for the neighbors around it depending
            on the size of the gaussian kernel
            */
            for (int ky = -center; ky <= center; ky++) {
                for (int kx = -center; kx <= center; kx++) {
                    px = x + kx;
                    py = y + ky;

                    //Boundary check
                    if (px >= 0 && py >= 0 && px < width && py < height) {

                        //This would get the index of the neighbor of the selected pixel
                        neigbhorIndex = (py * width + px);

                        //Convulotion
                        weightedSum += image[neigbhorIndex] * kernel[ky + center][kx + center];    
                    }
                }
            }

            //Out of bounds check
            if (weightedSum > 255) {
                weightedSum = 225;
            }

            output[y * width + x] = weightedSum;
        }
    }

    return output;
}