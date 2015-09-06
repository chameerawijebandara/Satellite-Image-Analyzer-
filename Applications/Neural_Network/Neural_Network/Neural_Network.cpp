// Neural_Network.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"


#define _CRT_SECURE_NO_DEPRECATE
#include "stdafx.h"
// TrainNetwork.cpp : Defines the entry point for the console application.
 
#include "opencv2/opencv.hpp"    // opencv general include file
#include "opencv2/ml/ml.hpp"          // opencv machine learning include file
#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;
using namespace cv;
/******************************************************************************/
 
#define TRAINING_SAMPLES 281       //Number of samples in training dataset
#define ATTRIBUTES 49  //Number of pixels per sample.7X7
#define TEST_SAMPLES 900      //Number of samples in test dataset
#define CLASSES 2                  //Number of distinct labels.
#define BOX_SIZE 7 
int tree_images = 120;
std::string folder_name = "C:\\Users\\Dell\\Desktop\\Tree_project\\image1\\";
std::string image_name = "image1.jpg";
std::string Mat_output = "Matlab_image.jpg";
/********************************************************************************
This function will read the csv files(training and test dataset) and convert them
into two matrices. classes matrix have 10 columns, one column for each class label. If the label of nth row in data matrix
is, lets say 5 then the value of classes[n][5] = 1.
********************************************************************************/
void read_dataset(char *filename, cv::Mat &data, cv::Mat &classes,  int total_samples)
{
 
    //int label;
    float pixelvalue;
	string full_name;
    //open the file
    //FILE* inputfile = fopen( filename, "r" );
	cv::Mat scan_img,img;
	char img_name [200];
    //read each row of the csv file
   for(int row = 0; row < total_samples; row++)
   {
		sprintf (img_name, "%s\\%d.jpg",filename, row+1);
		img = imread(img_name);
		cv::cvtColor(img,scan_img,CV_RGB2GRAY);
		   //for each attribute in the row
		if(row < tree_images)
		{
			classes.at<float>(row,1) = 1.0;
			classes.at<float>(row,0) = 0;
		}
		else
		{
			classes.at<float>(row,1) = 0;
			classes.at<float>(row,0) = 1.0;
		}
		
		for(int col = 0; col <ATTRIBUTES; col++)
		{
			pixelvalue = (float)scan_img.at<uchar>(col/BOX_SIZE,col%BOX_SIZE);
			data.at<float>(row,col) = pixelvalue;
			
		}
    }
 
}

/******************************************************************************/

void create_dataset(string filename, cv::Mat &data,cv::Mat &test_image,string matlab_image_name)
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
			if((float)gray_dot_img.at<uchar>(row+BOX_SIZE/2,col+BOX_SIZE/2)>200.0f){
				test_image.at<Vec3b>(Point(col+BOX_SIZE/2,row+BOX_SIZE/2))[0] = 0;
				test_image.at<Vec3b>(Point(col+BOX_SIZE/2,row+BOX_SIZE/2))[1] = 0;
				test_image.at<Vec3b>(Point(col+BOX_SIZE/2,row+BOX_SIZE/2))[2] = 255;				
			}
			for(int j = 0; j <BOX_SIZE*BOX_SIZE; j++)
			{	
				if((float)gray_dot_img.at<uchar>(row+BOX_SIZE/2,col+BOX_SIZE/2)>200.0f){
					pixelvalue = (float)scan_img.at<uchar>(row+j/BOX_SIZE,col+j%BOX_SIZE);
					//draw a BLUE box around the detected circles from Matlab code
					if(j/7==0||j%7==6||j%7==0||j/7==6)
					{
						test_image.at<Vec3b>(row+j/BOX_SIZE,col+j%BOX_SIZE)[0] = 255;
						test_image.at<Vec3b>(row+j/BOX_SIZE,col+j%BOX_SIZE)[1] = 0;
						test_image.at<Vec3b>(row+j/BOX_SIZE,col+j%BOX_SIZE)[2] = 0;
					}
					
				}
				else
					pixelvalue = 0.0f;

				data.at<float>(row*(scan_img.cols+1-BOX_SIZE)+col,j) = pixelvalue;
			}
		}
    }
}

