/* Jasmine Owens
   CS5330 Computer Vision
   Filters
   filters.cpp

   Implementations for filter class functions

   Updated 3.3.22
*/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/types.hpp>
#include "filters.hpp"

#define PI 3.14159265359

// PRIVATE METHODS
int filters::mod(int arg, int modulo) {
    int result = arg % modulo;
    if (result < 0)
        result *= -1;
    return result;
}

/* horizontal blur component of Gauss filter
   filter used: 1/16 [1 4 6 4 1]
*/
int filters::hGauss( cv::Mat &src, cv::Mat &dst ) {
    dst = src.clone();
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            for (int k = 0; k < src.channels(); k++) {
                // H blur with filter [1 4 6 4 1] 
                dst.at<cv::Vec3b>(i,j).val[k] = (
                    src.at<cv::Vec3b>(i, mod(j - 2, src.cols) ).val[k]
                    + 4*src.at<cv::Vec3b>(i, mod(j - 1, src.cols) ).val[k]
                    + 6*src.at<cv::Vec3b>(i,j).val[k]
                    + 4*src.at<cv::Vec3b>(i, mod(j + 1, src.cols) ).val[k]
                    + src.at<cv::Vec3b>(i, mod(j + 2, src.cols) ).val[k]
                    )/16;
            }
        }
    }

    return 0;
}
/* vertical blur component of Gauss filter
   filter used: 1/16 [1 4 6 4 1]T
*/
int filters::vGauss( cv::Mat &src, cv::Mat &dst ) {
    dst = src.clone();

    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            for (int k = 0; k < src.channels(); k++) {
                // V blur with filter [1 4 6 4 1]T 
                dst.at<cv::Vec3b>(i,j).val[k] = (
                    src.at<cv::Vec3b>( mod(i - 2, src.rows), j).val[k]
                    + 4*src.at<cv::Vec3b>( mod(i - 1, src.rows),j).val[k]
                    + 6*src.at<cv::Vec3b>(i,j).val[k]
                    + 4*src.at<cv::Vec3b>( mod(i + 1, src.rows),j).val[k]
                    + src.at<cv::Vec3b>( mod(i + 2, src.rows),j).val[k]
                    )/16;
            }
        }
    }
    return 0;
}



// PUBLIC METHODS
/* Alternative greyscale output: G channel only
      [Task 4]
   */
int filters::altGray( cv::Mat &src, cv::Mat &dst ) {
   dst = src.clone();

    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            cv::Vec3b intensity = src.at<cv::Vec3b>(i,j);
            for (int k = 0; k < src.channels(); k++) {
                dst.at<cv::Vec3b>(i, j).val[k] = intensity.val[1];
                
            }
        }
    }

    return 0;
}

/* Gaussian Blur Filter: 1/16[1 4 6 4 1] x 1/16 T[1 4 6 4 1]
      e.g. 1/256 times the following matrix:
      1  4  6  4  1
      4 16 24 16  4
      6 24 36 16  6
      4 16 24 16  4
      1  4  6  4  1
      [Task 5]
*/
int filters::blur5x5( cv::Mat &src, cv::Mat &dst ) {
    cv::Mat temp = src.clone();
    dst = src.clone();

    hGauss( src, temp );
    vGauss( temp, dst );

    return 0;
}
/* SobelX Filter: [1 2 1]T x [-1 0 1] x A - unseparated
   -1 0 1
   -2 0 2
   -1 0 1
      [Task 6a]
*/
int filters::sobelX3x3( cv::Mat &src, cv::Mat &dst) {
    dst = src.clone();
    dst.create(src.rows, src.cols, CV_16SC3 );

    for (int i = 1; i < src.rows - 1; i++) {
        for (int j = 1; j < src.cols - 1; j++) {
            for (int k = 0; k < src.channels(); k++) {
                // mat blur
                dst.at<cv::Vec3s>(i,j).val[k] = (
                    -1 * src.at<cv::Vec3b>( i - 1, j - 1 ).val[k]
                    +1 * src.at<cv::Vec3b>( i - 1, j + 1).val[k]
                    -2 * src.at<cv::Vec3b>( i    , j - 1 ).val[k]
                    +2 * src.at<cv::Vec3b>( i    , j + 1 ).val[k]
                    -1 * src.at<cv::Vec3b>( i + 1, j - 1 ).val[k]
                    +1 * src.at<cv::Vec3b>( i + 1, j + 1 ).val[k]
                    )/4;
                    
            }
        }
    }
    return 0;
}
/* SobelY Filter: [1 2 1]T x [-1 0 1] x A - unseparated
      1  2  1
      0  0  0
   -1 -2 -1
      [Task 6b]
*/
int filters::sobelY3x3( cv::Mat &src, cv::Mat &dst) {
    dst = src.clone();
    dst.create(src.rows, src.cols, CV_16SC3 );
    
    for (int i = 1; i < src.rows - 1; i++) {
        for (int j = 1; j < src.cols - 1; j++) {
            for (int k = 0; k < src.channels(); k++) {
                // mat blur
                dst.at<cv::Vec3s>(i,j).val[k] = (
                        1 * src.at<cv::Vec3b>( i - 1, j - 1 ).val[k]
                    +2 * src.at<cv::Vec3b>( i - 1, j     ).val[k]
                    +1 * src.at<cv::Vec3b>( i - 1, j + 1 ).val[k]
                    -1 * src.at<cv::Vec3b>( i + 1, j - 1 ).val[k]
                    -2 * src.at<cv::Vec3b>( i + 1, j     ).val[k]
                    -1 * src.at<cv::Vec3b>( i + 1, j + 1 ).val[k]
                    )/4;

                
            }
        }
    }
    return 0;
}

