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

// a对比度1.0-3.0，b亮度0-100
void changeGain(float a, int b, const Mat& src, Mat& des) {

    des.create(src.rows, src.cols, src.type());

    for (int r=0;r<src.rows;r++){
        for(int c=0;c<src.cols;c++){
            for(int i=0;i<3;i++){
                des.at<Vec3b>(r, c)[i]=saturate_cast<uchar>(a*src.at<Vec3b>(r,c)[i]+b);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    Mat src = imread("1.png");
    Mat des;
    printMs("1");
    changeGain(1, 100, src, des);
    printMs("2");
    Mat des2;
    printMs("3");
    src.convertTo(des2, -1, 1.0, 100);
    printMs("4");

    namedWindow("src");
    imshow("src", src);

    namedWindow("des");
    imshow("des", des);

    namedWindow("des2");
    imshow("des2", des2);

    waitKey(0);
    return a.exec();
}
