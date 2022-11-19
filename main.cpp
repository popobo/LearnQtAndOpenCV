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
    VideoCapture videoCapture;
    videoCapture.open("test.mp4");
    if (!videoCapture.isOpened()) {
        std::cout << "failed to open video" << std::endl;
        getchar();
        return -1;
    }
    std::cout << "open video successfully" << std::endl;

    namedWindow("video");
    Mat frame;
    for (;;) {
        //        if (!videoCapture.read(frame)) {
        //            break;
        //        }
        // 读帧和解码
        if (!videoCapture.grab()) {
            break;
        }
        // 转换色彩格式
        if (!videoCapture.retrieve(frame)) {
            break;
        }

        if (frame.empty()) {
            break;
        }
        imshow("video", frame);
        waitKey(30);
    }

    getchar();

    return 0;
}
