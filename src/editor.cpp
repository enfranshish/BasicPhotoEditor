/* 
    Jasmine Owens
    CS5330 Computer Vision
    Final Project Main

    This basic photo editor loads an image from argv[] and adds effect filters 
    based on input from an accompanying GUI.
*/
#include <iostream> 
#include <string> 
#include <string.h> 
#include <sstream> 

#include "filters.hpp"
#include "MyGui.hpp"

#define MAX_STRING 100
#define ESC 27

/* Main: argv[] shoud be the path to the image file including the filename */
int main(int argc, char* argv[]) {
    if(argc < 2){
        printf("No image path provided.\n");
        return 0;
    }
    // get image
    char path[MAX_STRING];
    strcpy(path, argv[1] );
    cv::Mat img = cv::imread(path); 

    // Checking if image has been loaded
	if(img.empty()){
		std::cout <<"could not read the image "<< img << std::endl;
		return 1;
	}

    // initialize GUI and filter
    MyGui editor = MyGui(path, img);
    cv::Mat dst;
    filters filter;
    editor.window_init();

    // editing loop
    int saves = 0;
    while(1) {
        // check for gui window close
        if (cv::getWindowProperty("Controls", cv::WND_PROP_VISIBLE) < 1 ||
            cv::getWindowProperty(path, cv::WND_PROP_VISIBLE) < 1
        )        
            break;

        // reload original image
        dst = img.clone();
        // if slider is not in original position, add effect to image
        if(editor.get_slider(0) != 256)
            filter.exposure(dst, dst, editor.get_slider(0));
        if(editor.get_slider(2) != 128)
            filter.contrast(dst, dst, editor.get_slider(2), editor.get_slider(1));
        if(editor.get_slider(3) != 128)
            filter.saturation(dst, dst, editor.get_slider(3));
        if(editor.get_slider(4) != 128)
            filter.color(dst, dst, 0, editor.get_slider(4));
        if(editor.get_slider(5) != 128)
            filter.color(dst, dst, 1, editor.get_slider(5));
        if(editor.get_slider(6) != 128)
            filter.color(dst, dst, 2, editor.get_slider(6));
        if(editor.get_slider(7) != 0)
            filter.altGray(dst, dst);
        if(editor.get_slider(8) != 0)
            filter.invert(dst, dst);
        if(editor.get_slider(9) != 0)
            filter.cartoon(dst, dst, 6, 8*editor.get_slider(9) );
        // save image
        if(saves != editor.saves()) {
            std::string temp = path;
            temp = temp.substr(0, temp.length() - 4);
            temp.append("(");
            cv::imwrite( temp + std::to_string(saves++) + ").png" , dst);
        }

        // display edited image
        editor.update(dst);

        // checks for GUI input
        cv::pollKey();
         
    }

    
    return 0;
}

