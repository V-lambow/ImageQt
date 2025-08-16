#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsPixmapItem>

#include <QGraphicsView>
#include <QWheelEvent>
#include <QtMath>
#include<QMessageBox>
#include <QString>
#include <QVector>
#include <QDebug>
#include "modeLinePt.hpp"
#include "param.h"

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
private:
    int factor;

public:
    GraphicsView(QWidget* parent = nullptr);
    ~GraphicsView();

    ///记录点击的点
    QVector<QPointF> pts={};

    int ptsNumRecord=0;


    figure figureChosed=figure::POINT;

    QGraphicsScene *scene;

    QPainter painter;
    ///左键画图步骤
    uint drawStep=0;
    ///右键拖拽画图
    bool isDragging =false;
    std::unique_ptr<ModeLinePt>linePt=std::make_unique<ModeLinePt>(pts,&painter,drawStep);
    QPixmap* pixmap;

    //    std::unique_ptr<QGraphicsItem>item=std::make_unique<QGraphicsItem>();

    QPoint DraggingPos;


    int getFactor();
    void setFactor(int _factor);
private:
    friend class MainWindow;
    ///滚轮放大缩小
    virtual void wheelEvent(QWheelEvent *e) override;

    ///鼠标左键画直线
    virtual void mousePressEvent(QMouseEvent *e) override;
    virtual void mouseMoveEvent(QMouseEvent *e) override;
    virtual void paintEvent(QPaintEvent  *e) override;
    virtual void mouseReleaseEvent(QMouseEvent *e) override;
    void enterEvent(QEvent *e) override;
    void Translate(QPointF delta);
signals:
    void mouseMoved(const QPointF& pt);
    void sg_drawLine();
    void sg_califrom3pts();
    void sg_msfrom3pts();
    void sg_drawRect1();
    void sg_polyArea();
    void sg_pts3MsAgl();
};



#endif // GRAPHICSVIEW_H
