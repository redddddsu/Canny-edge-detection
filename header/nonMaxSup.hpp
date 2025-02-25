#ifndef NONMAXSUP_HPP
#define NONMAXSUP_HPP

unsigned char* computeGradientDirection(unsigned char* sobel, int width, int height);
unsigned char* nonMaxSuppression(unsigned char* image, int width, int height);

#endif
