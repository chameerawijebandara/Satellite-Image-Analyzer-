#include "ImageProcessor.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/opencv.hpp"		  // opencv general include file
#include "opencv2/ml/ml.hpp"          // opencv machine learning include file
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>
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
	
	int i;
	for(i = inputFile.size()-1;i>0;i--){
		if(inputFile.at(i)=='\\')
			break;
	}
	image_path = inputFile;
	tree_images = 120;
	folder_name = inputFile.substr(0,i+1);
	imwrite("image.png",imread(inputFile));
	Mat_output = "Matlab_image.jpg";

}



void ImageProcessor::showOutput()
{
	namedWindow( "Display window", WINDOW_NORMAL );		  // Create a window for display.
	imshow( "Display window", output );                   // Show our image inside it.
    waitKey(0);											  // Wait for a keystroke in the window
}

void ImageProcessor::read_dataset(std::string filename, cv::Mat &data, cv::Mat &classes,  int total_samples)
{
 
    float pixelvalue;
	string full_name;
	cv::Mat scan_img,img;
	char img_name [200];
    //read each row of the csv file
   for(int row = 0; row < total_samples; row++)
   {
	   sprintf (img_name, "%s\\%d.jpg",filename.c_str(), row+1);
		img = imread(img_name);
		cv::cvtColor(img,scan_img,CV_RGB2GRAY);
		   //for each attribute in the row
		if(row < tree_images){
			classes.at<float>(row,1) = 1.0;
			classes.at<float>(row,0) = 0;
		}
		else{
			classes.at<float>(row,1) = 0;
			classes.at<float>(row,0) = 1.0;
		}
		
		for(int col = 0; col <ATTRIBUTES; col++){
			pixelvalue = (float)scan_img.at<uchar>(col/BOX_SIZE,col%BOX_SIZE);
			data.at<float>(row,col) = pixelvalue;
			
		}
    }
 
}


void ImageProcessor::create_dataset(string filename, cv::Mat &data,cv::Mat &test_image,string matlab_image_name)
{
    float pixelvalue;
	cv::Mat scan_img,img;
	img = imread(filename);
	cv::cvtColor(img,scan_img,CV_RGB2GRAY);

	cv::Mat gray_dot_img,dot_img;
	dot_img = imread(matlab_image_name);
	cv::cvtColor(dot_img,gray_dot_img,CV_RGB2GRAY);

	data = Mat((scan_img.rows+1-BOX_SIZE)*(scan_img.cols+1-BOX_SIZE),BOX_SIZE*BOX_SIZE,CV_32F);
   
    //read each row of the csv file
	test_image = imread(filename);

	for(int row = 0; row < scan_img.rows+1-BOX_SIZE; row++)
	{	
		for(int col = 0; col < scan_img.cols+1-BOX_SIZE; col++)
		{
			/*if((float)gray_dot_img.at<uchar>(row+BOX_SIZE/2,col+BOX_SIZE/2)>200.0f){
				test_image.at<Vec3b>(Point(col+BOX_SIZE/2,row+BOX_SIZE/2))[0] = 0;
				test_image.at<Vec3b>(Point(col+BOX_SIZE/2,row+BOX_SIZE/2))[1] = 0;
				test_image.at<Vec3b>(Point(col+BOX_SIZE/2,row+BOX_SIZE/2))[2] = 255;				
			}*/
			for(int j = 0; j <BOX_SIZE*BOX_SIZE; j++)
			{	
				if((float)gray_dot_img.at<uchar>(row+BOX_SIZE/2,col+BOX_SIZE/2)>200.0f){
					pixelvalue = (float)scan_img.at<uchar>(row+j/BOX_SIZE,col+j%BOX_SIZE);
					//draw a BLUE box around the detected circles from Matlab code
					/*if(j/7==0||j%7==6||j%7==0||j/7==6)
					{
						test_image.at<Vec3b>(row+j/BOX_SIZE,col+j%BOX_SIZE)[0] = 255;
						test_image.at<Vec3b>(row+j/BOX_SIZE,col+j%BOX_SIZE)[1] = 0;
						test_image.at<Vec3b>(row+j/BOX_SIZE,col+j%BOX_SIZE)[2] = 0;
					}*/
					
				}
				else
					pixelvalue = 0.0f;

				data.at<float>(row*(scan_img.cols+1-BOX_SIZE)+col,j) = pixelvalue;
			}
		}
    }
}

