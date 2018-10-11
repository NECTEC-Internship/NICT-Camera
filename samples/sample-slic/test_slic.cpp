/*
 * test_slic.cpp.
 *
 * Written by: Pascal Mettes.
 *
 * This file creates an over-segmentation of a provided image based on the SLIC
 * superpixel algorithm, as implemented in slic.h and slic.cpp.
 */
 
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <float.h>
using namespace std;
using namespace cv;

#include "slic.h"

Mat input;

int main(int argc, char *argv[]) {
    /* Load the image and convert to Lab colour space. */
    input = imread(argv[1]);
    if(input.data){
    	    cvtColor(input, input, CV_BGR2Lab);
    	    IplImage *image = new IplImage(input);
    	    //IplImage *image = cvLoadImage(argv[1], 1);
	    //IplImage *lab_image = cvCloneImage(image);
	    
	    
	    /* Yield the number of superpixels and weight-factors from the user. */
	    int w = image->width, h = image->height;
	    int nr_superpixels = atoi(argv[2]);
	    int nc = atoi(argv[3]);
	
	    double step = sqrt((w * h) / (double) nr_superpixels);
	    
	    /* Perform the SLIC superpixel algorithm. */
	    Slic slic;
	    slic.generate_superpixels(image, step, nc);
	    slic.create_connectivity(image);
	    
	    /* Display the contours and show the result. */
	    slic.display_contours(image, cv::Scalar(255,0,0));
	    Mat converted_image = cvarrToMat(image);
	    cvtColor(converted_image, converted_image, CV_Lab2BGR);
	    //cvShowImage("result", image);
	    //cvWaitKey(0);
	    imwrite(argv[4], converted_image);
	    //cvSaveImage(argv[4], image);
	    cout << "Saved" << endl;
    }

}
