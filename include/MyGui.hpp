/*
    Jasmine Owens
    CS5330 Computer Vision
    Final Project
    GUI header file

    Declarations for MyGui. Docstring in implementation file.

*/

#ifndef MYGUI_H
#define MYGUI_H

#include <windows.h>  // NOT PORTABLE

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>

#define TRACKBARS 10

class MyGui {
    public:
        // getters
        int scr_w();
        int scr_h();
        int saves();
        int get_slider(int slider_number);

        MyGui(char* path, cv::Mat &img);
        
        int window_init();
        int update(cv::Mat &src);
        int size_to_screen(cv::Mat &src, cv::Mat &dst, int SCR_W, int SCR_H);

    private:
        // image variables     
        std::string window_name; // image path
        cv::Mat current;         // current image (fullsize)        
        cv::Mat display;         // display image

        /* static variables (screen dimensions and buttons) */
        static int SCR_W;   // NOT PORTABLE
        static int SCR_H;   // NOT PORTABLE
        static int save_count;
        static cv::Rect button1;
        static cv::Rect button2;
        static cv::Mat3b canvas;
        // slider variables
        char slider[TRACKBARS][20]; // slider names
        int slider_val[TRACKBARS];  // slider values

        // event handlers (functions)
        static void onMouse( int event, int x, int y, int, void* );
        static void onTrackbar(int event, void*);

};

#endif /* MYGUI_H */
