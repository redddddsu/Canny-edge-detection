#include "../header/gaussian.hpp"


void generateGaussian(float kernel[KERNEL_SIZE][KERNEL_SIZE], int kSize, float sigma) {
    //Gaussian kernel needs to start from the center and move outwards
    //Where the center is the largest number and it get progressively smaller as it move outwards

    int center = kSize / 2;
    float value;
    float sum = 0.0f;

    for (int y = -center; y <= center; y++) {
        for (int x = -center; x <= center; x++) {
            value = expf(-(x * x + y * y) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
            kernel[y + center][x + center] = value;
            sum += value;
        }
    }

    //Normalize so the values doesnt get too large
    for (int y = -center; y <= center; y++) {
        for (int x = -center; x <= center; x++) {
            kernel[y + center][x + center] /= sum;
        }
    }
}

unsigned char* applyGaussianKernel(float kernel[KERNEL_SIZE][KERNEL_SIZE], int kSize, unsigned char *image, int width, int height) {
    int center = kSize / 2;
    int weightedSum = 0;
    int py, px;
    int imageIndex, outputIndex;
    unsigned char *output = new unsigned char[width * height];


    //We need to first check the boundaries of the pixels around the original image
    //Can do this by getting the location pixel of the original image, then adding the position of the kernel to see if 
    //It goes out of bounds

    //Literate through every pixel
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            
            weightedSum = 0;

            //Literate through the kernel
            for (int ky = -center; ky <= center; ky++) {
                for (int kx = -center; kx <= center; kx++) {
                    px = x + kx;
                    py = y + ky;

                    //boundary check
                    if (px >= 0 && py >= 0 && px < width && py < height) {

                        //get the image pixel index
                        imageIndex = (py * width + px);

                        //convulotion
                        weightedSum += image[imageIndex] * kernel[ky + center][kx + center];    
                    }


                }
            }

            outputIndex = (y * width + x);

            if (weightedSum > 255) {
                weightedSum = 225;
            }

            output[outputIndex] = weightedSum;
        }
    }

    return output;
}