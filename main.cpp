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

    Mat src1 = imread("1.png");
    Mat src2 = imread("2.png");

    int desRows = src1.rows;
    int newSrc2Cols = (float)src2.cols * ((float)desRows / (float)src2.rows);
    resize(src2, src2, Size(desRows, newSrc2Cols));

    Mat des(desRows, src1.cols + src2.cols, src1.type());

    Mat r1 = des(Rect(0, 0, src1.cols, src1.rows));
    Mat r2 = des(Rect(src1.cols, 0, src2.cols, src2.rows));
    src1.copyTo(r1);
    src2.copyTo(r2);

    namedWindow("src1");
    imshow("src1", src1);

    namedWindow("src2");
    imshow("src2", src2);

    namedWindow("des");
    imshow("des", des);

    waitKey(0);
    return 0;
}
