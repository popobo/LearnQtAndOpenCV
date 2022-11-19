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

    Mat src = imread("1.png");
    Mat des;
    cv::rotate(src, des, ROTATE_180);

    Mat des1;
    cv::flip(src, des1, 0);

    namedWindow("des");
    imshow("des", des);

    namedWindow("des1");
    imshow("des1", des1);

    waitKey(0);
    return 0;
}
