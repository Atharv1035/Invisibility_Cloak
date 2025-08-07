#include<bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include "invisibility_cloak.hpp"
using namespace std;

cv::Point selectedPoint(-1, -1);
bool clicked = false;

// Mouse callback to store clicked point
void mouseCallback(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        selectedPoint = cv::Point(x, y);
        clicked = true;
    }
}

int main()
{
    cv::VideoCapture video(0);
    if (!video.isOpened()) {
        cerr << "Error: Cannot open webcam.\n";
        return -1;
    }

    int h = 0, s = 0, v = 0;

    cv::Mat bg;
    cout << "Get ready! Background capture will start in 5 seconds...\n";
    cv::waitKey(5000);
    // capture bg and show with temp var
    cout << "Capturing background... stay out of the frame!!\n";
    for (int i = 0; i < 100; i++) {
        cv::Mat temp;
        video.read(temp);
        bg = temp.clone();
        cv::imshow("Background", bg);
        cv::waitKey(30);
    }
    cout << "Background captured successfully.\n";
    cv::destroyWindow("Background");

    cv::namedWindow("Image", cv::WINDOW_NORMAL);
    cv::resizeWindow("Image", 640, 480);
    cv::setMouseCallback("Image", mouseCallback, nullptr);

    while (video.isOpened())
    {
        cv::Mat frame;
        video.read(frame);
        cv::imshow("Image", frame);

        if (cv::waitKey(10) == 'i')
        {
            cout << "Select object to set as cloak...\n";
            clicked = false;
            selectedPoint = {-1, -1};

            while (!clicked && video.isOpened()) {
                video.read(frame);
                cv::imshow("Image", frame);
                if (cv::waitKey(10) == 27) break; // ESC to cancel
            }

            if (clicked && selectedPoint.x >= 0 && selectedPoint.y >= 0) {
                cv::Mat hsv;
                cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
                cv::Vec3b pixel = hsv.at<cv::Vec3b>(selectedPoint);

                h = pixel[0];
                s = pixel[1];
                v = pixel[2];

                cout << " Color selected: H=" << h << ", S=" << s << ", V=" << v << endl;
            } else {
                cerr << " No valid point selected.\n";
                return -1;
            }

            break;
        }
    }

    while (video.isOpened())
    {
        cv::Mat frame, hsv;
        video.read(frame);
        cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

        const int h_buffer = 15;
        const int s_buffer = 80;
        const int v_buffer = 80;

        int lower_h = max(0, h - h_buffer);
        int upper_h = min(180, h + h_buffer); // H range in OpenCV is [0,180]
        int lower_s = max(0, s - s_buffer);
        int upper_s = min(255, s + s_buffer);
        int lower_v = max(0, v - v_buffer);
        int upper_v = min(255, v + v_buffer);

        cv::Scalar lower(lower_h, lower_s, lower_v);
        cv::Scalar upper(upper_h, upper_s, upper_v);

        cv::Mat cloak;
        cv::inRange(hsv, lower, upper, cloak);

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
