#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    int nbins = 64;
    float range[] = {0, 256};
    const float *histrange = {range};
    bool uniform = true;
    bool acummulate = false;
    Mat hist, histEq;

    VideoCapture cap;

    cap.open(0);
    if (!cap.isOpened())
    {
        cout << "Erro ao acessar a camera!\n";
        return -1;
    }

    // Calcula a largura e altura dos framas capturados
    int width = cap.get(CV_CAP_PROP_FRAME_WIDTH),
        height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

    cout << "Width: " << width << endl
         << "Height: " << height << endl;

    while (true)
    {
        Mat img, imgEq;
        cap >> img;

        // Inverte a imagem
        flip(img, img, 1);

        // Tranforma a imagem capturada para grayscale
        cvtColor(img, img, CV_BGR2GRAY);

        // Equaliza o histograma
        equalizeHist(img, imgEq);

        // Calcula o histograma
        calcHist(&img, 1, 0, Mat(), hist, 1,
                 &nbins, &histrange,
                 uniform, acummulate);
        calcHist(&imgEq, 1, 0, Mat(), histEq, 1,
                 &nbins, &histrange,
                 uniform, acummulate);

        int histw = nbins, histh = nbins / 2;
        Mat histImg(histh, histw, CV_8UC1, Scalar(0, 0, 0));
        Mat histImgEq(histh, histw, CV_8UC1, Scalar(0, 0, 0));

        // Normaliza o histograma para aparecer nas imagens
        normalize(hist, hist, 0, histImg.rows, NORM_MINMAX, -1, Mat());
        normalize(histEq, histEq, 0, histImgEq.rows, NORM_MINMAX, -1, Mat());

        for (int i = 0; i < nbins; i++)
        {
            line(histImg,
                 Point(i, histh),
                 Point(i, histh - cvRound(hist.at<float>(i))),
                 Scalar(255, 255, 255), 1, 8, 0);
            line(histImgEq,
                 Point(i, histh),
                 Point(i, histh - cvRound(histEq.at<float>(i))),
                 Scalar(255, 255, 255), 1, 8, 0);
        }

        histImg.copyTo(img(Rect(0, 0, nbins, histh)));
        histImgEq.copyTo(imgEq(Rect(0, 0, nbins, histh)));
        imshow("Equalized Histogram", imgEq);
        imshow("Normal", img);
        if (waitKey(30) == 'a')
            break;
    }

    return 0;
}