#include "widget.h"
#include <QApplication>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    Mat mat(3000, 4000, CV_8UC3);
    //mat.create(3000, 4000, CV_8UC3);
    int es = mat.elemSize();
    int size = mat.rows * mat.cols * mat.elemSize();

    for (int i = 0; i < size; i += es){
        mat.data[i] = 255;
        mat.data[i + 1] = 0;
        mat.data[i + 2] = 0;
    }

    namedWindow("mat");
    imshow("mat", mat);
    waitKey(0);

    return a.exec();
}
