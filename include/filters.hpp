/* Jasmine Owens
   CS5330 Computer Vision
   Filters header
   filters.hpp

   Definitions for filter class functions
*/
#ifndef FILTERS_H
#define FILTERS_H

#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>

#include <iostream>
#include <string>
#include <vector>

/* Custom filter options
*/
class filters {
    public:
        // Project 1 filters

        int altGray( cv::Mat &src, cv::Mat &dst );
        int blur5x5( cv::Mat &src, cv::Mat &dst );
        int sobelX3x3( cv::Mat &src, cv::Mat &dst);
        int sobelY3x3( cv::Mat &src, cv::Mat &dst);
        int magnitude( cv::Mat &sx, cv::Mat &sy, cv::Mat &dst );
        int blurQuantize( cv::Mat &src, cv::Mat &dst, int levels );
        int cartoon( cv::Mat &src, cv::Mat&dst, int levels, 
                     int magThreshold );
        int maxSat(cv::Mat &src, cv::Mat &dst);
        int invert(cv::Mat &src, cv::Mat &dst);


        //Project 3 filters

        int binary(cv::Mat &src, cv::Mat &dst, int tb, int tg, int tr);
        int shrink(cv::Mat &src, cv::Mat &dst, int rounds);
        int grow(cv::Mat &src, cv::Mat &dst, int rounds);
        int median(cv::Mat &src, cv::Mat &dst, int rounds);
        int region_finder(cv::Mat &src, cv::Mat &dst, 
            std::vector<int> &regionOrder, 
            cv::Mat &labels, cv::Mat &stats, int N);
        int principal_axis(cv::Mat &src, cv::Mat &dst, 
                        std::vector<int> &regionOrder, 
                        std::vector<double> angles, cv::Mat &centroids);
        int o_box(cv::Mat &src, cv::Mat &dst, std::vector<int> &corners);


        // final project filters

        int contrast(cv::Mat &src, cv::Mat &dst, int factor, int threshold);
        int exposure(cv::Mat &src, cv::Mat &dst, int amount);
        int saturation(cv::Mat &src, cv::Mat &dst, int amount);
        int color(cv::Mat &src, cv::Mat &dst, int channel, int amount);
    
    private:
        int mod(int arg, int modulo);
        int hGauss( cv::Mat &src, cv::Mat &dst );
        int vGauss( cv::Mat &src, cv::Mat &dst );
};

#endif /* FILTERS_H */