#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QtMath>
#include<QMessageBox>
#include <QString>
#include <QVector>
#include <QDebug>
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

    enum class  figure{
        POINT=1,
        LINE=2,
        CALI3PTS,
        MS3PTS,
        RECT1,
        POLY
    };
    QPainter painter;
    figure figureChosed=figure::POINT;

    int getFactor();
    void setFactor(int _factor);
private:
       friend class MainWindow;
    ///滚轮放大缩小
    virtual void wheelEvent(QWheelEvent *e) override;

    ///鼠标左键画直线
    virtual void mousePressEvent(QMouseEvent *e) override;
    virtual void mouseMoveEvent(QMouseEvent *e) override;
signals:
    void mouseMoved(const QPointF& pt);
    void sg_drawLine();
    void sg_califrom3pts();
    void sg_msfrom3pts();
    void sg_drawRect1();
    void sg_polyArea();
};



#endif // GRAPHICSVIEW_H
