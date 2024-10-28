#ifndef MYGRAPHICSITEM_H
#define MYGRAPHICSITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include "modeLinePt.hpp"
#include <QGraphicsSceneMouseEvent>
#include <iostream>



class MyGraphicsPixmapItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPixmap m_pixmap READ pixmap WRITE setPixmap NOTIFY pixmapChanged)


private:

    QPixmap m_pixmap;
    ///画图点
    QVector<QPointF> pts{};
    ///左键画图步骤
    uint drawStep=0;
    ///画图函数
    std::shared_ptr<ModeLinePt>linePt=std::make_shared<ModeLinePt>(pts,nullptr,drawStep);

    uint ptsSizeReserved=0;
    enum class  figure{
        POINT=1,
        LINE=2,
        CALI3PTS,
        MS3PTS,
        RECT1,
        POLY,
        PTS3MSAGL
    };

    figure figureChosed=figure::CALI3PTS;



protected:

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    QRectF boundingRect() const override ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public:
    explicit MyGraphicsPixmapItem(QObject *parent = nullptr,const QPixmap& pixmap=QPixmap()):m_pixmap(pixmap){
        setAcceptedMouseButtons(Qt::AllButtons);
        setAcceptHoverEvents(true);
        setFlag(QGraphicsItem::ItemIsFocusable);
        this->setParent(parent);
        qDebug()<<"item setted..";
    }
    ~MyGraphicsPixmapItem(){
        qDebug()<<"item free...";
    }

    QPixmap pixmap(){return m_pixmap;}
    void setPixmap(QPixmap pix){
        this->m_pixmap=pix;
        update();
        }




signals:
        void    pixmapChanged();
public slots:

};

#endif // MYGRAPHICSITEM_H
