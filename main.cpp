#include "widget.h"
#include <QApplication>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

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
    cvtColor(src, gray, COLOR_BGR2GRAY);
    Mat mygray;
    RGBToGray(src, mygray);

    namedWindow("src");
    imshow("src", src);

    namedWindow("gray");
    imshow("gray", gray);

    namedWindow("mygray");
    imshow("mygray", mygray);

    waitKey(0);
    return a.exec();
}
