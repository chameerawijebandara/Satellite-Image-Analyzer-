#pragma once

#include <opencv2\highgui\highgui.hpp>
#include <vector>

#define TRAINING_SAMPLES 281       //Number of samples in training dataset
#define ATTRIBUTES 49  //Number of pixels per sample.7X7
#define TEST_SAMPLES 900      //Number of samples in test dataset
#define CLASSES 2                  //Number of distinct labels.
#define BOX_SIZE 7 


class ImageProcessor
{

private :
		int tree_images; 
		std::string folder_name;
		std::string Mat_output;
		std::string image_path;


public:
	static int type_A_no;
	static int type_B_no;

	cv::Mat input;
	cv::Mat output;

	std::string inputFile;

	
	ImageProcessor(std::string sInputFileName);

	void Process();
	void showOutput();

	private:
		ImageProcessor();
		void Find_nearby_trees(int *count,cv::Mat dot_image,cv::Mat dot_image_out,cv::Mat rgb_image,int marging_size,int min_trees,cv::Scalar colour,bool large_box);
		void Mean_variance(int *arr,cv::Mat matrix);
		void create_dataset(std::string filename, cv::Mat &data,cv::Mat &test_image,std::string matlab_image_name);
		void read_dataset(char *filename, cv::Mat &data, cv::Mat &classes,  int total_samples);

	
};