/* Magnitude Filter: square root of SobelX^2 + SobelY^2
      [Task 7]
*/
int filters::magnitude( cv::Mat &sx, cv::Mat &sy, cv::Mat &dst ) {
   dst.create(sx.rows, sx.cols, CV_8UC3);
   
    for (int i = 0; i < sx.rows; i++) {
        for (int j = 0; j < sx.cols; j++) {
            for (int k = 0; k < sx.channels(); k++) {
                // sqrt of squares of values 
                dst.at<cv::Vec3b>(i,j).val[k] = (
                    sqrt(sx.at<cv::Vec3s>( i, j).val[k]
                            *sx.at<cv::Vec3s>( i, j).val[k]
                            +
                            sy.at<cv::Vec3s>( i, j).val[k]
                            *sy.at<cv::Vec3s>( i, j).val[k]
                            )
                    );

            }
        }
    }
    return 0;
}

/* Quantizes color image to specified level
      [task 8]
*/
int filters::blurQuantize( cv::Mat &src, cv::Mat &dst, int levels ) {
    int b = 255/levels;
    int xTemp = 0;
    int xFinal = 0;

    dst = src.clone();

    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            for (int k = 0; k < src.channels(); k++) {
                // quantize 
                xTemp = src.at<cv::Vec3b>(i,j ).val[k]/b;
                xFinal = xTemp * b;
                dst.at<cv::Vec3b>(i,j).val[k] = xFinal;
            }
        }
    }

    return 0;
}

/* Returns cartoonized image with black background and white edges
      [Task 9]
*/
int filters::cartoon( cv::Mat &src, cv::Mat&dst, int levels, int magThreshold ) {
    cv::Mat sx = src.clone();
    cv::Mat sy = src.clone();
    cv::Mat temp = src.clone();

    dst = src.clone();
    

    sobelX3x3(src, sx);
    sobelY3x3(src, sy);
    magnitude(sx, sy, temp);
    //blur5x5(dst, temp);
    blurQuantize(src, dst, levels);

    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            for (int k = 0; k < src.channels(); k++) {
                // remove thresholds 
                if (temp.at<cv::Vec3b>(i,j).val[k] > magThreshold) {
                dst.at<cv::Vec3b>(i,j).val[k] = 0;
                }
            }
        }
    }

    return 0;
}


/* Inverts 0 to 255 per color channel,
   sets everything else to 0.
   Designed to work with cartoon
      [Task 10]
*/
int filters::maxSat(cv::Mat &src, cv::Mat &dst) {
    dst = src.clone();
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            for (int k = 0; k < src.channels(); k++) {
                // invert colors 
                if (dst.at<cv::Vec3b>(i,j).val[k] > 128)
                dst.at<cv::Vec3b>(i,j).val[k] = 255;
                else 
                dst.at<cv::Vec3b>(i,j).val[k] = 0;
            
            }
        }
    }
    return 0;
}
/* Inverts 0 to 255 per color channel,
   sets everything else to 0.
   Designed to work with cartoon
      [Task 10]
*/
int filters::invert(cv::Mat &src, cv::Mat &dst) {
    dst = src.clone();
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            for (int k = 0; k < src.channels(); k++) {
                // invert colors 
                dst.at<cv::Vec3b>(i,j).val[k] = 255 -dst.at<cv::Vec3b>(i,j).val[k];
            
            }
        }
    }
    return 0;
}

