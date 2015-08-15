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

using namespace std;
using namespace cv;
/******************************************************************************/
 
#define TRAINING_SAMPLES 201       //Number of samples in training dataset
#define ATTRIBUTES 49  //Number of pixels per sample.16X16
#define TEST_SAMPLES 110      //Number of samples in test dataset
#define CLASSES 2                  //Number of distinct labels.
#define BOX_SIZE 7 
int tree_images = 120;
int x = 0;		//for test
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
			//if its the pixel value.
			//if (col < ATTRIBUTES){
 
			//    fscanf(inputfile, "%f,", &pixelvalue);
			pixelvalue = (float)scan_img.at<uchar>(col/BOX_SIZE,col%BOX_SIZE);
			data.at<float>(row,col) = pixelvalue;
			//}//if its the label
			//else if (col == ATTRIBUTES){
			//    //make the value of label column in that row as 1.
			//    fscanf(inputfile, "%i", &label);
			//    classes.at<float>(row,label) = 1.0;
 
			//}
		}

		//cout << row <<"\n";
    }
 
    //fclose(inputfile);
 
}

/******************************************************************************/

void create_dataset(char *filename, cv::Mat &data)
{
    float pixelvalue;
	cv::Mat scan_img,img;
	img = imread(filename);
	cv::cvtColor(img,scan_img,CV_RGB2GRAY);
	data = Mat((scan_img.rows+1-BOX_SIZE)*(scan_img.cols+1-BOX_SIZE),BOX_SIZE*BOX_SIZE,CV_32F);
   
    //read each row of the csv file
	for(int row = 0; row < scan_img.rows+1-BOX_SIZE; row++)
	{	
		for(int col = 0; col < scan_img.cols+1-BOX_SIZE; col++)
		{
			for(int j = 0; j <BOX_SIZE*BOX_SIZE; j++)
			{	
				pixelvalue = (float)scan_img.at<uchar>(row+j/BOX_SIZE,col+j%BOX_SIZE);
				data.at<float>(row*col+col,j) = pixelvalue;
					//for test
					if(pixelvalue<0)		
						x = 5;
					/////////////////
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
	read_dataset("C:\\Users\\Dell\\Desktop\\Tree_project\\New folder\\Test", test_set, test_set_classifications, TEST_SAMPLES);
	//create_dataset("C:\\Users\\Dell\\Desktop\\Tree_project\\image1.jpg", test_set);
	cv::Mat test_image = imread("C:\\Users\\Dell\\Desktop\\Tree_project\\image1.jpg");
	cv::Mat dot_image(test_image.rows,test_image.cols,CV_32F);
	dot_image = Scalar(0);
	
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
    for (int tsample = 0; tsample < test_set.rows; tsample++) {
 
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
        {   value = classificationResult.at<float>(0,index);
            if(value>maxValue)
            {   
				maxValue = value;
                maxIndex=index;
            }
        }
		
		int row = tsample/(test_image.cols+1-BOX_SIZE) + BOX_SIZE/2, 
				col = tsample%(test_image.cols+1-BOX_SIZE) + BOX_SIZE/2;
		if(maxIndex == 1){
			count++;
			test_image.at<Vec3b>(Point(col,row))[0] = 255;
			test_image.at<Vec3b>(Point(col,row))[1] = 0;
			test_image.at<Vec3b>(Point(col,row))[2] = 0;

			dot_image.at<float>(Point(col,row)) = 255;
			//printf("Found at row %d  %d %d\n", tsample,row,col);

		}

		else{
			dot_image.at<float>(Point(col,row)) = 0;
		}
        //printf("Testing Sample %i -> class result (digit %d  %f  %f)\n", tsample,maxIndex, classificationResult.at<float>(0,0),classificationResult.at<float>(0,1));
 
        //Now compare the predicted class to the actural class. if the prediction is correct then\
        //test_set_classifications[tsample][ maxIndex] should be 1.
        //if the classification is wrong, note that.
        if (test_set_classifications.at<float>(tsample%TEST_SAMPLES, maxIndex)!=1.0f)
        {
            // if they differ more than floating point error => wrong class
 
            wrong_class++;
 
            //find the actual label 'class_index'
            for(int class_index=0;class_index<CLASSES;class_index++)
            {
                if(test_set_classifications.at<float>(tsample%TEST_SAMPLES, class_index)==1.0f)
                {
                    classification_matrix[class_index][maxIndex]++;// A class_index sample was wrongly classified as maxindex.
                    break;
                }
            }
 
        } else {
 
            // otherwise correct
            correct_class++;
            classification_matrix[maxIndex][maxIndex]++;
        }
    }

	cout << "COUNT = " << count;
	namedWindow("show",WINDOW_NORMAL);
	imshow("show",test_image);waitKey(1);
	namedWindow("sho",WINDOW_NORMAL);
	imshow("sho",dot_image);waitKey(0);
	cout << "\n\n";
    printf( "\nResults on the testing dataset\n"
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
    }
	
	//for test
	float pixelvalue;
	for(int row = 0; row < test_set.rows; row++)
	{	
		for(int col = 0; col < test_set.cols; col++)
		{
			pixelvalue = (float)test_set.at<float>(row,col);
			if(pixelvalue<0)
				x = 5;
		}
	}
	cout << "x = "<< x << "\n\n";

	//cout << test_set.row(33)<<"\n\n";
	double *m;
	m = nnetwork.get_weights(0);
	for(int i = 0;i<4;i++)
	{
		cout << i <<" = "<< m[i] <<"\n";
	}
	/////////////////////////////////

	int a;
	cin >> a;
    return 0;
 
}