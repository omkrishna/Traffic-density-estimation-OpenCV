/* 
Subtask2- Task 1 - C0P290. Semester 2, 2020-21
Using Background Subtractor and Optical Flow to calculate Queue and Dynamic density of vehicles using traffic camera's video as input

Authors - Harshita(2019CS10357) & Om Krishna(2019CS10272)
*/

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>

#include <iostream>
#include <fstream>
#include <chrono>

#include <pthread.h>

using namespace cv;
using namespace std;
using namespace std::chrono;

//ofstream MyFile("out.csv");
ofstream MyTextFile("2.txt");
float q_density_avg = 0;
Mat fgMask;

void *myBackgroundSubtractor(void *threadarg);
Ptr<BackgroundSubtractor> backSubt = createBackgroundSubtractorMOG2();

struct thread_data
{
    Mat frame;
};

int main(int argc, char **argv)
{
    auto start = high_resolution_clock::now();
    int c = 0;
    VideoCapture cap(argv[1]);
    if (!cap.isOpened())
    {
        cout << "Err : Couldnt read the video file. Check the path/extension" << endl;
        return -1;
    }

    Mat img = imread("background.png");
    if (!img.data)
    {
        cout << "Err : Couldnt read the image file. Check the path/extension" << endl;
        return -1;
    }

    Mat img_cropped;
    Mat frame;

    float dy_pixels, dy_density, pixels, nonZeroPixels, q_density;

    vector<Point2f> img_points;
    vector<Point2f> crp_points;

    cvtColor(img, img, COLOR_BGR2GRAY);

    //cropping background.png to create initial fgMask
    //Points start at top-left and go clockwise
    img_points.push_back(Point2f(937, 275));
    img_points.push_back(Point2f(1290, 267));
    img_points.push_back(Point2f(1535, 1047));
    img_points.push_back(Point2f(579, 1053));

    crp_points.push_back(Point2f(0, 0));
    crp_points.push_back(Point2f(400, 0));
    crp_points.push_back(Point2f(400, 800));
    crp_points.push_back(Point2f(0, 800));

    //Finding the homography matrix and using it for perspective correction
    Size size(400, 800);
    Mat h2 = findHomography(img_points, crp_points);
    warpPerspective(img, img_cropped, h2, size);

    backSubt->apply(img_cropped, fgMask, 0);

    pthread_t t1;
    pthread_t t2;
    
    

    Mat frame2;
  

    while (1)
    {
        bool bSuccess = cap.read(frame);
        bool bSuccess2 = cap.read(frame2);
       
        if (!bSuccess2)
        {
            cout << "Fin" << endl;
            break;
        }
        else
        {
            struct thread_data fr;
            fr.frame = frame;
            c++;
            pthread_create(&t1, NULL, myBackgroundSubtractor, (void *)&fr);

            //writing the averaged queue & dynamic density per second (15 frames)
            if (c % 15 == 0)
            {
                //MyFile << (c / 15) << "," << q_density_avg / 15 << "," << dy_density_avg / 15 << endl;

                MyTextFile << (c / 15) << "," << q_density_avg / 15 << endl;

                cout << (c / 15) << "," << q_density_avg / 15 << endl;

                q_density_avg = 0;
            }

            struct thread_data fr2;
            fr2.frame = frame2;
            c++;
            pthread_create(&t2, NULL, myBackgroundSubtractor, (void *)&fr2);

            //writing the averaged queue & dynamic density per second (15 frames)
            if (c % 15 == 0)
            {
                //MyFile << (c / 15) << "," << q_density_avg / 15 << "," << dy_density_avg / 15 << endl;

                MyTextFile << (c / 15) << "," << q_density_avg / 15 << endl;

                cout << (c / 15) << "," << q_density_avg / 15 << endl;

                q_density_avg = 0;
            }

              

            
            

            pthread_join(t1, NULL);
            pthread_join(t2, NULL);
            
            
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Time:" << duration.count() << endl;
    MyTextFile << "Time:" << duration.count() << endl;
    return 0;
    //MyFile.close();
    MyTextFile.close();
}

void *myBackgroundSubtractor(void *threadarg)
{
    struct thread_data *my_data;
    my_data = (struct thread_data *)threadarg;
    vector<Point2f> frame_p;
    vector<Point2f> crframe_p;
    Size size(400, 800);

    Mat cropped_frame;

    Mat h;

    cvtColor(my_data->frame, my_data->frame, COLOR_BGR2GRAY);

    frame_p.push_back(Point2f(968, 254));
    frame_p.push_back(Point2f(1308, 260));
    frame_p.push_back(Point2f(1551, 1065));
    frame_p.push_back(Point2f(587, 1065));

    crframe_p.push_back(Point2f(0, 0));
    crframe_p.push_back(Point2f(400, 0));
    crframe_p.push_back(Point2f(400, 800));
    crframe_p.push_back(Point2f(0, 800));

    h = findHomography(frame_p, crframe_p);
    warpPerspective(my_data->frame, cropped_frame, h, size);

    backSubt->apply(cropped_frame, fgMask, 0);
    //threshold(fgMask, fgMask, 128, 255, cv::THRESH_BINARY);

    float pixels, nonZeroPixels, q_density;

    pixels = fgMask.rows * fgMask.cols;
    nonZeroPixels = countNonZero(fgMask);
    q_density = nonZeroPixels / pixels;
    q_density_avg += q_density;

    return NULL;
}