/* Given a color image, creates a binary image in the destination 
   based on the input thresholds for B, G, and R. RGB values less than
   the specified threshold are set to foreground (i.e., dark colors).
   Otherwise, they are set to background (light colors). Destination is 
   saved as openCV Mat of type CV_8UC1.
*/
int filters::binary(cv::Mat &src, cv::Mat &dst,
                       int tb, int tg, int tr) {
    
    cv::Mat temp;
    temp = src.clone();
    dst = temp.clone();
    dst.create(src.rows, src.cols, CV_8UC1 );

    blur5x5(src, temp); 


    for (int i = 0; i < temp.rows; i++) {
        for (int j = 0; j < temp.cols; j++) {
            for (int k = 0; k < temp.channels(); k++) {
                if(temp.at<cv::Vec3b>(i,j).val[0] < tb || // blue thr
                temp.at<cv::Vec3b>(i,j).val[1] < tg || // green thr
                temp.at<cv::Vec3b>(i,j).val[2] < tr    // red thr
                ) {
                    dst.at<uchar>(i,j) = 255;  // set to foreground
                } else {
                    dst.at<uchar>(i,j) = 0;    // set to background
                }
            }
        }
    }

    return 0;

}

/* Given an source and destination image, turns a foreground source
   pixel to background in the destination if at least one neighbor 
   is in the background. Neighborhoods are 8-connected. Source matrix
   is assumed to be a binary image.

   Process repeats specified number of times (rounds)
*/
int filters::shrink(cv::Mat &src, cv::Mat &dst, int rounds) {
    if(rounds < 1)
        return 1;

    cv::Mat temp;
    temp = src.clone();
    temp.create(src.rows, src.cols, CV_8UC1);

    dst = temp.clone();
    dst.create(src.rows, src.cols, CV_8UC1 );


    for(int k = 0; k < rounds; k++) {
      for (int i = 1; i < temp.rows - 1; i++) {
            for (int j = 1; j < temp.cols - 1; j++) {

                if(temp.at<uchar>(i, j) == 255 && // in foreground 
                (temp.at<uchar>(i - 1, j - 1) == 0 ||   // NE 
                    temp.at<uchar>(i - 1, j) == 0 ||       // N 
                    temp.at<uchar>(i - 1, j + 1) == 0 ||   // NW
                    temp.at<uchar>(i, j - 1) == 0 ||       // E 
                    temp.at<uchar>(i, j + 1) == 0 ||       // W
                    temp.at<uchar>(i + 1, j - 1) == 0 ||   // SE 
                    temp.at<uchar>(i + 1, j) == 0 ||       // S 
                    temp.at<uchar>(i + 1, j + 1) == 0      // SW
                    )
                ) {
                    dst.at<uchar>(i, j) = 0; // change to background
                } else {
                    dst.at<uchar>(i, j) = temp.at<uchar>(i, j);
                }

            }
        }

    temp = dst.clone();

   }

   return 0;
}

/* Given an source and destination image, turns a background source
   pixel to foreground in the destination if at least one neighbor 
   is in the foreground. Neighborhoods are 8-connected. Source matrix
   is assumed to be a binary image.

   Process repeats specified number of times (rounds)
*/
int filters::grow(cv::Mat &src, cv::Mat &dst, int rounds) {
    if(rounds < 1)
        return 1;

    cv::Mat temp;
    temp = src.clone();
    temp.create(src.rows, src.cols, CV_8UC1);

    dst = src.clone();
    dst.create(src.rows, src.cols, CV_8UC1 );


    for(int k = 0; k < rounds; k++) {
        for (int i = 1; i < temp.rows - 1; i++) {
            for (int j = 1; j < temp.cols - 1; j++) {
                if(temp.at<uchar>(i, j) == 0 && // in background 
                (temp.at<uchar>(i - 1, j - 1) == 255 ||   // NE 
                    temp.at<uchar>(i - 1, j) == 255 ||       // N 
                    temp.at<uchar>(i - 1, j + 1) == 255 ||   // NW
                    temp.at<uchar>(i, j - 1) == 255 ||       // E 
                    temp.at<uchar>(i, j + 1) == 255 ||       // W
                    temp.at<uchar>(i + 1, j - 1) == 255 ||   // SE 
                    temp.at<uchar>(i + 1, j) == 255 ||       // S 
                    temp.at<uchar>(i + 1, j + 1) == 255      // SW
                    )
                ) {
                dst.at<uchar>(i, j) = 255; // change to foreground
                } else {
                dst.at<uchar>(i, j) = temp.at<uchar>(i, j);
                }
            }
        }
        temp = dst.clone();

    }

    return 0;
}

