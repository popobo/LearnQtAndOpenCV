#include "MatView.h"
#include <QImage>
#include <QPainter>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

MatView::MatView(QWidget *widget) : QOpenGLWidget(widget) {}

void MatView::paintEvent(QPaintEvent *e) {}
