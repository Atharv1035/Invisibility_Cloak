#ifndef INVISIBILITY_CLOAK_HPP
#define INVISIBILITY_CLOAK_HPP
#include <opencv2/opencv.hpp>

using namespace std;

double median(vector<double> vec);

tuple<double, double, double> getMedianPixelValues(cv::Mat img);

#endif