#include "mygraphicspixmapitem.h"

void MyGraphicsPixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)  {
    painter->drawPixmap(0,0,/*-1-m_pixmap.width()/2,-1-m_pixmap.height()/2,*/m_pixmap);
    qDebug()<<"item painting";
    painter->setRenderHint(QPainter::Antialiasing);
    if((pts.size()>=2)&&drawStep){
    linePt->setPainter(painter);
    linePt->drawPattern(pts,drawStep);
    }
    return QGraphicsPixmapItem::paint(painter,option,widget);
}

void MyGraphicsPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *e)  {
    e->accept();

    QPointF scenePos = mapToScene(e->pos());
    if (e->button()== Qt::LeftButton) {
            qDebug()<<"item Pressed...";
        if((figureChosed==figure::MS3PTS)||(figureChosed==figure::CALI3PTS)){
            ///第一次按击
            if (drawStep == 0) {
                pts.resize(2);
                pts[0] = scenePos; // 设置起点
                pts[1] = scenePos; // 初始化用于预览的终点
                drawStep = 1; // 进入第一步
                qDebug()<<"0Tostep1";

            }
            ///第二次按击
            else if (drawStep == 1) {
                pts.resize(3);
                pts[1] = scenePos;
                pts[2] = scenePos;
                drawStep = 2; // 进入第二步
                qDebug()<<"1Tostep2";
            }
            ///第三次按击
            else if (drawStep == 2) {
                pts.resize(3);
                pts[2] = scenePos;
                drawStep = 0; // 重置绘制状态
                qDebug()<<"2Tostep0";
            }
            update(); // 请求重绘
        }
        else{
            this->pts.push_back(scenePos);
            qDebug()<<"pts.push_back";
        } ///figure::others
    } ///Qt::LeftButton

    return QGraphicsPixmapItem::mousePressEvent(e);
} ///func

void MyGraphicsPixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *e) {
    e->accept();
    qDebug()<<"item moving...";

    QPointF scenePos = mapToScene(e->pos());
    ///左键画图功能
    switch (drawStep) {
    ///TO step1
    case 1:{
            pts.resize(2);
        pts[1] = scenePos;
        update(); // 请求重绘
    };break;
    case 2:{

            pts.resize(3);
        pts[2] = scenePos;
        update(); // 请求重绘
    };break;
    default: break;
    }
    return QGraphicsPixmapItem::mouseMoveEvent(e);
}

void MyGraphicsPixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *e){
    e->accept();
    qDebug()<<"item Released";

    return QGraphicsPixmapItem::mouseReleaseEvent(e);
}


QRectF MyGraphicsPixmapItem::boundingRect() const {
    return m_pixmap.rect();
//            QRectF(-1-m_pixmap.width()/2,-1-m_pixmap.height()/2,m_pixmap.width()+2,m_pixmap.height()+2);
}




