/*
    Jasmine Owens
    CS5330 Computer Vision
    Final Project
    GUI implementation

    This GUI provides sliders and buttons that can be used by a main 
    function for image processing. This GUI does not do any image
    processing itself.
*/


#include "MyGui.hpp"

// ------------------------ Static variables ----------------------- //
/* screenwidth  NOT PORTABLE */
int MyGui::SCR_W = (int) GetSystemMetrics(SM_CXSCREEN);
/* screenheight NOT PORTABLE */
int MyGui::SCR_H = (int) GetSystemMetrics(SM_CYSCREEN);
/* number of program saves */
int MyGui::save_count = 0;

/*  save button */
cv::Rect MyGui::button1 = cv::Rect(0, 0, 150, 50);
/*  reset button */
cv::Rect MyGui::button2 = cv::Rect(150, 0, 150, 50);
/*  button drawer */
cv::Mat3b MyGui::canvas = cv::Mat3b(button1.height, 
                                    button1.width + button2.width, 
                                    cv::Vec3b(0,0,0));


// ---------------------------- Getters ---------------------------- //
/* Get screen width */
int MyGui::scr_w() {return SCR_W;}

/* Get screen height */
int MyGui::scr_h() {return SCR_H;};

/* Get number of program saves */
int MyGui::saves() {return save_count;}

/* Get specified slider value */
int MyGui::get_slider(int slider_number){
    switch (slider_number) {
        case 0:
            return slider_val[0]; // exposure
        case 1:
            return slider_val[1]; // threshold
        case 2:
            return slider_val[2]; // contrast
        case 3:
            return slider_val[3]; // sat
        case 4:
            return slider_val[4]; // blue
        case 5:
            return slider_val[5]; //green
        case 6:
            return slider_val[6]; //red
        case 7:
            return slider_val[7]; //grayscale
        case 8:
            return slider_val[8]; //invert
        case 9:
            return slider_val[9]; //cartoonize
        default:
            return -1;
    }
}


// -------------------------- Constructor -------------------------- //
/*  Initializes current image, display image, and slider values. 
    Note: Constructor only partly sets up GUI. Need to call 
    .window_init() as well */
MyGui::MyGui(char* path, cv::Mat &img) {
    current = img.clone();
    display = img.clone();
    window_name = (std::string) path;
    slider_val[0] = 256; //exposure
    slider_val[1] = 128; //threshold
    slider_val[2] = 128; //contrast
    slider_val[3] = 128; //sat
    slider_val[4] = 128; //blue
    slider_val[5] = 128; //green
    slider_val[6] = 128; //red
    slider_val[7] = 0; //grayscale
    slider_val[8] = 0; //invert
    slider_val[9] = 0; //cartoonize

}


// ------------------------- GUI functions ------------------------- //
/*  Opens image window and control panel with sliders and buttons.*/
int MyGui::window_init(){
    // display photo and scale to screen
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
    size_to_screen(current, display, SCR_W, SCR_H);
    cv::imshow(window_name,  display);

    //control panel 
    cv::namedWindow("Controls", cv::WINDOW_GUI_NORMAL);

    // buttons 
    // based on https://stackoverflow.com/a/33938726
    canvas(button1) = cv::Vec3b(200,100,100);
    cv::putText(canvas(button1), "Save",  // save button
        cv::Point(button1.width*0.3, button1.height*0.7), 
        cv::FONT_HERSHEY_DUPLEX, 0.75, cv::Scalar(0,0,0));
    canvas(button2) = cv::Vec3b(100,200,100);
    cv::putText(canvas(button2), "Reset", // reset button 
        cv::Point(button2.width*0.3, button2.height*0.7), 
        cv::FONT_HERSHEY_DUPLEX, 0.75, cv::Scalar(0,0,0));
    cv::imshow("Controls", canvas);
    // beautify buttons
    cv::rectangle(canvas, button1, cv::Scalar(150, 75, 75), 3);
    cv::rectangle(canvas, button2, cv::Scalar(100, 150, 100), 3);
    // make buttons do stuff
    cv::setMouseCallback("Controls", onMouse, (void*) &current);

    // trackbars
    sprintf( slider[0], "Exposure ", 20); 
    cv::createTrackbar( slider[0], "Controls", 
                        &slider_val[0], 512, onTrackbar);
    sprintf( slider[1], "Threshold ", 20);
    cv::createTrackbar( slider[1], "Controls", 
                        &slider_val[1], 255, onTrackbar);
    sprintf( slider[2], "Contrast ", 20);
    cv::createTrackbar( slider[2], "Controls", 
                        &slider_val[2], 255, onTrackbar);
    sprintf( slider[3], "Saturation ", 20);
    cv::createTrackbar( slider[3], "Controls", 
                        &slider_val[3], 255, onTrackbar);
    sprintf( slider[4], "Blue ", 20);
    cv::createTrackbar( slider[4], "Controls", 
                        &slider_val[4], 255, onTrackbar);
    sprintf( slider[5], "Green ", 20);
    cv::createTrackbar( slider[5], "Controls", 
                        &slider_val[5], 255, onTrackbar);
    sprintf( slider[6], "Red ", 20);
    cv::createTrackbar( slider[6], "Controls", 
                        &slider_val[6], 255, onTrackbar);
    sprintf( slider[7], "Grayscale ", 20);
    cv::createTrackbar( slider[7], "Controls", 
                        &slider_val[7], 1, onTrackbar);
    sprintf( slider[8], "Invert ", 20);
    cv::createTrackbar( slider[8], "Controls", 
                        &slider_val[8], 1, onTrackbar);
    sprintf( slider[9], "Cartoon ", 20);
    cv::createTrackbar( slider[9], "Controls", 
                        &slider_val[9], 5, onTrackbar);

    return 0;
}

