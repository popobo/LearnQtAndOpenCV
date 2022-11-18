#include "widget.h"
#include <QApplication>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

void printMs(const std::string& text = "") {
    static long long last = 0;
    long long cur = getTickCount();
    if (last == 0) {
        last = cur;
        return;
    }
    long long ms;
    ms = ((double)(cur - last) / getTickFrequency()) * 1000;
    if (text != "") {
        std::cout << text << " " << ms << "ms" << std::endl;
    }
    last = getTickCount();
}

void RGBToGray(const Mat& src, Mat& des) {
    // GRay = (R*30+G*59+B*11+50)/100
    des.create(src.rows, src.cols, CV_8UC1);
    for (int r=0;r<src.rows;r++) {
        for(int c=0;c<src.cols;c++){
            const Vec3b& m=src.at<Vec3b>(r, c);
            des.at<uchar>(r, c) = (m[2]*30+m[1]*59+m[0]*11+50)/100;
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    Mat src = imread("1.png");
    Mat gray;
    printMs();
    // first cvtColor costs more time due to init
    cvtColor(src, gray, COLOR_BGR2GRAY);
    printMs(std::to_string(__LINE__));
    Mat mygray;
    printMs(std::to_string(__LINE__));
    RGBToGray(src, mygray);
    printMs(std::to_string(__LINE__));

    namedWindow("src");
    imshow("src", src);

    namedWindow("gray");
    imshow("gray", gray);

    namedWindow("mygray");
    imshow("mygray", mygray);

    waitKey(0);
    return a.exec();
}