/******************************************************************************/
void ImageProcessor::Mean_variance(int *arr,cv::Mat matrix){
	 arr[0] = (int)cv::sum(cv::sum(matrix))[0]/49;
	 int var = 0;
	 
	 for(int j = 0;j < matrix.rows;j++){
		 for(int i = 0;i < matrix.cols;i++){
			 var = var + ((int)matrix.at<uchar>(j,i)-arr[0])*((int)matrix.at<uchar>(j,i)-arr[0]);
		}
	}
	 arr[1] = var/49;
 }
/******************************************************************************/


/******************************************************************************/
void ImageProcessor::Find_nearby_trees(int *count,cv::Mat dot_image,cv::Mat dot_image_out,cv::Mat rgb_image,int marging_size,int min_trees,Scalar colour,bool large_box){
	 for(int j = 0;j < dot_image.rows;j++)
	{
		for(int i = 0;i < dot_image.cols;i++)
		{
			if(dot_image.at<float>(Point(i,j)) == 255){
				int size = 1;
				int near_by_trees = 0;
				int x_min,y_min,x_max,y_max;
				bool tree_found = false;
				for (; size < marging_size; size++){
					if(i - size<0) x_min = 0;
					else x_min = i - size;

					if(i + size>dot_image.cols-1) x_max = dot_image.cols-1;
					else x_max = i + size;

					if(j - size<0) y_min = 0;
					else y_min = j - size;

					if(j + size>dot_image.rows-1) y_max = dot_image.rows-1;
					else y_max = j + size;
					near_by_trees = 0;
					for(int j1 = y_min;j1 <= y_max;j1++){
						for(int i1 = x_min;i1 <= x_max;i1++){
							if((dot_image.at<float>(Point(i1,j1)) == 255)&&(i1 != i || j1 != j)){
								near_by_trees++;
								if (near_by_trees==min_trees){
									if (size < 4){
										dot_image.at<float>(Point(i1,j1)) = 0;
									}
									tree_found = true;
									break;
								}
									
							}
						}
						if (tree_found)break;
					}
					if (tree_found)break;
				}
				if (size < marging_size){
					dot_image_out.at<float>(Point(i,j)) = 255;
					if (large_box)
					{
						for(int a=-1;a<2;a++){
							for(int b=-1;b<2;b++){
								rgb_image.at<Vec3b>(Point(i+a+BOX_SIZE/2,j+b+BOX_SIZE/2))[0] = colour[0];
								rgb_image.at<Vec3b>(Point(i+a+BOX_SIZE/2,j+b+BOX_SIZE/2))[1] = colour[1];
								rgb_image.at<Vec3b>(Point(i+a+BOX_SIZE/2,j+b+BOX_SIZE/2))[2] = colour[2];

							}
						}
					}
					else{
						/*rgb_image.at<Vec3b>(Point(i+BOX_SIZE/2,j+BOX_SIZE/2))[0] = colour[0];
						rgb_image.at<Vec3b>(Point(i+BOX_SIZE/2,j+BOX_SIZE/2))[1] = colour[1];
						rgb_image.at<Vec3b>(Point(i+BOX_SIZE/2,j+BOX_SIZE/2))[2] = colour[2];*/
					}
					count[0]++;
				}

			}
		}
	}
 }
/******************************************************************************/


