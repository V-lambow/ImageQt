#ifndef MODELINEPT_H
#define MODELINEPT_H
#include <QWidget>
#include <QPainter>
#include <QDebug>
class ModeLinePt
{
public:
    ModeLinePt(const QVector<QPointF>&pts={} ,QPainter* painter=nullptr ,const size_t &step=0):\
        m_pts(pts),
        m_painter(painter),
        curStatus(static_cast<status>(step)){};


    void drawPattern(const QVector<QPointF>&pts,const size_t &step){
        curStatus=static_cast<status>(step);
        m_pts=pts;
        if(curStatus==status::drawingLine){
            if(m_pts.size()>1)
            m_painter->drawLine(m_pts.at(0),m_pts.at(1));
            qDebug()<<"line1 painted";
        }
        else if(curStatus==status::drawingVerticalL){
            if(m_pts.size()<3){
                return;}
             m_painter->drawLine(m_pts.at(0),m_pts.at(1));
            QLineF line(m_pts.at(0),m_pts.at(1));
            QPointF pt(m_pts.at(2));

            float k =(line.y2()-line.y1())*1.0/(line.x2()-line.x1());
            float B=-1.0;
            float C=line.y1()-k*line.x1();

            QPointF pFoot{(B*B*pt.x()-k*B*pt.y()-k*C)/(k*k+B*B),(k*k*pt.y()-k*B*pt.x()-B*C)/(k*k+B*B)};
            m_painter->drawLine(pFoot,pt);


            float dx = line.length() / 2 / std::sqrt(1 + k * k);
            float dy = dx * k;
            QPointF p1(pt.x() - dx, pt.y() - dy); // 线段起始点
            QPointF p2(pt.x() + dx, pt.y() + dy); // 线段终止点

            // 绘制直线
            m_painter->drawLine(p1, p2);
            qDebug()<<"line23 painted";


        }
        else{
            return;
        }
    }

    void setPainter(QPainter* painter){
        m_painter=painter;
    }


private:
    QVector<QPointF>m_pts;
    enum class status{
        drawingFalse=0,
        drawingLine=1,
        drawingVerticalL=2
    };
    QPainter* m_painter;
    status curStatus=status::drawingFalse;
};



#endif // MODELINEPT_H
