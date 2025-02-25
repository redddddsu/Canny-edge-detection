#ifndef NONMAXSUP_HPP
#define NONMAXSUP_HPP

unsigned char* computeGradientDirection(unsigned char* sobelX, unsigned char* sobelY, int width, int height);
unsigned char* nonMaxSuppression(unsigned char* image, int width, int height);

#endif