void ImageProcessor::Process (int training_option)
{
	system("Detect_circles.exe");

	cv::Mat layers(3,1,CV_32S);
    layers.at<int>(0,0) = ATTRIBUTES;//input layer
    layers.at<int>(1,0) = 16;//hidden layer
    layers.at<int>(2,0) = CLASSES;//output layer
    //create the neural network.
    CvANN_MLP nnetwork(layers, CvANN_MLP::SIGMOID_SYM,0.6,1);

	if(training_option==0){
		nnetwork.load("Default_Neural_Network.xml");
	}
	else if(training_option==1){
		nnetwork.load("User_Neural_Network.xml");
	}
	else
		return;
	/*else{
		//matrix to hold the training sample
		cv::Mat training_set(TRAINING_SAMPLES,ATTRIBUTES,CV_32F);
		//matrix to hold the labels of each taining sample
		cv::Mat training_set_classifications(TRAINING_SAMPLES, CLASSES, CV_32F);
	
		//load the training and test data sets.
		read_dataset("C:\\Users\\Dell\\Desktop\\Tree_project\\New folder\\Positive", training_set, training_set_classifications, TRAINING_SAMPLES);

			// define the structure for the neural network (MLP)
			// The neural network has 3 layers.
			// - one input node per attribute in a sample so 256 input nodes
			// - 16 hidden nodes
			// - 10 output node, one for each class.
 
    
 
		CvANN_MLP_TrainParams params(                     
										// terminate the training after either 1000
										// iterations or a very small change in the
										// network wieghts below the specified value
										cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 1000, 0.000001),
										// use backpropogation for training
										CvANN_MLP_TrainParams::BACKPROP,
										// co-efficents for backpropogation training
										// recommended values taken from http://docs.opencv.org/modules/ml/doc/neural_networks.html#cvann-mlp-trainparams
										0.1,
										0.1);
 
		// train the neural network (using training data)
 
	   // printf( "\nUsing training dataset\n");
		int iterations = nnetwork.train(training_set, training_set_classifications,cv::Mat(),cv::Mat(),params);
		//printf( "Training iterations: %i\n\n", iterations);
 
		// Save the model generated into an xml file.
		CvFileStorage* storage = cvOpenFileStorage( "User_Neural_Network.xml.xml", 0, CV_STORAGE_WRITE );
		nnetwork.write(storage,"DigitOCR");
		cvReleaseFileStorage(&storage);
	}*/

	//matric to hold the test samples
	cv::Mat test_set(TEST_SAMPLES,ATTRIBUTES,CV_32F);
	//matrix to hold the test labels.
	//cv::Mat test_set_classifications(TEST_SAMPLES,CLASSES,CV_32F);
	cv::Mat classificationResult(1, CLASSES, CV_32F);
	//tree_images = 90;
	//read_dataset("C:\\Users\\Dell\\Desktop\\Tree_project\\New folder\\MatLab", test_set, test_set_classifications, TEST_SAMPLES);
	cv::Mat test_image;
	create_dataset(image_path, test_set,test_image,Mat_output);

	//Colour all the tree areas in green
	cv::Mat temp = imread(image_path);
	cvtColor(temp,temp,CV_RGB2GRAY);
	blur(temp, temp, Size(3, 3));
	erode(temp, temp, Mat());
	threshold(temp, temp, 100, 255, CV_THRESH_BINARY);
	
	for(int row = 0; row < temp.rows+1-BOX_SIZE; row++){	
		for(int col = 0; col < temp.cols+1-BOX_SIZE; col++){
			if((float)temp.at<uchar>(row,col)<175){
				test_image.at<Vec3b>(Point(col,row))[0] = 0;
				test_image.at<Vec3b>(Point(col,row))[2] = 0;
			}
		}
	}
	/////////////////////////////////////////////////////////////////////

	//create a black images to mark detected trees
	cv::Mat dot_image(test_image.rows,test_image.cols,CV_32F);
	cv::Mat dot_image1(test_image.rows,test_image.cols,CV_32F);
	cv::Mat dot_image2(test_image.rows,test_image.cols,CV_32F);
	cv::Mat dot_image3(test_image.rows,test_image.cols,CV_32F);
	dot_image = Scalar(0);
	dot_image1 = Scalar(0);
	dot_image2 = Scalar(0);
	dot_image3 = Scalar(0);

	
	//Mark a dot on the points detected by matlab
	cv::Mat gray_dot_img,Matlab_dot_img;
	Matlab_dot_img = imread(Mat_output);
	cv::cvtColor(Matlab_dot_img,gray_dot_img,CV_RGB2GRAY);
	/*for(int row = 0; row < test_image.rows; row++)
	{	
		for(int col = 0; col < test_image.cols; col++)
		{
			if((float)gray_dot_img.at<uchar>(row,col)>200.0f){
				test_image.at<Vec3b>(Point(col,row))[0] = 255;
				test_image.at<Vec3b>(Point(col,row))[1] = 0;
				test_image.at<Vec3b>(Point(col,row))[2] = 255;
			}
		}
    }*/
	///////////////////////////////////////////////////////////////////////

	cv::Mat test_image1 = imread(image_path);
	cv::Mat gray_test_image(test_image.rows,test_image.cols,CV_32F);
	cv::cvtColor(test_image1,gray_test_image,CV_RGB2GRAY);


	
    // Test the generated model with the test samples.
    cv::Mat test_sample;
    ////count of correct classifications
    //int correct_class = 0;
    ////count of wrong classifications
    //int wrong_class = 0;
 
    ////classification matrix gives the count of classes to which the samples were classified.
    //int classification_matrix[CLASSES][CLASSES]={{}};

	int count = 0;
    // for each sample in the test set.
	int ts;
    for (int tsample = 0; tsample < test_set.rows; tsample++) {
		ts = tsample;
        // extract the sample
        test_sample = test_set.row(tsample);
 
        //try to predict its class
        nnetwork.predict(test_sample, classificationResult);
        /*The classification result matrix holds weightage  of each class.
        we take the class with the highest weightage as the resultant class */
 
        // find the class with maximum weightage.
        int maxIndex = 0;
        float value = 0.0f;
        float maxValue = classificationResult.at<float>(0,0);
        for(int index=1;index<CLASSES;index++)
        {   
			value = classificationResult.at<float>(0,index);
            if(value>maxValue)
            {   
				maxValue = value;
                maxIndex=index;
            }
        }
		
		int row = tsample/(test_image.cols+1-BOX_SIZE), 
			col = tsample%(test_image.cols+1-BOX_SIZE);

		if(maxIndex == 1){
			int mean_var[2];
			Rect margin(col,row,BOX_SIZE,BOX_SIZE);
			Mean_variance(mean_var,gray_test_image(margin));
			//cout<<mean_var[0]<<"\t";

			if(mean_var[0]>75&&mean_var[0]<110){
				count++;
				//Mark detected trees in white dots on the black image
				dot_image.at<float>(Point(col,row)) = 255;

				//Mark a dot on the tree
				/*test_image.at<Vec3b>(Point(col + BOX_SIZE/2,row + BOX_SIZE/2))[0] = 15;
				test_image.at<Vec3b>(Point(col + BOX_SIZE/2,row + BOX_SIZE/2))[1] = 185;
				test_image.at<Vec3b>(Point(col + BOX_SIZE/2,row + BOX_SIZE/2))[2] = 255;*/
			
				//draw a GREEN box around the detected trees
				for(int j = 0; j <BOX_SIZE*BOX_SIZE; j++){
					//if(j/7==0||j%7==6||j%7==0||j/7==6){
						/*test_image.at<Vec3b>(row+j/BOX_SIZE,col+j%BOX_SIZE)[0] = 0;
						test_image.at<Vec3b>(row+j/BOX_SIZE,col+j%BOX_SIZE)[1] = 255;
						test_image.at<Vec3b>(row+j/BOX_SIZE,col+j%BOX_SIZE)[2] = 0;*/
					//}
				}
			}
		}
		else{
			dot_image.at<float>(Point(col,row)) = 0;
		}        
    }

	///////////////////////////////////////////////////////////////////////////////////////////////
	int new_count = 0;
	Scalar colour;
	colour = Scalar(0,0,255);
	Find_nearby_trees(&new_count,dot_image,dot_image1,test_image,10,1,colour,false);
	///////////////////////////////////////////////////////////////////////////////////////////////
	new_count = 0;
	colour = Scalar(0,255,0);
	Find_nearby_trees(&new_count,dot_image1,dot_image2,test_image,12,2,colour,false);
	///////////////////////////////////////////////////////////////////////////////////////////////
	new_count = 0;
	colour = Scalar(255,255,0);
	Find_nearby_trees(&new_count,dot_image2,dot_image3,test_image,17,1,colour,true);
	///////////////////////////////////////////////////////////////////////////////////////////////


	//cout << "\n\nCOUNT = " << ts<<"\n";
	//cout << "COUNT = " << count;
	//cout << "\nNEW COUNT = " << new_count;

	//Save result images
	imwrite(folder_name+"Result1.png",test_image);
	/*imwrite(folder_name+"Result2.png",dot_image);
	imwrite(folder_name+"Result3.png",dot_image1);
	imwrite(folder_name+"Result4.png",dot_image2);
	imwrite(folder_name+"Result5.png",dot_image3);*/
	/////////////////////////////////////////////////////

	//Outputs to show in GUI(Tree count and tree image)
	type_A_no = new_count;
	output = test_image;

 
}
void ImageProcessor::train( std::string folderPath, int total_images, int tree_images )
{
	this->tree_images = tree_images;
	cv::Mat layers(3,1,CV_32S);
    layers.at<int>(0,0) = ATTRIBUTES;//input layer
    layers.at<int>(1,0) = 16;//hidden layer
    layers.at<int>(2,0) = CLASSES;//output layer
	
    //create the neural network.
    CvANN_MLP nnetwork(layers, CvANN_MLP::SIGMOID_SYM,0.6,1);
		
	//matrix to hold the training sample
	cv::Mat training_set(total_images,ATTRIBUTES,CV_32F);
	//matrix to hold the labels of each taining sample
	cv::Mat training_set_classifications(total_images, CLASSES, CV_32F);
	//load the training and test data sets. 
	read_dataset(folderPath, training_set, training_set_classifications, total_images);
	//folderPath = "C:\\Users\\Dell\\Desktop\\Tree_project\\New folder\\Positive";
	
		// define the structure for the neural network (MLP)
		// The neural network has 3 layers.
		// - one input node per attribute in a sample so 256 input nodes
		// - 16 hidden nodes
		// - 10 output node, one for each class.
 
    
 
	CvANN_MLP_TrainParams params(                     
									// terminate the training after either 1000
									// iterations or a very small change in the
									// network wieghts below the specified value
									cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 1000, 0.000001),
									// use backpropogation for training
									CvANN_MLP_TrainParams::BACKPROP,
									// co-efficents for backpropogation training
									// recommended values taken from http://docs.opencv.org/modules/ml/doc/neural_networks.html#cvann-mlp-trainparams
									0.1,
									0.1);
 
	// train the neural network (using training data)
 
	// printf( "\nUsing training dataset\n");
	int iterations = nnetwork.train(training_set, training_set_classifications,cv::Mat(),cv::Mat(),params);
	//printf( "Training iterations: %i\n\n", iterations);
 
	// Save the model generated into an xml file.
	CvFileStorage* storage = cvOpenFileStorage( "User_Neural_Network.xml", 0, CV_STORAGE_WRITE );
	nnetwork.write(storage,"DigitOCR");
	cvReleaseFileStorage(&storage);
	

}
