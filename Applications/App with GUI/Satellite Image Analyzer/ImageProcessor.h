#pragma once

#include <opencv2\highgui\highgui.hpp>
#include <vector>

class ImageProcessor
{
public:
	ImageProcessor();
	ImageProcessor::ImageProcessor(std::string sInputFileName, std::string sOutputFileName, std::string sOutputFileNameTxt, int iStartHour, int iStartMinute, int iStartSecond, int iNoLanes);
	
};

