#define _CRT_SECURE_NO_DEPRECATE
#include "stdafx.h"
#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>


using namespace cv;
using namespace std;

#define BOX_SIZE 7

void DrawLines(Mat img);
void CallBackFunc(int event, int x, int y, int flags, void* userdata);
void DrawBox(Mat img,int x,int y);

int current_x,current_y;
int imagecount_p = 0;
//int imagecount_n = 0;
Mat clone_image,image;

int main( int argc, const char** argv )
{
	cout << "First Image Number = ";
	cin >> imagecount_p;
	image = imread("C:\\Users\\Dell\\Desktop\\Tree_project\\img.jpg");
	namedWindow("Mark the Lanes", WINDOW_NORMAL);
	imshow("Mark the Lanes", image);
	/*clone_image = image.clone();
	namedWindow("Mark the Lanes", WINDOW_NORMAL);
	DrawLines(image);
	imshow("Mark the Lanes", image);*/

	setMouseCallback("Mark the Lanes", CallBackFunc, 0);
	waitKey(0);

	return 0;

}




/*Detect mouse moves and events of keyboard*/
/*void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	char name[150];
	if (event == EVENT_RBUTTONDOWN)
	{
		imagecount_n++;
		sprintf(name,"C:\\Users\\Dell\\Desktop\\Tree_project\\New folder\\Negative\\%d.jpg",imagecount_n);
		Rect margin(BOX_SIZE*(x/BOX_SIZE),BOX_SIZE*(y/BOX_SIZE),BOX_SIZE,BOX_SIZE);
		imwrite(name,clone_image(margin));
	}
	else if (event == EVENT_LBUTTONDOWN)
	{
		cout<<x<<" "<<y<<"\n";
		imagecount_p++;
		sprintf(name,"C:\\Users\\Dell\\Desktop\\Tree_project\\New folder\\Positive\\%d.jpg",imagecount_p);
		Rect margin(BOX_SIZE*(x/BOX_SIZE),BOX_SIZE*(y/BOX_SIZE),BOX_SIZE,BOX_SIZE);
		imwrite(name,clone_image(margin));
			
	}
		
	else if (event == EVENT_MOUSEMOVE)
	{}

	if (event == EVENT_MOUSEMOVE && flags == EVENT_FLAG_SHIFTKEY)
	{}

	else if (event == EVENT_MOUSEMOVE)
	{}

}*/

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	char name[150];
	if (event == EVENT_RBUTTONDOWN)
	{		
		sprintf(name,"C:\\Users\\Dell\\Desktop\\Tree_project\\New folder\\Positive\\%d.jpg",imagecount_p);
		Rect margin(x-BOX_SIZE/2,y-BOX_SIZE/2,BOX_SIZE,BOX_SIZE);
		imwrite(name,image(margin));
		cout << "\tIMAGE SAVED";
		imagecount_p++;
	}
	else if (event == EVENT_LBUTTONDOWN)
	{
		current_x = x;
		current_y = y;
		cout<<"\n"<<"x = "<<x<<"\t\t"<<"y = "<<y;
		clone_image = image.clone();
		DrawBox(clone_image,x,y);
		namedWindow("Mark the Lanes", WINDOW_NORMAL);
		imshow("Mark the Lanes", clone_image);
	}
		
	else if (event == EVENT_MOUSEMOVE)
	{}

	if (event == EVENT_MOUSEMOVE && flags == EVENT_FLAG_SHIFTKEY)
	{}

	else if (event == EVENT_MOUSEMOVE)
	{}

}

void DrawBox(Mat img,int x,int y)
{
	int width,height;
	width = img.cols;
	height = img.rows;
	if(x>BOX_SIZE/2 && y>BOX_SIZE/2 && x<width-1-BOX_SIZE/2 && y<height-1-BOX_SIZE/2)
	{
		for (int i = x-1-BOX_SIZE/2;  i <= x+1+BOX_SIZE/2; i++)
		{
			img.at<Vec3b>(Point(i,y-1-BOX_SIZE/2))[0] = 0;
			img.at<Vec3b>(Point(i,y-1-BOX_SIZE/2))[1] = 0;
			img.at<Vec3b>(Point(i,y-1-BOX_SIZE/2))[2] = 0;

			img.at<Vec3b>(Point(i,y+1+BOX_SIZE/2))[0] = 0;
			img.at<Vec3b>(Point(i,y+1+BOX_SIZE/2))[1] = 0;
			img.at<Vec3b>(Point(i,y+1+BOX_SIZE/2))[2] = 0;
		}

		for (int i = y-1-BOX_SIZE/2;  i <= y+1+BOX_SIZE/2; i++)
		{
			img.at<Vec3b>(Point(x-1-BOX_SIZE/2,i))[0] = 0;
			img.at<Vec3b>(Point(x-1-BOX_SIZE/2,i))[1] = 0;
			img.at<Vec3b>(Point(x-1-BOX_SIZE/2,i))[2] = 0;

			img.at<Vec3b>(Point(x+1+BOX_SIZE/2,i))[0] = 0;
			img.at<Vec3b>(Point(x+1+BOX_SIZE/2,i))[1] = 0;
			img.at<Vec3b>(Point(x+1+BOX_SIZE/2,i))[2] = 0;

		}
	}
}

void DrawLines(Mat img)
{
	int width,height;
	width = img.cols;
	height = img.rows;

	
	for (int x = 1;  x <= width/BOX_SIZE; x++)
	{
		for (int y = 0; y < height; y++)
		{
			for (int i = 0; i < 1; i++)
			{
				img.at<Vec3b>(Point(BOX_SIZE*x-1-i,y))[0] = 0;
				img.at<Vec3b>(Point(BOX_SIZE*x-1-i,y))[1] = 0;
				img.at<Vec3b>(Point(BOX_SIZE*x-1-i,y))[2] = 0;
			}
				
		}
	}

	for (int x = 0;  x < width; x++)
	{
		for (int y = 1; y <= height/BOX_SIZE; y++)
		{
			for (int i = 0; i < 1; i++)
			{
				img.at<Vec3b>(Point(x,BOX_SIZE*y-1-i))[0] = 0;
				img.at<Vec3b>(Point(x,BOX_SIZE*y-1-i))[1] = 0;
				img.at<Vec3b>(Point(x,BOX_SIZE*y-1-i))[2] = 0;
			}
				
		}
	}
}