/* Assuming an input binary image, turns a source pixel to foreground 
   in the destination image if it is surrounded by at least 4 
   foreground neighbors. Neighborhoods are 8-connected.

   Process repeats specified number of times (rounds)
*/
int filters::median(cv::Mat &src, cv::Mat &dst, int rounds) {
    if(rounds < 1)
        return 1;

    cv::Mat temp;
    temp = src.clone();
    temp.create(src.rows, src.cols, CV_8UC1);

    dst = src.clone();
    dst.create(src.rows, src.cols, CV_8UC1 );

    int count;


    for(int k = 0; k < rounds; k++) {
        for (int i = 1; i < temp.rows - 1; i++) {
            for (int j = 1; j < temp.cols - 1; j++) {
                count = 0;
                if(temp.at<uchar>(i - 1, j - 1) == 255)      // NE
                count++;
                if(temp.at<uchar>(i - 1, j) == 255)       // N 
                count++;
                if(temp.at<uchar>(i - 1, j + 1) == 255)   // NW
                count++;
                if(temp.at<uchar>(i, j - 1) == 255)       // E 
                count++;
                if(temp.at<uchar>(i, j + 1) == 255)       // W
                count++;
                if(temp.at<uchar>(i + 1, j - 1) == 255)   // SE 
                count++;
                if(temp.at<uchar>(i + 1, j) == 255)       // S 
                count++;
                if(temp.at<uchar>(i + 1, j + 1) == 255)   // SW
                count++;
                
                if(count > 3) {
                dst.at<uchar>(i, j) = 255; // change to foreground
                } else {
                dst.at<uchar>(i, j) = temp.at<uchar>(i, j);
                }
            }
        }
        temp = dst.clone();

    }

    return 0;
}


/* Finds the N largest regions of the image, saves the region number
   of the N largest regions in order to a vector (regionOrder), and 
   produces a color image with the N largest regions shown. Colors 
   cycle through BGR.
*/
int filters::region_finder(cv::Mat &src, cv::Mat &dst, 
      std::vector<int> &regionOrder, cv::Mat &labels, 
      cv::Mat &stats, int N) {

    int regions = stats.rows;
    int regNum;
    int channel;  

    int bySize[regions] = {0};
    int order[regions] = {0};
    regionOrder.assign(N + 1, 0);

    for(int i = 0; i < regions; i++) {
        bySize[i] = stats.at<int>(i, 4);
        order[i] = i;
    }

    // sort variables
    int max_idx; 
    int temp_i;
    // modified selection sort (from Geeks to Geeks page
    // https://www.geeksforgeeks.org/selection-sort/)

    // One by one move boundary of unsorted subarray 
    // Only need N matches, so stop after N
    for (int i = 1; i < N + 1; i++) { 
        // Find the max element in unsorted array 
        max_idx = i; 
        for (int j = i + 1; j < regions; j++) {
            if (bySize[j] > bySize[max_idx] ) {
                max_idx = j; 
            }
        }
   
        // Swap the found minimum element with the first element
        temp_i = bySize[max_idx];
        bySize[max_idx] = bySize[i];
        bySize[i] = temp_i;
        // swap region index
        temp_i = order[max_idx];
        order[max_idx] = order[i];
        order[i] = temp_i;
        regionOrder[i] = order[i];

    }

    // populate image with colors by region
    for(int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            regNum = labels.at<int>(i,j);
         
            for(int k = 1; k < N + 1; k++) {
                if(regNum == order[k]) {
                    channel = (k - 1)%3;
                    break;
                } else {
                    channel = -1;
                }
            }
          
          
            if(channel == 0) {
                dst.at<cv::Vec3b>(i,j).val[0] = 255;
                dst.at<cv::Vec3b>(i,j).val[1] = 0;
                dst.at<cv::Vec3b>(i,j).val[2] = 0;
            } else if (channel == 1) {
                dst.at<cv::Vec3b>(i,j).val[0] = 0;
                dst.at<cv::Vec3b>(i,j).val[1] = 255;
                dst.at<cv::Vec3b>(i,j).val[2] = 0;
            } else if (channel == 2) {
                dst.at<cv::Vec3b>(i,j).val[0] = 0;
                dst.at<cv::Vec3b>(i,j).val[1] = 0;
                dst.at<cv::Vec3b>(i,j).val[2] = 255;
            } else {
                dst.at<cv::Vec3b>(i,j).val[0] = 0;
                dst.at<cv::Vec3b>(i,j).val[1] = 0;
                dst.at<cv::Vec3b>(i,j).val[2] = 0; 
            }

        }
    }
   
    return 0;

}

