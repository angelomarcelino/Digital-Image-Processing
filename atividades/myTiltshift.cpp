#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace cv;
using namespace std;

int blurValue;
int blur_slider = 0;
int blur_slider_max = 10;

Mat img1, img2;
int height;

char TrackbarName[50];

void refresh(){
    imshow("tiltshift", img2);
}

void on_trackbar_blur(int, void*){
    blurValue = blur_slider;
    Mat aux, mask;
    float media[] = {1,1,1,
                     1,1,1,
                     1,1,1};
    // Creates the Mask matrix
    mask = Mat(3, 3, CV_32F, media); 
    scaleAdd(mask, 1/9.0, Mat::zeros(3,3,CV_32F), mask);
    // "img1" is used otherwise the blur will always increase
    img1.convertTo(aux, CV_32F); 
    for (int i = 0; i < blurValue; i++) {
        filter2D(aux, aux, aux.depth(), mask, Point(1, 1), 0);
    }
    aux=abs(aux);
    aux.convertTo(img2, CV_8UC3);
    // Updates window
    refresh();
}

int main(int argvc, char** argv){
    img1 = imread(argv[1], IMREAD_COLOR);
    height = img1.size().height;
    img2 = img1.clone();
    namedWindow("tiltshift", 1);

    sprintf(TrackbarName, "Blur");
    createTrackbar(TrackbarName, 
                   "tiltshift", 
                   &blur_slider, 
                   blur_slider_max,
                   on_trackbar_blur);
    on_trackbar_blur(blur_slider, 0);

    waitKey(0);

    imwrite("tiltshiftedImg.jpg", img2);
    return 0;
}
