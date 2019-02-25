#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    Mat image;
    Vec3b val;

    image = imread(argv[1], CV_LOAD_IMAGE_COLOR );
    if (!image.data)
        cout << "A imagem nao foi carregada corretamente" << endl;

    namedWindow("janela", WINDOW_AUTOSIZE);
    
}