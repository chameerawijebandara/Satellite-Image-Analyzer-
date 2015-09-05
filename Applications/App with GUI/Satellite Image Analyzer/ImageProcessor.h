#pragma once

#include <opencv2\highgui\highgui.hpp>
#include <vector>

class ImageProcessor
{
public:
	static int type_A_no;
	static int type_B_no;

	cv::Mat input;
	cv::Mat output;

	std::string inputFile;

	ImageProcessor();
	ImageProcessor(std::string sInputFileName);

	void Process();
	void showOutput();

	
};

