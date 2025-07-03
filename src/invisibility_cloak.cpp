#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

double median(vector<double> vec)
{
    int size = vec.size();
    if (size = 0) return 0;
    sort(vec.begin(),vec.end());
    if (size % 2 == 0)
    {
        return (vec[size/2 -1] + vec[size/2]) / 2.0;
    }
    else
    {
        return vec[size/2];
    }
}

tuple<double,double,double> getMedianPixelValues(cv::Mat img)
{
    vector<double> hue_pix;
    vector<double> saturation_pix;
    vector<double> value_pix;

    for (int i=0; i < img.rows; i++)
    {
        for (int j=0; j < img.cols; j++)
        {
            cv::Vec3b pixel = img.at<cv::Vec3b>(i,j);
            hue_pix.push_back(pixel[0]);
            saturation_pix.push_back(pixel[1]);
            value_pix.push_back(pixel[2]);
        }
    }

    double hue_median = median(hue_pix);
    double saturation_median = median(saturation_pix);
    double value_median = median(value_pix);

    return make_tuple(hue_median, saturation_median, value_median);
}