/*  Update GUI image display. */
int MyGui::update(cv::Mat &src) {
    current = src.clone();
    size_to_screen(current, display, SCR_W, SCR_H);
    cv::imshow(window_name, display);

    return 0;
}

/*  Resize display image to fit within computer screen */
int MyGui::size_to_screen(cv::Mat &src, cv::Mat &dst, 
                          int SCR_W, int SCR_H) {
    // if already small do nothing
    if (src.rows <= SCR_W && src.cols <= SCR_H ) {
        return 0;
    }
    // get image relative scale to screen
    double hratio, vratio;
    hratio = 0.99*(SCR_W - 300) / (double) src.cols;
    vratio = 0.9 * SCR_H / (double) src.rows;
    // scale to fit either horizontal or vertical
    if(hratio < vratio) {
        cv::resize(src, dst, cv::Size(), hratio, hratio);
    } else {
        cv::resize(src, dst, cv::Size(), vratio, vratio); 
    }
    return 0;
}


// -------------------- event handlers (private) ------------------- //
/*  This function handles mouse events. Clicking on the left button
    increase the save count so that the main function can save an 
    image. Clicking on the right button will reset the sliders. */
void MyGui::onMouse(int event, int x, int y, int, void* userdata){
    if (event == cv::EVENT_LBUTTONDOWN) {
        if (x > 0 && x < 150 && y > 0 && y < 50) {
            // hilight button and up save count
            cv::rectangle(canvas(button1), button1, 
                          cv::Scalar(100, 50, 50), 3);
            save_count++;

        } else if (x > 150 && x < 300 && y > 0 && y < 50) {  
            // highlight button and reset sliders        
            cv::rectangle(canvas, button2, 
                          cv::Scalar(100, 100, 50), 3);
            cv::setTrackbarPos("Exposure ", "Controls", 256);
            cv::setTrackbarPos("Threshold ", "Controls", 128);
            cv::setTrackbarPos("Contrast ", "Controls", 128);
            cv::setTrackbarPos("Saturation ", "Controls", 128);
            cv::setTrackbarPos("Blue ", "Controls", 128);
            cv::setTrackbarPos("Green ", "Controls", 128);
            cv::setTrackbarPos("Red ", "Controls", 128);
            cv::setTrackbarPos("Grayscale ", "Controls", 0);
            cv::setTrackbarPos("Invert ", "Controls", 0);
            cv::setTrackbarPos("Cartoon ", "Controls", 0);
        }
    } else if (event == cv::EVENT_LBUTTONUP) {
        // dehighlight buttons
        cv::rectangle(canvas, button1, cv::Scalar(150, 75, 75), 3);
        cv::rectangle(canvas, button2, cv::Scalar(100, 150, 100), 3);
    }
    // show the button effects in the control panel
    cv::imshow("Controls", canvas);
    cv::waitKey(1);

    
}

/*  This function does nothing. Image processing is handled by main. */
void MyGui::onTrackbar( int, void* ) {}

