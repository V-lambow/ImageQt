#ifndef PATTERNDRAWER_H
#define PATTERNDRAWER_H
#include <QVector>
#include <QPainter>
class PatternDrawer{
    QPainter* m_painter;

    virtual void drawPattern(const QVector<QPointF>&pts,const size_t &step)=0;
public:
    virtual void setPainter(QPainter* painter){
        m_painter=painter;
    }


    PatternDrawer(){}
    PatternDrawer(QPainter* painter):m_painter(painter){}
    ~PatternDrawer(){}
};

#endif // PATTERNDRAWER_H
