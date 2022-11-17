#include "MatView.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <QImage>
#include <QPainter>
#include <iostream>
using namespace cv;

MatView::MatView(QWidget *widget):QOpenGLWidget(widget)
{
    m_mat = imread("1.png");
    cvtColor(m_mat, m_mat, COLOR_BGR2RGB);
    this->resize(QSize(m_mat.cols, m_mat.rows));
}

void MatView::paintEvent(QPaintEvent *e)
{

    //do not write business logic code
    //only paint
    std::cout << this->size().height() << " ," << this->size().width() << std::endl;
    QImage img(m_mat.data, m_mat.cols, m_mat.rows, QImage::Format_RGB888);
    QPainter painter;
    painter.begin(this);
    painter.drawImage(QPoint(0,0), img);
}
