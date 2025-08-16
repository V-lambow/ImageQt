#ifndef MODELINE_H
#define MODELINE_H


#include <QWidget>
#include <QPainter>
#include <QDebug>
#include "patterndrawer.hpp"

class ModeLine:public PatternDrawer
{
public:
    ModeLine(const QVector<QPointF>&pts={} ,QPainter* painter=nullptr ,const size_t &step=0):\
        m_pts(pts),
        m_painter(painter),
        curStatus(static_cast<status>(step)){};
    ModeLine(QPainter* painter):m_painter(painter){};



    void drawPattern(const QVector<QPointF>&pts,const size_t &step){
        curStatus=static_cast<status>(step);
        m_pts=pts;
        if(curStatus==status::drawingLine){
            if(m_pts.size()>1)
            m_painter->drawLine(m_pts.at(0),m_pts.at(1));
        }

        else{
            return;
        }
    }



private:
    QVector<QPointF>m_pts;
    enum class status{
        drawingFalse=0,
        drawingLine=1,
    };
    QPainter* m_painter;
    status curStatus=status::drawingFalse;
};


#endif // MODELINE_H
