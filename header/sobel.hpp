#ifndef SOBEL_HPP
#define SOBEL_HPP

unsigned char* sobelX(unsigned char* image, int width, int height);
unsigned char* sobelY(unsigned char* image, int width, int height);
unsigned char* computeMagnitude(unsigned char* sobelX, unsigned char* sobelY, int width, int height);

#endif