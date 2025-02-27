#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../header/stb_image.h"
#include "../header/stb_image_write.h"

#include "../header/gaussian.hpp"
#include "../header/sobel.hpp"
#include "../header/nonMaxSup.hpp"
#include "../header/threshhold.hpp"


using namespace std;

int main() {
    int width, height, channel;
    unsigned char *image = stbi_load("./src/image.jpg", &width, &height, &channel, 1);

    float sigma = 1.0f;
    float kernel[KERNEL_SIZE][KERNEL_SIZE];

    // generateGaussian(kernel, KERNEL_SIZE, sigma);

    // unsigned char *gaussian = applyGaussianKernel(kernel, KERNEL_SIZE, image, width, height);
    // stbi_write_jpg("./results/gaussian.jpg", width, height, 1, gaussian, 90);

    unsigned char* sobelx = sobelX(image, width, height);
    unsigned char* sobely = sobelY(image, width, height);
    unsigned char* sobel = computeMagnitude(sobelx, sobely, width, height);
    stbi_write_jpg("./results/sobel.jpg", width, height, 1, sobel, 90);

    unsigned char* direction = computeGradientDirection(sobelx, sobely, width, height);
    stbi_write_jpg("./results/direction.jpg", width, height, 1, direction, 90);

    unsigned char* nms = nonMaxSuppression(sobel, direction, width, height);
    stbi_write_jpg("./results/nms.jpg", width, height, 1, nms, 90);

    delete[] image;
    // delete[] gaussian;
    delete[] sobelx;
    delete[] sobely;
    delete[] sobel;
    delete[] direction;

    unsigned char* threshhold = applyThreshhold(nms, width, height);
    stbi_write_jpg("./results/threshhold.jpg", width, height, 1, threshhold, 90);
    
    unsigned char* edgeLink = edgeLinking(threshhold, width, height); 
    stbi_write_jpg("./results/edgeLink.jpg", width, height, 1, edgeLink, 90);



   
    delete[] nms;
    delete[] threshhold;
    delete[] edgeLink;
    return 0;
}