/******************************************************************************/
void Mean_variance(int *arr,cv::Mat matrix){
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
void Find_nearby_trees(int *count,cv::Mat dot_image,cv::Mat dot_image_out,cv::Mat rgb_image,int marging_size,int min_trees,Scalar colour){
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
					rgb_image.at<Vec3b>(Point(i+BOX_SIZE/2,j+BOX_SIZE/2))[0] = colour[0];
					rgb_image.at<Vec3b>(Point(i+BOX_SIZE/2,j+BOX_SIZE/2))[1] = colour[1];
					rgb_image.at<Vec3b>(Point(i+BOX_SIZE/2,j+BOX_SIZE/2))[2] = colour[2];
					count[0]++;
				}

			}
		}
	}
 }	
/******************************************************************************/


int main( int argc, char** argv )
{
	//matrix to hold the training sample
	cv::Mat training_set(TRAINING_SAMPLES,ATTRIBUTES,CV_32F);
	//matrix to hold the labels of each taining sample
	cv::Mat training_set_classifications(TRAINING_SAMPLES, CLASSES, CV_32F);
	//matric to hold the test samples
	//cv::Mat test_set;
	cv::Mat test_set(TEST_SAMPLES,ATTRIBUTES,CV_32F);
	//matrix to hold the test labels.
	cv::Mat test_set_classifications(TEST_SAMPLES,CLASSES,CV_32F);
 
	//
	cv::Mat classificationResult(1, CLASSES, CV_32F);
	//load the training and test data sets.
	read_dataset("C:\\Users\\Dell\\Desktop\\Tree_project\\New folder\\Positive", training_set, training_set_classifications, TRAINING_SAMPLES);
	tree_images = 90;
	read_dataset("C:\\Users\\Dell\\Desktop\\Tree_project\\New folder\\MatLab", test_set, test_set_classifications, TEST_SAMPLES);
	cv::Mat test_image;
	create_dataset(folder_name+image_name, test_set,test_image,folder_name+Mat_output);
	
	//create a black image to mark detected trees
	cv::Mat dot_image(test_image.rows,test_image.cols,CV_32F);
	cv::Mat dot_image1(test_image.rows,test_image.cols,CV_32F);
	cv::Mat dot_image2(test_image.rows,test_image.cols,CV_32F);
	cv::Mat dot_image3(test_image.rows,test_image.cols,CV_32F);
	dot_image = Scalar(0);
	dot_image1 = Scalar(0);
	dot_image2 = Scalar(0);
	dot_image3 = Scalar(0);

	//
	cv::Mat gray_dot_img,dot_img;
	dot_img = imread(folder_name+Mat_output);
	cv::cvtColor(dot_img,gray_dot_img,CV_RGB2GRAY);
	for(int row = 0; row < test_image.rows; row++)
	{	
		for(int col = 0; col < test_image.cols; col++)
		{
			if((float)gray_dot_img.at<uchar>(row,col)>200.0f){
				test_image.at<Vec3b>(Point(col,row))[0] = 0;
				test_image.at<Vec3b>(Point(col,row))[1] = 0;
				test_image.at<Vec3b>(Point(col,row))[2] = 255;
			}
		}
    }
	test_image = imread(folder_name+image_name);
	cv::Mat gray_test_image(test_image.rows,test_image.cols,CV_32F);
	cv::cvtColor(test_image,gray_test_image,CV_RGB2GRAY);
		// define the structure for the neural network (MLP)
		// The neural network has 3 layers.
		// - one input node per attribute in a sample so 256 input nodes
		// - 16 hidden nodes
		// - 10 output node, one for each class.
 
    cv::Mat layers(3,1,CV_32S);
    layers.at<int>(0,0) = ATTRIBUTES;//input layer
    layers.at<int>(1,0) = 16;//hidden layer
    layers.at<int>(2,0) = CLASSES;//output layer
		
		

    //create the neural network.
    CvANN_MLP nnetwork(layers, CvANN_MLP::SIGMOID_SYM,0.6,1);
 
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
 
    printf( "\nUsing training dataset\n");
    int iterations = nnetwork.train(training_set, training_set_classifications,cv::Mat(),cv::Mat(),params);
    printf( "Training iterations: %i\n\n", iterations);
 
    // Save the model generated into an xml file.
    CvFileStorage* storage = cvOpenFileStorage( "C:\\Users\\Dell\\Desktop\\Tree_project\\param.xml", 0, CV_STORAGE_WRITE );
    nnetwork.write(storage,"DigitOCR");
    cvReleaseFileStorage(&storage);
 
    // Test the generated model with the test samples.
    cv::Mat test_sample;
    //count of correct classifications
    int correct_class = 0;
    //count of wrong classifications
    int wrong_class = 0;
 
    //classification matrix gives the count of classes to which the samples were classified.
    int classification_matrix[CLASSES][CLASSES]={{}};
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
				//cout << tsample << "  "<< row +1<<"  "<< col +1<<"  "<< test_image.cols+1-BOX_SIZE << " \n";

				//Mark detected trees in white dots on the black image
				dot_image.at<float>(Point(col,row)) = 255;

				//Mark a dot on the tree
				test_image.at<Vec3b>(Point(col + BOX_SIZE/2,row + BOX_SIZE/2))[0] = 15;
				test_image.at<Vec3b>(Point(col + BOX_SIZE/2,row + BOX_SIZE/2))[1] = 185;
				test_image.at<Vec3b>(Point(col + BOX_SIZE/2,row + BOX_SIZE/2))[2] = 255;
			
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
	Find_nearby_trees(&new_count,dot_image,dot_image1,test_image,10,1,colour);
	///////////////////////////////////////////////////////////////////////////////////////////////
	new_count = 0;
	colour = Scalar(0,255,0);
	Find_nearby_trees(&new_count,dot_image1,dot_image2,test_image,12,2,colour);
	///////////////////////////////////////////////////////////////////////////////////////////////
	new_count = 0;
	colour = Scalar(255,255,0);
	Find_nearby_trees(&new_count,dot_image2,dot_image3,test_image,17,1,colour);
	///////////////////////////////////////////////////////////////////////////////////////////////


	cout << "\n\nCOUNT = " << ts<<"\n";
	cout << "COUNT = " << count;
	cout << "\nNEW COUNT = " << new_count;
	imwrite(folder_name+"Result1.png",test_image);
	imwrite(folder_name+"Result2.png",dot_image);
	imwrite(folder_name+"Result3.png",dot_image1);
	imwrite(folder_name+"Result4.png",dot_image2);
	imwrite(folder_name+"Result5.png",dot_image3);
	namedWindow("Trees",WINDOW_NORMAL);
	imshow("Trees",test_image);waitKey(1);
	namedWindow("Trees as Dots 3",WINDOW_NORMAL);
	imshow("Trees as Dots 3",dot_image3);waitKey(0);

	cout << "\n\n";
    /*printf( "\nResults on the testing dataset\n"
    "\tCorrect classification: %d (%g%%)\n"
    "\tWrong classifications: %d (%g%%)\n", 
    correct_class, (double) correct_class*100/TEST_SAMPLES,
    wrong_class, (double) wrong_class*100/TEST_SAMPLES);
    cout<<"   ";
    for (int i = 0; i < CLASSES; i++)
    {
        cout<< i<<"\t";
    }
    cout<<"\n";
    for(int row=0;row<CLASSES;row++)
    {
		cout<<row<<"   ";
        for(int col=0;col<CLASSES;col++)
        {
            cout<<classification_matrix[row][col]<<"\t";
        }
        cout<<"\n";
    }*/
	
	int a;
	cin >> a;
    return 0;
 
}