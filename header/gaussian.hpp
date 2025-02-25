#ifndef GAUSSIAN_HPP
#define GAUSSIAN_HPP
#define KERNEL_SIZE 5

#include <math.h>

void generateGaussian(float kernel[KERNEL_SIZE][KERNEL_SIZE], int kSize, float sigma);
unsigned char* applyGaussianKernel(float kernel[KERNEL_SIZE][KERNEL_SIZE], int kSize, unsigned char *image, int width, int height);

#endif