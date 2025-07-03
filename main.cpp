#include<bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include "invisibility_cloak.hpp"
using namespace std;
int main()
{
    cv::VideoCapture video(0);
    int h = 0, s = 0, v = 0;

    cv::Mat bg;
    cout<<"Capturing background... stay out of the frame!!\n";
    for (int i=0;i<100;i++)
    {
        cv::Mat temp;
        video.read(temp);
        //cv::flip(temp,temp,1);
        bg = temp.clone();
        cv::imshow("Background", bg);
        cv::waitKey(30);
    }
    cv::destroyWindow("Background");

    while (video.isOpened())
    {
        
        cv::Mat frame;
        video.read(frame);
        cv::namedWindow("Image", cv::WINDOW_NORMAL);
        cv:: resizeWindow("Image", 640, 480);
        cv::imshow("Image", frame);

        if (cv::waitKey(10) =='i')
        {
            cv::Rect bbox = cv::selectROI("Image", frame, false, false);
            cv::Mat hsv;
            cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
            cv::Mat obj = hsv(cv::Rect(bbox.x, bbox.y, bbox.width, bbox.height));
            tuple<double, double, double> medians = getMedianPixelValues(obj);
            h = get<0>(medians);
            s = get<1>(medians);
            v = get<2>(medians);
            break;
        }
    }
    //cv::destroyWindow("Image");

    while (video.isOpened())
    {
        cv::Mat frame, hsv;
        video.read(frame);
        cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

        cv::Scalar lower(h-5, max(0, s-50), max(0,v-50));
        cv::Scalar upper(h+5, max(s+50,255), max(v+50,255));

        cv::Mat cloak;
        cv::inRange(hsv, lower, upper, cloak);

        // cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::size(3,3));
        // cv::morphologyEx(cloak, cloak, cv::MORPH_OPEN, kernel);
        // cv::morphologyEx(cloak, cloak, cv::MORPH_DILATE, kernel);

        cv::Mat inv_mask, cloak_area, visible, final_output;
        cv::bitwise_not(cloak, inv_mask);
        bg.copyTo(cloak_area, cloak);
        frame.copyTo(visible, inv_mask);
        final_output = cloak_area + visible;

        cv::imshow("Invisibility Cloak", final_output);
        if (cv::waitKey(10) == 'x') break;
    }
    video.release();
    cv::destroyAllWindows();
    return 0;
}