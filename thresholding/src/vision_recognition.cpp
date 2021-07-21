#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

// Additional libraries


int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;

cv::Mat original_grey_image, thresholded_image, thresholded_image2, original_hsv_image, mask_image;
std::string window_name("Threshold Demo");
std::string trackbar_type("Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted");
std::string trackbar_value("Value");

/*
// Initialize HSV min/max values
hMin = sMin = vMin = hMax = sMax = vMax = 0;
phMin = psMin = pvMin = phMax = psMax = pvMax = 0;
*/

// Set threshold values for cornerstones
int hMin = 140;
int sMin = 180;
int vMin = 0;
int hMax = 155;
int sMax = 255;
int vMax = 255;

// callback function for the slider. It requries signature of int, void* even if these are unused
static void threshold_demo( int trackbarPos, void* userData ) {
    /* 
     Thresholding types:
     0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
    */
    // perform the threshold value with the current slider values
    cv::threshold( thresholded_image, thresholded_image2, threshold_value, max_binary_value, threshold_type );
    // show the thresholded image (stored in thresholded_image)
    //cv::imshow( window_name, thresholded_image2 );
}
int main( int argc, char** argv ) {
    // Store the full path to the image file in a string
    std::string imageName("/home/mtrn4230/mp_repos/vision_repo/thresholding/src/SolitaireCorner1.jpg");

    // read in the image defined above and store into a Matrix (cv::Mat data type)
    cv::Mat original_colour_image  = cv::imread(imageName, cv::IMREAD_COLOR ); // Load an image
    
    // if the matrix is empty, then there was a problem reading the file
    if (original_colour_image.empty()) {
        std::cout << "Cannot read the image: " << imageName << std::endl;
        return -1;
    }

    cv::cvtColor( original_colour_image, original_grey_image, cv::COLOR_BGR2GRAY ); // Convert the image to Gray
    cv::namedWindow( window_name, cv::WINDOW_AUTOSIZE ); // Create a window to display results

    // Cornerstone code
    /*
    // Set minimum and maximum HSV values to display
    lower[1][3] = [hMin,sMin,vMin];
    upper[1][3] = [hMax,sMax,vMax];
    */

    // Convert to HSV format and color threshold
    cv::cvtColor(original_colour_image, original_hsv_image, cv::COLOR_BGR2HSV);
    cv::inRange(original_hsv_image, cv::Scalar(hMin,sMin,vMin), cv::Scalar(hMax,sMax,vMax), mask_image);
    cv::imshow( window_name, mask_image );
    
    /*
    // When you have finished choosing a threshold type and value, you can comment out these three lines
    cv::createTrackbar( trackbar_type,
                    window_name, &threshold_type,
                    max_type, threshold_demo ); // Create a Trackbar to choose type of Threshold
    cv:: createTrackbar( trackbar_value,
                    window_name, &threshold_value,
                    max_value, threshold_demo ); // Create a Trackbar to choose Threshold value
    threshold_demo( 0, 0 ); // Call the function to initialize
    */
    
    // Once you have chosen your threshold type and value you can uncomment this section below:
    
     int my_threshold_value = 120; // put your threshold value here (0-255)
     int my_threshold_type = 3; // put your threshold type here (0-4)
     cv::threshold( original_grey_image, thresholded_image, my_threshold_value, max_binary_value, my_threshold_type); // now perform the threshold using your values
     //cv::imshow( window_name, thresholded_image ); // show the thresholded image
    
    // the thresholded image is stored in thresholded_image, so you can now operate on thresholded_image with any other image processing functions
    // add in your other image processing stuff below to find the centre of each coin...
    /*
    // When you have finished choosing a threshold type and value, you can comment out these three lines
    cv::createTrackbar( trackbar_type,
                    window_name, &threshold_type,
                    max_type, threshold_demo ); // Create a Trackbar to choose type of Threshold
    cv:: createTrackbar( trackbar_value,
                    window_name, &threshold_value,
                    max_value, threshold_demo ); // Create a Trackbar to choose Threshold value
    threshold_demo( 0, 0 ); // Call the function to initialize
    */

    // Once you have chosen your threshold type and value you can uncomment this section below:
    
     int my_threshold_value2 = 240; // put your threshold value here (0-255)
     int my_threshold_type2 = 4; // put your threshold type here (0-4)
     cv::threshold( thresholded_image, thresholded_image2, my_threshold_value2, max_binary_value, my_threshold_type2); // now perform the threshold using your values
     //cv::imshow( window_name, thresholded_image2 ); // show the thresholded image


    // wait for a keypress before exiting - if you don't have this line, the program will end!
    cv::waitKey();
    return 0;
}