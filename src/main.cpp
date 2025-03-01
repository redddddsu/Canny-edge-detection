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
    int kernelSize = 3;
    float kernel[KERNEL_SIZE][KERNEL_SIZE];


    /*
    Gaussian blurs the image to handle images with high intensity
    We first have to generate the gaussian kernel then map it to each pixel of the image

    I have it commented out since the image I have used for testing doesn't require blur
    */
    // generateGaussian(kernel, KERNEL_SIZE, sigma);

    // unsigned char *gaussian = applyGaussianKernel(kernel, KERNEL_SIZE, image, width, height);
    // stbi_write_jpg("./results/gaussian.jpg", width, height, 1, gaussian, 90);

    /*
    The sobel kernel to do the edge detection
    sobel x and y are calculated differently to calculate the direction of the pixel later on    
    */
    unsigned char* sobel_x = sobelX(image, width, height);
    unsigned char* sobel_y = sobelY(image, width, height);
    unsigned char* sobel = computeMagnitude(sobel_x, sobel_y, width, height);
    stbi_write_jpg("./results/sobel.jpg", width, height, 1, sobel, 90);

    /*
    Uses sobel x and y to calculate the direction of each pixel
    The direction is used to do non-maximum suppression 
    */
    unsigned char* direction = computeGradientDirection(sobel_x, sobel_y, width, height);
    stbi_write_jpg("./results/direction.jpg", width, height, 1, direction, 90);


    /*
    Non-maximum suppression uses direction of the pixel to compare with it's neighboring pixels
    to determine the strongest intensity to remain
    */
    unsigned char* nms = nonMaxSuppression(sobel, direction, width, height);
    stbi_write_jpg("./results/nms.jpg", width, height, 1, nms, 90);

    /*
    Clear memory since we are talking about A LOT of memory with these images
    */
    delete[] image;
    // delete[] gaussian;
    delete[] sobel_x;
    delete[] sobel_y;
    delete[] sobel;
    delete[] direction;

    /*
    Threshholding determine strong and weak pixels
    Strong are marked by 255 while weak are marked by 20
    Rest are set to 0
    */
    unsigned char* threshhold = applyThreshhold(nms, width, height);
    stbi_write_jpg("./results/threshhold.jpg", width, height, 1, threshhold, 90);
    
    /*
    Edge linking look for at every weak pixel (20) and check it's neighbors to check if it is connected to a strong pixel
    If it is, set to 255, if not, 0
    */
    unsigned char* edgeLink = edgeLinking(threshhold, width, height); 
    stbi_write_jpg("./results/edgeLink.jpg", width, height, 1, edgeLink, 90);
   
    delete[] nms;
    delete[] threshhold;
    delete[] edgeLink;
    return 0;
}