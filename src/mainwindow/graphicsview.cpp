#include "graphicsview.h"

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    setMouseTracking(true);
    factor = 0;
}

GraphicsView::~GraphicsView()
{
    // to do
}

int GraphicsView::getFactor()
{
    return factor;
}

void GraphicsView::setFactor(int _factor)
{
    if (_factor == 0)
    {
        factor = 0;
    }
    else
    {
        factor += _factor;
    }
}

void GraphicsView::wheelEvent(QWheelEvent *e)
{
    // Calculate wheel movement
    int distance = e->delta()/15/8;
    qreal val;

    if (distance != 0)
    {
        val = pow(1.2, distance);
        this->scale(val, val);
        if (distance > 0)
        {
            factor ++;
        }
        else
        {
            factor --;
        }
    }
}

void GraphicsView::mousePressEvent(QMouseEvent *e){

    if (e->button() == Qt::LeftButton) {
        // 设置画笔属性（颜色和粗细）
        QPen pen(Qt::red, 2);
        QPointF scenePos = mapToScene(e->pos());
        this->pts.push_back(scenePos);

        switch (this->figureChosed) {
        ///显示点的坐标
        case figure::POINT: {

            QMessageBox::information(this, "坐标点信息", \
                                     "当前坐标:("+QString::number(scenePos.x())+\
                                     ","+QString::number(scenePos.y())+")",\
                                     QMessageBox::Ok);
        };break;
            ///画一条直线
        case figure::LINE:{
            if(this->pts.size()==2){
                //调用
                emit sg_drawLine();
            };break;

        };
            ///点到直线构建
        case figure::CALI3PTS:{
            if(this->pts.size()==3){
                emit sg_califrom3pts();
            }

        };break;
        case figure::MS3PTS:{
            if(this->pts.size()==3){
                emit sg_msfrom3pts();
            }

        };break;
        case figure::RECT1:{
            if(this->pts.size()==2){
                emit sg_drawRect1();
            }
        };break;
        case figure::POLY:{
            if(this->pts.size()==this->ptsNumRecord){
                emit sg_polyArea();
            }
        };break;
        default:{};break;
        }
    }
    return;
}

void GraphicsView::mouseMoveEvent(QMouseEvent *e){
    QPointF scenePos = mapToScene(e->pos());
    switch (this->figureChosed) {
    case figure::POINT:{
        emit mouseMoved(scenePos);
    }
    default:{};break;
    }
}


//void GraphicsView::mousePressEvent(QMouseEvent *event)
//{
//    if(event->button() == Qt::LeftButton)
//    {
//        m_isTranslate = true;
//        m_lastMousePos = event->pos();
//    }
//    else if(event->button()==Qt::RightButton)
//    {
//        QPointF point = mapToScene(event->pos());
//        //只有点击图片时才发送
//        if (scene()->itemAt(point, transform()) != NULL)
//        {
//            emit rightPixmapItem->ImageClick(point.x(),point.y());
//        }
//    }

//    QGraphicsView::mousePressEvent(event);
//}


