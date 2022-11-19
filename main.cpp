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

Mat resizeImage(const Mat &src, int width, int height) {
    Mat des(height, width, src.type());

    int sx, sy = 0;
    float dx = (float)src.cols / des.cols;
    float dy = (float)src.rows / des.rows;
    for (int r = 0; r < des.rows; r++) {
        sy = r * dy + 0.5;
        for (int c = 0; c < des.cols; c++) {
            sx = c * dx + 0.5;
            des.at<Vec3b>(r, c) = src.at<Vec3b>(sy, sx);
        }
    }
    return des;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Widget w;
    w.show();

    Mat src = imread("1.png");
    Mat des = resizeImage(src, 2000, 2000);
    Mat des2;
    resize(src, des2, Size(2000, 2000), 0, 0, INTER_NEAREST);

    resize(src, des2, Size(1000, 1000), 0, 0, INTER_NEAREST);
    namedWindow("des2");
    imshow("des2", des2);

    namedWindow("src");
    imshow("src", src);

    resize(src, des2, Size(1000, 1000), 0, 0, INTER_LINEAR);
    namedWindow("des3");
    imshow("des3", des2);

    waitKey(0);
    return a.exec();
}
