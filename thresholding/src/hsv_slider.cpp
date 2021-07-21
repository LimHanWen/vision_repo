#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

// ------------------------------------------------------------------------------------------------------------------------------------------------------------
// Start

//Intialise
cv::Mat hsv , original_colour_image , mask, result;

// Load Image
std::string imageName("/home/mtrn4230/mp_repos/vision_repo/thresholding/src/Solitare1-crop2.jpg");
cv::Mat original_colour_image  = cv::imread(imageName, cv::IMREAD_COLOR ); // Load an image

//Create a window
cv::namedWindow( hsv_window, cv::WINDOW_AUTOSIZE ); // Create a window to display results
cv::resizeWindow( hsv_window, 900, 700);

//Create trackbars
cv::createTrackbar( HMin, hsv_window, 0, 179, nothing );
cv::createTrackbar( SMin, hsv_window, 0, 255, nothing );
cv::createTrackbar( VMin, hsv_window, 0, 255, nothing );
cv::createTrackbar( HMax, hsv_window, 0, 179, nothing );
cv::createTrackbar( SMax, hsv_window, 0, 255, nothing );
cv::createTrackbar( VMax, hsv_window, 0, 255, nothing );

//Set default values for Max HSV trackbars
cv::setTrackbarPos( HMax, hsv_window, 179);
cv::setTrackbarPos( SMax, hsv_window, 255);
cv::setTrackbarPos( VMax, hsv_window, 255);

// Intialise HSV min/max values
int hMin = 0;
int sMin = 0;
int vMin = 0;
int hMax = 0;
int sMax = 0;
int vMax = 0;

int phMin = 0;
int psMin = 0;
int pvMin = 0;
int phMax = 0;
int psMax = 0;
int pvMax = 0;



// end
// ------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;

cv::Mat original_rgb_image, thresholded_image;
std::string window_name("Threshold Demo");
std::string trackbar_type("Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted");
std::string trackbar_value("Value");

// callback function for the slider. It requries signature of int, void* even if these are unused
static void threshold_demo( int trackbarPos, void* userData ) {
     
     //Thresholding types:
     //0: Binary
     //1: Binary Inverted
     //2: Threshold Truncated
     //3: Threshold to Zero
     //4: Threshold to Zero Inverted
    
    // perform the threshold value with the current slider values
    cv::threshold( original_rgb_image, thresholded_image, threshold_value, max_binary_value, threshold_type );
    // show the thresholded image (stored in thresholded_image)
    cv::imshow( window_name, thresholded_image );
}*/
int main( int argc, char** argv ) {
    /*
    // Store the full path to the image file in a string
    std::string imageName("/home/mtrn4230/mp_repos/vision_repo/thresholding/src/Solitare1-crop2.jpg");

    // read in the image defined above and store into a Matrix (cv::Mat data type)
    cv::Mat original_colour_image  = cv::imread(imageName, cv::IMREAD_COLOR ); // Load an image
    
    // if the matrix is empty, then there was a problem reading the file
    if (original_colour_image.empty()) {
        std::cout << "Cannot read the image: " << imageName << std::endl;
        return -1;
    }

    cv::cvtColor( original_colour_image, original_grey_image, cv::COLOR_BGR2RGB ); // Convert the image to Gray
    cv::namedWindow( window_name, cv::WINDOW_AUTOSIZE ); // Create a window to display results
    
    // When you have finished choosing a threshold type and value, you can comment out these three lines
    cv::createTrackbar( trackbar_type,
                    window_name, &threshold_type,
                    max_type, threshold_demo ); // Create a Trackbar to choose type of Threshold
    cv::createTrackbar( trackbar_value,
                    window_name, &threshold_value,
                    max_value, threshold_demo ); // Create a Trackbar to choose Threshold value
    threshold_demo( 0, 0 ); // Call the function to initialize
    
    // Once you have chosen your threshold type and value you can uncomment this section below:

    // int my_threshold_value = ??; // put your threshold value here (0-255)
    // int my_threshold_type = ??; // put your threshold type here (0-4)
    // cv::threshold( original_grey_image, thresholded_image, my_threshold_value, max_binary_value, my_threshold_type); // now perform the threshold using your values
    // cv::imshow( window_name, thresholded_image ); // show the thresholded image
    
    // the thresholded image is stored in thresholded_image, so you can now operate on thresholded_image with any other image processing functions
    // add in your other image processing stuff below to find the centre of each coin...


    */

   //while (1) {
        //Get current position if trackers
        hMin = cv::getTrackbarPos(HMin, hsv_window);
        sMin = cv::getTrackbarPos(SMin, hsv_window);
        vMin = cv::getTrackbarPos(VMin, hsv_window);
        hMax = cv::getTrackbarPos(HMax, hsv_window);
        sMax = cv::getTrackbarPos(SMax, hsv_window);
        vMax = cv::getTrackbarPos(VMax, hsv_window);

        //Set min and max HSV valuesto display
        
        // Convert HSV format to color threshold
        cv::cvtColor(original_colour_image, hsv, cv::COLOR_BGR2HSV);
        cv::inRange(hsv, cv::Scalar(hMin, sMin, vMin), cv::Scalar(hMax,sMax,vMax), mask);
        cv::imshow(mask);
    //}

    // wait for a keypress before exiting - if you don't have this line, the program will end!
    cv::waitKey();
    return 0;
}