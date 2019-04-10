#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

/** @function main */
int main(int argc, char** argv) {
    /// Declare variables
    VideoCapture video;
    Mat src, dst;

    Mat kernel;
    Point anchor;
    double delta;
    int ddepth;
    int kernel_size;

    int c;

    /// Load an image
    video.open(0);
    if (!video.isOpened()) {
        cout << "Video is not opened" << endl;
        return -1;
    }

    video >> src;

    if (!src.data) {
        return -1;
    }

    /// Create window
    namedWindow("filter2D Demo", CV_WINDOW_AUTOSIZE);

    /// Initialize arguments for the filter
    anchor = Point(-1, -1);
    delta = 0;
    ddepth = -1;

    /// Loop - Will filter the image with different kernel sizes each 0.5
    /// seconds
    int ind = 0;
    while (true) {
        video >> src;
        c = waitKey(30);
        /// Press 'ESC' to exit the program
        if ((char)c == 27) {
            break;
        }

        /// Update kernel size for a normalized box filter
        kernel_size = 3 + 2 * (ind % 50);
        kernel = Mat::ones(kernel_size, kernel_size, CV_32F) /
                 (float)(kernel_size * kernel_size);

        /// Apply filter
        filter2D(src, dst, ddepth, kernel, anchor, delta, BORDER_DEFAULT);
        imshow("filter2D Demo", dst);
        ind++;
    }

    return 0;
}
