#include "widget.h"
#include <QApplication>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

void printMs(const std::string &text = "") {
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

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Widget w;
    w.show();

    Mat src = imread("1.png");
    Mat src2 = imread("2.png");
    Mat des;
    resize(src2, src2, Size(src.rows, src.cols));
    float alpha = 0.5;
    addWeighted(src, alpha, src2, 1 - alpha, 0, des);

    namedWindow("des");
    imshow("des", des);

    waitKey(0);
    return a.exec();
}
