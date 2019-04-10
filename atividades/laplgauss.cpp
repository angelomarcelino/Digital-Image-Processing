#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void printmask(Mat& m) {
    for (int i = 0; i < m.size().height; i++) {
        for (int j = 0; j < m.size().width; j++) {
            cout << m.at<float>(i, j) << ",";
        }
        cout << endl;
    }
}

void menu() {
    cout << "\nPressione a tecla correspondente para ativar o filtro: \n"
            "a - imagem original\n"
            "l - laplaciano 3x3 sem gauss\n"
            "g - laplaciano do gaussiano 3x3\n"
            "5 - laplaciano do gaussiano 5x5\n"
            "esc - sair\n";
}

int main(int argvc, char** argv) {
    VideoCapture video;
    // Masks
    Mat mgauss, mlaplacian, mlog, mask, mask1;
    float id[] = {0, 0, 0, 0, 1, 0, 0, 0, 0};
    float gauss[] = {1, 2, 1, 2, 4, 2, 1, 2, 1};
    float laplacian[] = {0, -1, 0, -1, 4, -1, 0, -1, 0};
    float lapofgau[] = {0,  0,  -1, 0,  0,  0,  -1, -2, -1, 0,  -1, -2, 16,
                        -2, -1, 0,  -1, -2, -1, 0,  0,  0,  -1, 0,  0};

    Mat cap, frame, frame32f, frameFiltered;
    Mat result, result1;
    double width, height;

    mask = mask1 = Mat(3, 3, CV_32F, id);
    mgauss = Mat(3, 3, CV_32F, gauss) / (float)(16);
    mlaplacian = Mat(3, 3, CV_32F, laplacian);
    mlog = Mat(5, 5, CV_32F, lapofgau);

    video.open(0);
    if (!video.isOpened()) return -1;

    width = video.get(CV_CAP_PROP_FRAME_WIDTH);
    height = video.get(CV_CAP_PROP_FRAME_HEIGHT);
    cout << "Largura = " << width << "\n";
    cout << "Altura = " << height << "\n";

    namedWindow("filtroespacial", 1);
    menu();

    while (true) {
        video >> cap;
        cvtColor(cap, frame, CV_BGR2GRAY);
        flip(frame, frame, 1);
        imshow("original", frame);

        frame.convertTo(frame32f, CV_32F);
        filter2D(frame32f, frameFiltered, -1, mask, Point(-1, -1), 0,
                 BORDER_DEFAULT);
        filter2D(frameFiltered, frameFiltered, -1, mask1, Point(-1, -1), 0,
                 BORDER_DEFAULT);
        frameFiltered.convertTo(result, CV_8U);
        imshow("filtroespacial", result);

        char key = (char)waitKey(30);
        if (key == 27) break;
        switch (key) {
            case 'a':
                menu();
                mask = mask1 = Mat(3, 3, CV_32F, id);
                printmask(mask);
                break;
            case 'l':
                menu();
                mask = mlaplacian;
                mask1 = Mat(3, 3, CV_32F, id);
                printmask(mask);
                break;
            case 'g':
                menu();
                mask = mgauss;
                printmask(mask);
                mask1 = mlaplacian;
                printmask(mask1);
                break;
            case '5':
                menu();
                mask = mgauss;
                mask1 = mlog;
                printmask(mask1);
                break;
            default:
                break;
        }
    }
    return 0;
}