/* Given src, dst, regions sorted by size, angles, and CCA centroids, prints the
   principal and secondary axes on the dst image.
*/
int filters::principal_axis(cv::Mat &src, cv::Mat &dst, 
                        std::vector<int> &regionOrder, 
                        std::vector<double> angles, cv::Mat &centroids) {
   dst = src.clone();

   int r;
   cv::Point centroid;
   cv::Point pAxis;
   cv::Point pAxis_o;
   cv::Point qAxis;
   cv::Point qAxis_o;

   // draw principal and secondary axes
   for(int k = 1; k < regionOrder.size(); k++) {

      //calculate axes segment points
      centroid.x = centroids.at<double>(regionOrder[k], 1);
      centroid.y = centroids.at<double>(regionOrder[k], 0);
      pAxis.x = centroid.x + 100*sin(angles[k]);
      pAxis.y = centroid.y + 100*cos(angles[k]);
      pAxis_o.x = centroid.x - 100*sin(angles[k]);
      pAxis_o.y = centroid.y - 100*cos(angles[k]);
      qAxis.x = centroid.x + 50*sin(angles[k] + PI/2);
      qAxis.y = centroid.y + 50*cos(angles[k] + PI/2);
      qAxis_o.x = centroid.x - 50*sin(angles[k] + PI/2);
      qAxis_o.y = centroid.y - 50*cos(angles[k] + PI/2);

      //draw axes
      line(dst, cv::Point((int)pAxis_o.y, (int)pAxis_o.x), 
            cv::Point((int)pAxis.y, (int)pAxis.x), 
            cv::Scalar(255, 255, 255), 1);
      line(dst, cv::Point((int)qAxis_o.y, (int)qAxis_o.x), 
            cv::Point((int)qAxis.y, (int)qAxis.x), 
            cv::Scalar(128, 128, 128), 1);


   }

   

   return 0;


}

/* Prints the oriented bounding box on the image, given source, destination, and corners
*/
int filters::o_box(cv::Mat &src, cv::Mat &dst, std::vector<int> &corners) {
   dst = src.clone();
   int n = corners.size()/8;
   cv::Point c1;
   cv::Point c2;
   cv::Point c3;
   cv::Point c4;

   for(int i = 1; i < n; i++) {
    
        c1.x = corners[8*i];        // xmin
        c1.y = corners[8*i + 1];    // ymin
        c2.x = corners[8*i + 2];    // xmin
        c2.y = corners[8*i + 3];    // ymax
        c3.x = corners[8*i + 4];    // xmax
        c3.y = corners[8*i + 5];    // ymin
        c4.x = corners[8*i + 6];    // xmax
        c4.y = corners[8*i + 7];    // ymax
        line(dst, c1, c2, cv::Scalar(128, 128, 128), 1);
        line(dst, c2, c3, cv::Scalar(128, 128, 128), 1);
        line(dst, c3, c4, cv::Scalar(128, 128, 128), 1);
        line(dst, c4, c1, cv::Scalar(128, 128, 128), 1);

        

    }

    return 0;

}


// ========== FINAL PROJECT FILTERS ===========

