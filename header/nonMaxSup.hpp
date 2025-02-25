#ifndef NONMAXSUP_HPP
#define NONMAXSUP_HPP
#include <cmath>

unsigned char* computeGradientDirection(unsigned char* sobelX, unsigned char* sobelY, int width, int height);
unsigned char* nonMaxSuppression(unsigned char* image, unsigned char* direction, int width, int height);

#endif
