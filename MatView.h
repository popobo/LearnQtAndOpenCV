#ifndef MATVIEW_H
#define MATVIEW_H

#include <QOpenGLWidget>
#include <opencv2/core.hpp>

class MatView:public QOpenGLWidget
{
    Q_OBJECT

public:
    MatView(QWidget* widget);

    void paintEvent(QPaintEvent* e);

 private:
     cv::Mat m_mat;
};

#endif // MATVIEW_H
