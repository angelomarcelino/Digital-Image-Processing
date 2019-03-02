#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    Mat image, mask;
    int width, height;
    int nobjects, nholes;

    nobjects = nholes = 0;

    CvPoint p;
    image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);

    if (!image.data)
    {
        std::cout << "imagem nao carregou corretamente\n";
        return (-1);
    }
    width = image.size().width;
    height = image.size().height;

    p.x = 0;
    p.y = 0;

    // busca objetos na borda de cima e de baixo
    for (int col = 0; col < width; col++)
    {
        if (image.at<uchar>(0, col) == 255)
        {
            // achou um objeto
            p.x = col;
            p.y = 0;
            floodFill(image, p, 0);
        }
        if (image.at<uchar>(height - 1, col) == 255)
        {
            // achou um objeto
            p.x = col;
            p.y = height - 1;
            floodFill(image, p, 0);
        }
    }
    // busca objetos na bordas da esq e dir
    for (int row = 0; row < height; row++)
    {
        if (image.at<uchar>(row, 0) == 255)
        {
            // achou um objeto
            p.x = 0;
            p.y = row;
            floodFill(image, p, 0);
        }
        if (image.at<uchar>(row, width - 1) == 255)
        {
            // achou um objeto
            p.x = width - 1;
            p.y = row;
            floodFill(image, p, 0);
        }
    }

    // mudar o fundo
    floodFill(image, cvPoint(0, 0), 140);

    imshow("image", image);
    imwrite("labeling.png", image);
    cout << "nobjects = " << nobjects << endl;
    waitKey();
    return 0;
}
