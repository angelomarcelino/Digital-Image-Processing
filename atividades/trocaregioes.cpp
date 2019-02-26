#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    Mat image, A, B, C, D, Vab, Vcd;
    Rect rect;

    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    if (!image.data)
    {
        cout << "A imagem nao foi carregada corretamente" << endl;
        return -1;
    }
    namedWindow("janela", WINDOW_AUTOSIZE);

    imshow("janela", image);
    cout << image.rows << " " << image.cols << endl;
    waitKey();
    
    rect = Rect(Point(0,0), Point(image.rows/2, image.cols/2));
    A = Mat(image,rect);
    rect = Rect(Point(0,image.cols/2), Point(image.rows/2, image.cols));
    B = Mat(image,rect);
    rect = Rect(Point(image.rows/2,0), Point(image.rows, image.cols/2));
    C = Mat(image,rect);
    rect = Rect(Point(image.rows/2, image.cols/2), Point(image.rows, image.cols));
    D = Mat(image,rect);

    vconcat(B, A, Vab);
    vconcat(D, C, Vcd);
    hconcat(Vcd, Vab, image);
    imshow("janela", image);
    waitKey();
    
    return 0;
}