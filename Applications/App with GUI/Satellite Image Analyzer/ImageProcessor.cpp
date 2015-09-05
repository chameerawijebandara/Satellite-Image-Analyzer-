#include "ImageProcessor.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

using namespace cv;
using namespace std;

int ImageProcessor::type_A_no = 0;
int ImageProcessor::type_B_no = 0;

ImageProcessor::ImageProcessor()
{

}
ImageProcessor::ImageProcessor(string sInputFileName): inputFile(sInputFileName)
{

}
void ImageProcessor::Process()
{
    input = imread(inputFile, CV_LOAD_IMAGE_COLOR);   // Read the file

	cvtColor( input, output, CV_BGR2GRAY );

	type_A_no = 100;
	type_B_no = 111;
}

void ImageProcessor::showOutput()
{
	namedWindow( "Display window", WINDOW_NORMAL );// Create a window for display.
	imshow( "Display window", output );                   // Show our image inside it.
    waitKey(0);                                          // Wait for a keystroke in the window
}
