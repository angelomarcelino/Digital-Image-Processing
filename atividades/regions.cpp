#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

struct ponto
{
    int x, y;
};

int main(int argc, char **argv)
{
    srand(time(NULL));
    Mat image;
    ponto p1, p2;
    Vec3b val;

    image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    if (!image.data)
        cout << "A imagem nao foi carregada corretamente" << endl;

    namedWindow("janela", WINDOW_AUTOSIZE);

    cout << "Insira os pontos do retângulo dentro dos limites da imagem ("
         << image.rows << "," << image.cols << "): ";
    cin >> p1.x >> p1.y >> p2.x >> p2.y;

    imshow("janela", image);
    imwrite("grayscale.png", image);
    waitKey();

    for (int i = p1.x; i < p2.x; i++)
    {
        for (int j = p1.y; j < p2.y; j++)
        {
            image.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);
        }
    }

    imshow("janela", image);
    imwrite("negativo_grayscale.png", image);
    waitKey();

    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    if (!image.data)
        cout << "A imagem nao foi carregada corretamente" << endl;

    imshow("janela", image);
    waitKey();

    val[0] = 255; //B
    val[1] = 255; //G
    val[2] = 255; //R

    for (int i = p1.x; i < p2.x; i++)
    {
        for (int j = p1.y; j < p2.y; j++)
        {
            image.at<Vec3b>(i, j) = val - image.at<Vec3b>(i, j);
        }
    }

    imshow("janela", image);
    imwrite("negativo_color.png", image);
    waitKey();
    return 0;
}