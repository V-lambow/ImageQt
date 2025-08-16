#include "graphicsview.h"


GraphicsView::GraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    scene(new QGraphicsScene(this))
{
    setMouseTracking(true);
    this->setScene(scene);
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    //    pixmap=new QPixmap(400,600);
    //    pixmap->fill(Qt::transparent);
    //    scene->addPixmap(*pixmap);

    centerOn(0, 0);
    factor = 0;

}

GraphicsView::~GraphicsView()
{
    // to do
    //    delete pixmap;
    //    pixmap=nullptr;
}


void GraphicsView::paintEvent(QPaintEvent *e){
    e->accept();
    this->painter.begin(viewport());
    painter.setPen(QPen(Qt::black, 1, Qt::DashLine));
    this->painter.setRenderHint(QPainter::Antialiasing);
//    painter.save();
    if(pts.size()>=2){

        if (drawStep)
        {
            ///画图
            if(pts.size()>=2)
                linePt->drawPattern(pts,drawStep);
            qDebug()<<"drawing Pattern";
        }
    }
//    painter.restore();
    this->painter.end();


    return QGraphicsView::paintEvent(e);
}

void GraphicsView::mousePressEvent(QMouseEvent *e){

    if (e->button() == Qt::LeftButton) {
        QPointF scenePos = mapToScene(e->pos());

        ///3点情况
        if ((figureChosed==figure::MS3PTS)||(figureChosed==figure::CALI3PTS)){
            ///TO step1
            if (drawStep==0) {
                pts.resize(2);
                if(pts.size()>1){
                    pts[0] = scenePos; // Set the start point to the current mouse position
                    pts[1] = scenePos; // Initialize end point for preview
                }
                drawStep = 1; // Set drawing to true
                qDebug()<<"press 0tostep1";
            }
            ///TO step2
            else if(drawStep==1){
                if(pts.size()>1)
                    pts[1] = scenePos;
                drawStep = 2; // Set drawing to true
                qDebug()<<"press 1tostep2";
            }
            ///TO step0
            else if(drawStep==2){
                if(pts.size()>2)
                    pts[2] = scenePos;
                drawStep = 0; // Set drawing to true
                qDebug()<<"press 2tostep0";
            }
        }//figure::MS3PTS &&figure::CALI3PTS
        else{
            this->pts.push_back(scenePos);
        }

        ///

    }//Qt::LeftButton

    ///右键拖拽
    if (e->button() == Qt::RightButton) {
        this->isDragging = true;
        this->DraggingPos = e->pos();
        setCursor(Qt::ClosedHandCursor);
    }
    return QGraphicsView::mousePressEvent(e);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *e){

    ///显示鼠标当前位置坐标
    QPointF scenePos = mapToScene(e->pos());
    emit mouseMoved(scenePos);

    ///右键拖拽功能
    if (this->isDragging) {
        // 计算移动的距离
        QPointF delta = mapToScene(e->pos()) - mapToScene(this->DraggingPos);
        Translate(delta);
        scene->setSceneRect(scene->sceneRect().translated(delta));
        this->DraggingPos = e->pos(); // 更新上一个位置
    }

    ///左键画图功能
    switch (drawStep) {
    ///TO step1
    case 1:{
        if(pts.size()<2){
            pts.resize(2);}
        pts[1] = mapToScene(e->pos());
          viewport()->update();  // 请求重绘
        //        qDebug()<<"move painting step1...";
    };break;
    case 2:{
        if(pts.size()<3){
            pts.resize(3);}
        pts[2] = mapToScene(e->pos());
           viewport()->update(); // 请求重绘
        //        qDebug()<<"move painting step2...";
    };break;
    default: break;
    }


    return QGraphicsView::mouseMoveEvent(e);
}



void GraphicsView::mouseReleaseEvent(QMouseEvent *e)
{
    ///右键鼠标释放
    if (e->button() == Qt::RightButton) {
        this->isDragging= false;
        setCursor(Qt::CrossCursor);
    }


    ///左键鼠标释放
    if (e->button() == Qt::LeftButton){

        ///选择画图信号
        switch (figureChosed)
        {
        ///显示点的坐标
        case figure::POINT: {

            return QGraphicsView::mousePressEvent(e);

            //            QMessageBox::information(this, "坐标点信息", \
            //                                     "当前坐标:("+QString::number(scenePos.x())+\
            //                                     ","+QString::number(scenePos.y())+")",\
            //                                     QMessageBox::Ok);

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
            if((this->pts.size()==3)&&(this->drawStep==0)){
                emit sg_califrom3pts();
            }

        };break;
        case figure::MS3PTS:{
            if((this->pts.size()==3)&&(this->drawStep==0)){
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
        case figure::PTS3MSAGL:{
            if(this->pts.size()==3){
                emit sg_pts3MsAgl();
            }
        };break;
        default:{
        };break;
        }

    }///左键释放
    QGraphicsView::mouseReleaseEvent(e);
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

void GraphicsView::Translate(QPointF delta){
    // 获取当前视图的中心位置
    QPointF currentCenter = mapToScene(viewport()->rect().center());

    // 计算新的中心位置
    QPointF newCenter = currentCenter - delta; // 使用 delta 直接更新位置

    // 将视图中心设置为新的位置
    centerOn(newCenter);
}
void GraphicsView::enterEvent(QEvent *e)
{
    QGraphicsView::enterEvent(e);
    setCursor(Qt::CrossCursor);
}




