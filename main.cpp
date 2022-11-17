#include "widget.h"
#include <QApplication>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
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
    Mat mat(3000, 4000, CV_8UC3);
    //mat.create(3000, 4000, CV_8UC3);
    int es = mat.elemSize();
    int size = mat.rows * mat.cols * mat.elemSize();
    printMs();
    for (int i = 0; i < size; i += es){
        mat.data[i] = 255;
        mat.data[i + 1] = 0;
        mat.data[i + 2] = 0;
    }
    printMs(std::to_string(__LINE__));
    for (int row = 0; row < mat.rows; row++) {
        for (int col = 0; col < mat.cols; col++) {
            (&mat.data[row * mat.step])[col*es] = 0;
            (&mat.data[row * mat.step])[col*es+1] = 0;
            (&mat.data[row * mat.step])[col*es+2] = 255;
        }
    }
    printMs(std::to_string(__LINE__));
    //使用ptr遍历Mat
    for (int row = 0; row < mat.rows; row++) {
        for (int col = 0; col < mat.cols; col++) {
            auto matPtr = mat.ptr<Vec3b>(row, col);
            matPtr->val[0] = 0;
            matPtr->val[1] = 255;
            matPtr->val[2] = 0;
        }
    }
    printMs(std::to_string(__LINE__));
    //use at mathod to traverse, when access is out of bounds, there is not exception, strange
    try {
        for (int row = 0; row < mat.rows; row++) {
            for (int col = 0; col < mat.cols; col++) {
                auto& m = mat.at<Vec3b>(row, col);
                m[0] = 200;
                m[1] = 200;
                m[3] = 111;
            }
        }
    } catch(Exception &ex) {
        std::cout << ex.what() << std::endl;
    }
    printMs(std::to_string(__LINE__));

    auto it = mat.begin<Vec3b>();
    auto end = mat.end<Vec3b>();
    for (; it!=end; it++){
        (*it).val[0] = 0;
        (*it).val[1] = 0;
        (*it).val[2] = 0;
    }
    printMs(std::to_string(__LINE__));
    namedWindow("mat");
    imshow("mat", mat);
    waitKey(0);

    return a.exec();
}
