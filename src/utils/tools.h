/****************************************************************************
 *                              Basic tools:
 * greyscale, brightness, flip, wand or cool ...
 * *************************************************************************/

#ifndef TOOLS_H
#define TOOLS_H


#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QtMath>
#include "gaussianblur.h"
#include <QMessageBox>
#include<iostream>



namespace Tools {
QImage GreyScale(QImage origin);
QImage Warm(int delta, QImage origin);
QImage Cool(int delta, QImage origin);
QImage DrawFrame(QImage origin, QImage &frame);
QImage Brightness(int delta, QImage origin);
QImage Horizontal(const QImage &origin);
QImage Vertical(const QImage &origin);
QImage LinearLevelTransformation(const QImage &origin, double a, double b);
QImage LogGreyLevelTransformation(const QImage &origin, double a, double b);
QImage PowerGreyLevelTransformation(const QImage &origin, double c, double r, double b);
QImage ExpTransform(const QImage &origin, double b, double c, double a);
QImage TwoThreshold(const QImage &orogin, double t1, double t2, int option);
QImage StretchTransform(const QImage &origin,
                                        int x1, int x2,
                                        double k1, double k2, double k3,
                                        double b2, double b3);
QImage SimpleSmooth(const QImage &origin);
QImage MeidaFilter(const QImage &origin, int radius);
QImage LaplaceSharpen(const QImage &origin);
QImage SobelEdge(const QImage &origin);
QImage GaussianSmoothing(const QImage &origin, int radius, double sigma);
QImage Binaryzation(const QImage &origin);
QImage Metal(QImage origin);
QImage PrewittEdge(const QImage &origin);
QImage ContourExtraction(const QImage &origin);
QImage Dilate(const QImage &origin);
QImage Expansion(const QImage &origin);
QImage Opening(const QImage &origin);
QImage Closing(const QImage &origin);
QImage Thinning(const QImage &origin);
//QImage RGB2HSV(const QImage &origin);
//QImage RGB2HSL(const QImage &origin);
//QImage RGB2CMYK(const QImage &origin);
QImage Final(const QImage &origin);

QPointF midPoint(const QPointF &pt1,const QPointF &pt2);
QPointF midPoint(const QPoint &pt1,const QPoint &pt2);

std::tuple<QImage,double> PaintLine(const QImage &origin,QLineF line,const double& reslouton,QPainter* Painter =nullptr,QPen pen=QPen(Qt::red, 1));
std::tuple<QImage,double> PaintLineAPt(const QImage &origin,QLineF line,QPointF pt,const double& reslouton,QString str="",QPainter* Painter =nullptr,QPen pen=QPen(Qt::red, 1));

std::tuple<QImage,double>  PaintRect1(const QImage &origin,QPointF ptbg,QPointF ptend,const double& reslouton,QPainter* Painter =nullptr,QPen pen=QPen(Qt::red, 1));
std::tuple<QImage,int> PaintRect2(const QImage &origin,QPointF ptbg,QPointF ptend,const double& reslouton,QPainter* Painter =nullptr,QPen pen=QPen(Qt::red, 1));
std::tuple<QImage,double> PaintPoly(const QImage &origin,const QVector<QPointF>pts,const double& reslouton,QPainter* Painter =nullptr,QPen pen=QPen(Qt::red, 1));
double calculatePolygonArea(const QVector<QPointF> &points);
double pts3toAngle(const QVector<QPointF>& points);
std::tuple<QImage,double>PaintAngle(const QImage &origin,const QVector<QPointF>pts,QPainter* Painter =nullptr,QPen pen=QPen(Qt::red, 1));

}




#endif // TOOLS_H
