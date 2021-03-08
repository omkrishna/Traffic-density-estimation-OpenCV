/* 
Subtask2 - Task 1 - C0P290. Semester 2, 2020-21
Authors - Harshita(2019CS10357) & Om Krishna(2019CS10272)
*/

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/imgproc/imgproc_c.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace cv;
using namespace std;
int c = 0;

string int2str(int &i) 
{
    string s;
    stringstream ss(s);
    ss << i;
    return ss.str();
}

int main(int argc, char **argv) 
{
	string s;

	VideoCapture cap(argv[1]);
	if (!cap.isOpened())  
	{
		cout << "Err : Couldnt read the video file. Check the path/extension" << endl;
		return -1;
	}

	Mat img = imread(argv[2]);
    if(!img.data)
	{
        cout << "Err : Couldnt read the image file. Check the path/extension" << endl;
        return -1;
    }

	cvtColor(img,img,COLOR_BGR2GRAY);
	vector<Point2f> img_points;
    vector<Point2f> crp_points;

	img_points.push_back(Point2f(300,100));
	img_points.push_back(Point2f(446,100));
	img_points.push_back(Point2f(520,360));
	img_points.push_back(Point2f(120,360));

    //Points start at top-left and go clockwise
    crp_points.push_back(Point2f(0,0));
    crp_points.push_back(Point2f(300,0));
    crp_points.push_back(Point2f(300,600));
    crp_points.push_back(Point2f(0,600));

    Size size(300,600);
    Mat h2 = findHomography(img_points,crp_points);
    warpPerspective(img,img,h2,size);

	/* double fps = cap.get(cv::CAP_PROP_FPS); //get the frames per seconds of the video
	cout << "Frame per seconds : " << fps << endl; */

	while (1)
	{
		Mat frame;
		Mat Gray_frame;
		bool bSuccess = cap.read(frame); // read a new frame from video

		if (!bSuccess) { cout << "Fin" << endl; break; }

		cvtColor(frame,frame,COLOR_BGR2GRAY);

		img_points.push_back(Point2f(300,100));
		img_points.push_back(Point2f(446,100));
		img_points.push_back(Point2f(520,360));
		img_points.push_back(Point2f(120,360));

		//Points start at top-left and go clockwise
		crp_points.push_back(Point2f(0,0));
		crp_points.push_back(Point2f(300,0));
		crp_points.push_back(Point2f(300,600));
		crp_points.push_back(Point2f(0,600));

		Size size(300,600);
		Mat h2 = findHomography(img_points,crp_points);
		warpPerspective(frame,frame,h2,size);

		frame = frame - img;

		s = int2str(c);
		c++;
		imwrite("ig" + s + ".jpg", frame);
	}
	imwrite("igempty.jpg", img);
	return 0;
}

