#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

// Additional libraries
#include <opencv2/core/mat.hpp>

int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;

cv::Mat original_grey_image, thresholded_image, thresholded_image2, original_hsv_image, mask_image, opened_image, blur_image, binary_image;
std::string window_name("Threshold Demo");
std::string open_window("Opening noise reduction");
std::string blur_window("Blurred image");
std::string test_window("Test window");
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

int main( int argc, char** argv ) {
    // Store the full path to the image file in a string
    std::string imageName("/home/mtrn4230/mp_repos/vision_repo/thresholding/src/SolitaireCorner2.jpg");

    // read in the image defined above and store into a Matrix (cv::Mat data type)
    cv::Mat original_colour_image  = cv::imread(imageName, cv::IMREAD_COLOR ); // Load an image
    
    // if the matrix is empty, then there was a problem reading the file
    if (original_colour_image.empty()) {
        std::cout << "Cannot read the image: " << imageName << std::endl;
        return -1;
    }

    //cv::cvtColor( original_colour_image, original_grey_image, cv::COLOR_BGR2GRAY ); // Convert the image to Gray
    cv::namedWindow( window_name, cv::WINDOW_AUTOSIZE ); // Create a window to display results

    // Convert to HSV format and color threshold
    cv::cvtColor(original_colour_image, original_hsv_image, cv::COLOR_BGR2HSV);
    cv::inRange(original_hsv_image, cv::Scalar(hMin,sMin,vMin), cv::Scalar(hMax,sMax,vMax), mask_image);
    cv::imshow( window_name, mask_image );

    // Perform Opening to remove salt noise
    // Create a structuring element
    cv::Point anchor = cv::Point(-1,-1);
    int morph_size = 1;
    //cv::Mat element = cv::getStructuringElement(1,cv::Size(2 * morph_size + 1,2 * morph_size + 1),cv::Point(morph_size,morph_size));
    cv::Mat open_kernel = cv::getStructuringElement(1,cv::Size(2 * morph_size + 1,2 * morph_size + 1),cv::Point(morph_size,morph_size));
    cv::morphologyEx(mask_image, opened_image, cv::MORPH_OPEN, open_kernel, anchor, 1);

    // Show opened image in new window
    cv::namedWindow( open_window, cv::WINDOW_AUTOSIZE );
    cv::imshow( open_window, opened_image );

    
    // Perform blurring to opened image
    cv::GaussianBlur(opened_image, blur_image, cv::Size(5,5), 0);
    cv::namedWindow( blur_window, cv::WINDOW_AUTOSIZE);
    cv::imshow( blur_window, blur_image);
    

    // Perform binary threshold on blurred image
    cv::threshold(blur_image, binary_image, 0, 255, cv::THRESH_BINARY);
    cv::namedWindow( test_window, cv::WINDOW_AUTOSIZE);
    cv::imshow( test_window, binary_image);

    // Find contours of the cornerstones
    //cv::OutputArrayOfArrays contour_array = cv::OutputArrayOfArrays(0);
    std::vector<std::vector<cv::Point> > contour_array; //create Output array of array vector for contour points storage
    cv::findContours(binary_image, contour_array, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    

    // wait for a keypress before exiting - if you don't have this line, the program will end!
    cv::waitKey();
    return 0;
}