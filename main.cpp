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


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    Mat src = imread("1.png");
    // cvtColor(src, src, COLOR_BayerBG2GRAY); 错误
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    Mat bin;
    // 二进制阈值化
    //threshold(gray, bin, 100, 255, THRESH_BINARY);
    // 反二进制阈值化
    threshold(gray, bin, 100, 255, THRESH_BINARY_INV);

    namedWindow("src");
    imshow("src", src);

    namedWindow("bin");
    imshow("bin", bin);


    waitKey(0);
    return a.exec();
}
