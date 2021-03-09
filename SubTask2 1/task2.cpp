#include <opencv4/opencv2/opencv.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include "opencv2/bgsegm.hpp"


#include <iostream>
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

int main(int argc, char** argv)
{
	string s;

	VideoCapture cap(argv[1]);
	if (!cap.isOpened())  
	{
		cout << "Err : Couldnt read the video file. Check the path/extension" << endl;
		return -1;
	}

	Mat img = imread("background.png");
    if(!img.data)
	{
        cout << "Err : Couldnt read the image file. Check the path/extension" << endl;
        return -1;
    }

    cvtColor(img,img,COLOR_BGR2GRAY);

    vector<Point2f> img_points;
    vector<Point2f> crp_points;

    Mat img_cropped;

    img_points.push_back(Point2f(937,275));
    img_points.push_back(Point2f(1290,267));
    img_points.push_back(Point2f(1535,1047));
    img_points.push_back(Point2f(579,1053));

    //Points start at top-left and go clockwise
    crp_points.push_back(Point2f(0,0));
    crp_points.push_back(Point2f(400,0));
    crp_points.push_back(Point2f(400,800));
    crp_points.push_back(Point2f(0,800));

    //Finding the homography matrix and using it for perspective correction
    Size size(400,800);
    Mat h2 = findHomography(img_points,crp_points);
    warpPerspective(img,img_cropped,h2,size);

    //Displaying output images to the user
    imwrite("Empty.jpg",img_cropped);

    while (1)
	{
		Mat frame;
        Mat cropped_frame;
		bool bSuccess = cap.read(frame); // read a new frame from video

		if (!bSuccess) { cout << "Fin" << endl; break; }

		cvtColor(frame,frame,COLOR_BGR2GRAY);

		vector<Point2f> frame_p;
        vector<Point2f> crframe_p;

        frame_p.push_back(Point2f(314,95));
        frame_p.push_back(Point2f(435,95));
        frame_p.push_back(Point2f(529,363));
        frame_p.push_back(Point2f(187,357));

        crframe_p.push_back(Point2f(0,0));
        crframe_p.push_back(Point2f(400,0));
        crframe_p.push_back(Point2f(400,800));
        crframe_p.push_back(Point2f(0,800));

        Mat h = findHomography(frame_p,crframe_p);
        warpPerspective(frame,cropped_frame,h,size);

		cropped_frame = cropped_frame - img_cropped;

		s = int2str(c);
		c++;
		imwrite("ig" + s + ".jpg", cropped_frame);
	}

    return 0;
}