/*  Given a color image, a destination, an amount, and a threshold, this function 
    moves the color image value towards or away from the thresholded value by the
    specified amount. */
int filters::contrast(cv::Mat &src, cv::Mat &dst, int amount, int threshold) {
    amount = amount - 128; // NOTE THIS IS TO SCALE GUI
    if(amount == 0)
        return 0;
    else if(amount > 128)
        amount = 128;
    else if(amount < -128)
        amount = -128;

    dst = src.clone();
    int val;

    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            for (int k = 0; k < src.channels(); k++) {
                int val = dst.at<cv::Vec3b>(i, j).val[k];
                if(amount > 0) {
                    if(val >= threshold) {          // over threshold
                        if(val + amount > 255 )
                            dst.at<cv::Vec3b>(i,j).val[k] = 255;
                        else
                            dst.at<cv::Vec3b>(i, j).val[k] = val + amount;
                    } else {                        // under threshold
                        if(val - amount < 0)
                            dst.at<cv::Vec3b>(i,j).val[k] = 0;
                        else
                            dst.at<cv::Vec3b>(i, j).val[k] = val - amount;
                    }
                } else {
                    if(val >= threshold) {                  // over threshold
                        if( val + amount < threshold )
                            dst.at<cv::Vec3b>(i,j).val[k] = threshold;
                        else
                            dst.at<cv::Vec3b>(i, j).val[k] = val + amount;
                    } else {                                // under threshold
                        if( val - amount > threshold )
                            dst.at<cv::Vec3b>(i,j).val[k] = threshold;
                        else
                            dst.at<cv::Vec3b>(i, j).val[k] = val - amount;
                    }
                }

            }
        }
    }

    return 0;
}

/*  Given a color image, a destination, and an amount, this function increases or 
    decreases all color channel values in the image. */
int filters::exposure(cv::Mat &src, cv::Mat &dst, int amount){
    amount = amount - 256;
    if(amount == 0)
        return 0;
    
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            for (int k = 0; k < src.channels(); k++) {
                int val = dst.at<cv::Vec3b>(i, j).val[k];

                if(val + amount > 255 )
                    dst.at<cv::Vec3b>(i,j).val[k] = 255;
                else if(val + amount < 0) 
                    dst.at<cv::Vec3b>(i,j).val[k] = 0;
                else
                    dst.at<cv::Vec3b>(i, j).val[k] = val + amount;
            }
        }
    }
    return 0;
}

/*  Given a color image, a destination, and an amount, this function converts the 
    image color space to HLS, increases or decreases the saturation value by the amount,
    the converts the color space back to BGR. */
int filters::saturation(cv::Mat &src, cv::Mat &dst, int amount) {
    dst = src.clone();
    amount = amount - 128;
    if(amount == 0)
        return 0;

    // convert to HSL
    cv::cvtColor(src, dst, cv::COLOR_BGR2HLS);

    double factor = (double) amount;
    double sat;
    sat = dst.at<cv::Vec3b>(100, 100).val[2];
 
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            sat = dst.at<cv::Vec3b>(i, j).val[2];

            // adjust sat
            if (factor + sat > 255.0) {
                sat = 1.0;
            } else if (factor + sat < 0) {
                sat = 0.0;
            } else {
                sat = sat + factor;
            }

            //assign
            dst.at<cv::Vec3b>(i, j).val[2] = sat;

        }
    }
    
    // back to BGR
    cv::cvtColor(dst, dst, cv::COLOR_HLS2BGR);
    return 0;
}

/*  Given a color image, a destination, a channel number, and an amount, this 
    function increases or decreases all values in the specified color channel by 
    the specified amount */
int filters::color(cv::Mat &src, cv::Mat &dst, int channel, int amount) {
    amount = amount - 128;
    if(amount == 0)
        return 0;
    if(channel < 0 || channel > 2) {
        printf("Invalid color channel. Use 0-3\n");
        return 1;
    }
        
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            int k  = channel;
            int val = dst.at<cv::Vec3b>(i, j).val[k];
            if(val + amount > 255 )
                dst.at<cv::Vec3b>(i,j).val[k] = 255;
            else if(val + amount < 0) 
                dst.at<cv::Vec3b>(i,j).val[k] = 0;
            else
                dst.at<cv::Vec3b>(i, j).val[k] = val + amount;
            
        }
    }
    return 0;
}