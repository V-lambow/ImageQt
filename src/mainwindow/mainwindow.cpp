#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    leftScene = new QGraphicsScene;
    rightScene = new QGraphicsScene;

    leftPixmapItem = new QGraphicsPixmapItem();
    rightPixmapItem = new MyGraphicsPixmapItem();

    size = new QLabel;

    info = nullptr;

    leftScene->setBackgroundBrush(QColor::fromRgb(224,224,224));
    ui->leftGraphicsView->setScene(leftScene);
    rightScene->setBackgroundBrush(QColor::fromRgb(224,224,224));
    ui->rightGraphicsView->setScene(rightScene);

    ui->statusBar->addPermanentWidget(size);
    ui->statusBar->addPermanentWidget(this->curResolutionName.get());

    ///实时显示坐标
    QLabel *pixLabel=new QLabel("当前坐标:(X,Y)",this);
    ui->statusBar->addWidget(pixLabel);

    connect(ui->rightGraphicsView,&GraphicsView::mouseMoved,this,[pixLabel](const QPointF& pt){
        pixLabel->setText(QString("当前坐标:( %1 , %2 )").arg(pt.x()).arg(pt.y()));
    });






    createAction();
    createToolBar();


    setActionStatus(false);
    setWindowTitle("ImageQt");

    ///画图链接

    connect(ui->rightGraphicsView,&GraphicsView::sg_drawLine,this,&MainWindow::on_actiondistancePP_triggered);

    connect(ui->rightGraphicsView,&GraphicsView::sg_califrom3pts,this,&MainWindow::on_actioncaliFrom3Pts_triggered);

    connect(ui->rightGraphicsView,&GraphicsView::sg_msfrom3pts,this,&MainWindow::on_actionmeasureFrom3Pts_triggered);

    connect(ui->rightGraphicsView,&GraphicsView::sg_drawRect1,this,&MainWindow::on_actionrect1Area_triggered);

    connect(ui->rightGraphicsView,&GraphicsView::sg_polyArea,this,&MainWindow::on_actionpolyArea_triggered);

    connect(ui->rightGraphicsView,&GraphicsView::sg_pts3MsAgl,this,&MainWindow::on_action3ptsMsAngle_triggered);




}

///工具栏
void MainWindow::createToolBar()
{
    ui->toolBar->addAction(ui->actionOpen);
    ui->toolBar->addAction(ui->actionSave);
    ui->toolBar->addAction(ui->actionClose);

    ui->toolBar->addSeparator();

    ui->toolBar->addAction(ui->actionRestore);
    ui->toolBar->addAction(ui->actionHistogram);

    ui->toolBar->addSeparator();

    ui->toolBar->addAction(ui->actionopenDevice);
    ui->toolBar->addAction(ui->actionstopGrab);
    ui->toolBar->addAction(ui->actiondisconnect);

    ui->toolBar->addSeparator();
    ui->toolBar->addSeparator();

    ui->toolBar->addAction(ui->actioncapture);
    ui->toolBar->addAction(ui->actionpicBefore);
    ui->toolBar->addAction(ui->actionpicNext);
    ui->toolBar->addAction(ui->actioneraserLast);
    ui->toolBar->addAction(ui->actionimageLeap);

    ui->toolBar->addSeparator();
    ui->toolBar->addSeparator();

    ui->toolBar->addAction(ui->actioncaliFrom3Pts);
    ui->toolBar->addAction(ui->actionmeasureFrom3Pts);



//    QWidget savedImgName= QWidget(this);
//    ui->toolBar->addWidget(&savedImgName);
//    savedImgName


}

void MainWindow::createAction()
{

}



MainWindow::~MainWindow()
{
    delete ui;

    if (leftScene)
    {
        delete leftScene;
        leftScene = nullptr;
    }

    if (size)
    {
        delete size;
        size = nullptr;
    }

    //add
    if (rightScene)
    {
        delete leftScene;
        leftScene = nullptr;
    }



    freeTgrabImg();

}


/******************************************************************************
 *                Update right image and repaint right scene
 *****************************************************************************/
void MainWindow::updateRightImage(QPixmap &pixmap)
{
    rightPixmapItem->setPixmap(pixmap);
    rightScene->setSceneRect(QRectF(pixmap.rect()));
}

/******************************************************************************
 *                      Clean image of both Scene
 *
 *****************************************************************************/
void MainWindow::cleanImage(QString whichSide)
{
    freeTgrabImg();
    if(whichSide=="left"){
        leftScene->clear();
        leftPixmapItem=nullptr;
        ui->leftGraphicsView->resetTransform();
    }
    else if(whichSide=="right"){
        rightScene->clear();
        rightPixmapItem=nullptr;
        ui->rightGraphicsView->resetTransform();
    }
    else{

        on_actiondisconnect_triggered();
        leftScene->clear();
        leftPixmapItem=nullptr;
        ui->leftGraphicsView->resetTransform();
        rightScene->clear();
        rightPixmapItem=nullptr;
        ui->rightGraphicsView->resetTransform();
    }

    if (size)
    {
        delete size;
        size = new QLabel;
        ui->statusBar->addPermanentWidget(size);
        std::unique_ptr<QLabel> curResolutionName=std::make_unique<QLabel>();

        ui->statusBar->addPermanentWidget(curResolutionName.get());
    }



    this->setWindowTitle(WINDOW_TITLE);
    setActionStatus(false);
}

void MainWindow::setActionStatus(bool status)
{
    ui->actionPrewitt->setEnabled(status);
    ui->actionContour_extraction->setEnabled(status);
    ui->actionEdge_following->setEnabled(status);
    // sharpen
    ui->actionLaplace->setEnabled(status);
    ui->actionSobel->setEnabled(status);
    //ui->actionEdge_Detection->setEnabled(status);
    // Blur
    ui->actionSimple->setEnabled(status);
    ui->actionGauss->setEnabled(status);
    ui->actionMeida_Filter->setEnabled(status);
    // Grey Transform
    ui->actionBinaryzation->setEnabled(status);
    ui->actionStretch_transformation->setEnabled(status);
    ui->actionExp_transfrom->setEnabled(status);
    ui->actionTwo_thresholds_transform->setEnabled(status);
    ui->actionPower_transformation->setEnabled(status);
    ui->actionLogarithm_grey_level_transformation->setEnabled(status);
    ui->actionSave->setEnabled(status);
    ui->actionClose->setEnabled(status);
    ui->actionSave_As->setEnabled(status);

    ui->actionCool->setEnabled(status);
    ui->actionWarm->setEnabled(status);
    ui->actionFlower_frame->setEnabled(status);
    ui->actionGrayscale->setEnabled(status);
    ui->actionHistogram->setEnabled(status);
    ui->actionHorizontal->setEnabled(status);
    ui->actionLeft->setEnabled(status);
    ui->actionLinear_level_transformation->setEnabled(status);
    ui->actionMetal->setEnabled(status);
    ui->actionMovie_frame->setEnabled(status);
    ui->actionNormal->setEnabled(status);
    ui->actionRestore->setEnabled(status);
    ui->actionVertical->setEnabled(status);
    ui->actionClassic_frame->setEnabled(status);
    ui->actionAdjust_brightness->setEnabled(status);
    ui->zoomAction->setEnabled(status);
    //***********dzy******************//
    ui->actioncaliFrom3Pts->setEnabled(status);
    ui->actionmeasureFrom3Pts->setEnabled(status);
    ui->actionOpening->setEnabled(status);
    ui->actionClosing->setEnabled(status);
    ui->actionThinning->setEnabled(status);
    ui->actionDilate->setEnabled(status);
    ui->actionExpansion->setEnabled(status);
    ui->actionRotate->setEnabled(status);
    ui->actionrect1Area->setEnabled(status);
    ui->actionpolyArea->setEnabled(status);
    ui->action3ptsMsAngle->setEnabled(status);
    ui->actiondistancePP->setEnabled(status);
    ui->actionresolutionManage->setEnabled(status);
}

void MainWindow::setDrawActionStatus(bool status){
    ui->action3ptsMsAngle->setEnabled(status);
    ui->actiondistancePP->setEnabled(status);
    ui->actioncaliFrom3Pts->setEnabled(status);
    ui->actionmeasureFrom3Pts->setEnabled(status);
    ui->actionpolyArea->setEnabled(status);
    ui->actionrect1Area->setEnabled(status);
}




void MainWindow::setHKcamActionStatus(bool status){
    ui->actionopenDevice->setEnabled(status);
    ui->actionsetSpecInfo->setEnabled(status);
    ui->actiondisconnect->setEnabled(status);
    ui->actioncapture->setEnabled(status);
    ui->actionstopGrab->setEnabled(status);

}



void MainWindow::receiveGaussianFactor(int radius, double sigma)
{
    GaussianBlur *blur = new GaussianBlur(radius, sigma);

    QPixmap rightImage = rightPixmapItem->pixmap();

    QImage newImage = blur->BlurImage(rightImage.toImage());
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}

///******************************************************************************
// *                   Receive data from zoom dialog
// *             and then call the function to done zoom action
// *****************************************************************************/
//void MainWindow::receiveZoomFactor(int factor)
//{
//    qDebug()<<"zoom factor:"<<factor;

//    if (factor != 100)
//    {
//        QPixmap rightImage = rightPixmapItem->pixmap();

//        int cur_width = rightImage.width();
//        int cur_height = rightImage.height();

//        QPixmap newPixmap = rightImage.scaled(cur_width*factor/100, cur_height*factor/100);

//        updateRightImage(newPixmap);
//    }
//    else
//    {
//        return;
//    }
//}

void MainWindow::receiveLinearGreyParameter(double _a, double _b)
{
    QPixmap rightImage = rightPixmapItem->pixmap();

    QImage newImage = Tools::LinearLevelTransformation(rightImage.toImage(), _a, _b);
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}

void MainWindow::receivePowerGreyParamter(double c, double r, double b)
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImage = Tools::PowerGreyLevelTransformation(rightImage.toImage(), c, r, b);
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}

void MainWindow::receiveLogGreyParamter(double _a, double _b)
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImage = Tools::LinearLevelTransformation(rightImage.toImage(), _a, _b);
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}

void MainWindow::receiveExpGreyParamter(double b, double c, double a)
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImage = Tools::ExpTransform(rightImage.toImage(), b, c, a);
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}

void MainWindow::receiveTwoThresholdParamter(int t1, int t2, int option)
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImage = Tools::TwoThreshold(rightImage.toImage(), t1, t2, option);
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}

void MainWindow::receiveStretchParamter(int x1, int x2,
                                        double k1, double k2, double k3,
                                        double b2, double b3)
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImage = Tools::StretchTransform(rightImage.toImage(),x1,x2,k1,k2,k3,b2,b3);
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}

//void MainWindow::receiveCaliFrom3ptsParamter(double x ,double y)
//{

//}




/******************************************************************************
 *                      Open a image file and show it
 ******************************************************************************
 * Args:
 *      QString imagePath: The abslute path of a image
 *****************************************************************************/
void MainWindow::on_actionOpen_triggered()
{
    freeTgrabImg();
    // Automatically detects the current user's home directory
    // And then wait the user to select one image
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open image"), getUserPath() + "/Pictures",
                                                     tr("All Files (*);;"
                                                        "All Images (*.bmp *.gif *.jpg *.jpeg *.png *.ppm *.xbm *.xpm);;"
                                                        "Image BPM (*.bmp);;"
                                                        "Image GIF (*.gif);;"
                                                        "Image JPG (*.jpg);;"
                                                        "Image JPEG (*.jpeg);;"
                                                        "Image PNG (*.png);;"
                                                        "Image PPM (*.ppm);;"
                                                        "Image XBM (*.xbm);;"
                                                        "Image XPM (*.xpm);;"));

    if (!imagePath.isEmpty())
    {
        QFile file(imagePath);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr(WINDOW_CRITICAL),
                                  tr("Unable to open image."));
            return;
        }

        // delete previous image
//        cleanImage("both");

        // upload image
        info = new QFileInfo(imagePath);

        QPixmap leftPixmap(imagePath);

        leftPixmapItem = leftScene->addPixmap(leftPixmap);
        leftScene->setSceneRect(QRectF(leftPixmap.rect()));

        QPixmap rightPixmap(imagePath);
        //dzy1025
        rightPixmapItem=new MyGraphicsPixmapItem();
        rightPixmapItem->setPixmap(rightPixmap);
        rightScene->addItem(rightPixmapItem);
        rightScene->setSceneRect(QRectF(rightPixmap.rect()));

        // settings
        this->setWindowTitle(info->fileName() + " - ImageQt");

        setActionStatus(true);

        size->setText(QString::number(leftPixmapItem->pixmap().width())
                      + " x " + QString::number(leftPixmapItem->pixmap().height()));
        QString name;
        if(curReslution!=0.0){
            std::for_each(this->resolution->begin(),this->resolution->end(),[this,&name](std::pair<QString,double> resolutionEle){
                if(resolutionEle.second==curReslution){
                    name=resolutionEle.first;
                }
            });
        }
        this->ImgDqe.clear();
        this->curResolutionName.get()->setText("当前标定命名："+name);

    }
}

/******************************************************************************
 *                      Clean image of both Scene
 *
 *****************************************************************************/
void MainWindow::on_actionClose_triggered()
{
    do{
    ///如果相机没有打开
    if((this->nRet!=MV_OK) && (this->HkHandle==nullptr)){
        QMessageBox::warning(this,"警告","请先打开相机"+QString::number(this->nRet), QMessageBox::Ok);
        break;
    }
    ///相机打开则暂停
    if(this->hkStopFlg==false){
        on_actionstopGrab_triggered();
    }
    ui->rightGraphicsView->figureChosed=figure::POINT;
    cleanImage("both");
    }while(0);
}

void MainWindow::on_actionSave_triggered()
{


    imageNamedDlg dlg(this);
    connect(&dlg, &imageNamedDlg::sendData,[this](QString str){
        this->savedImage.addImage(this->rightPixmapItem->pixmap().toImage(),str);
        qDebug()<<"图像已保存";
        this->savedShowIdx++;
    });
    dlg.exec();

}

/******************************************************************************
 *                          Action : Save as
 *****************************************************************************/
void MainWindow::on_actionSave_As_triggered()
{

    QString newPath = QFileDialog::getSaveFileName(this, tr("Save image"), QString(),
                                                   tr("All files (*);;"
                                                      "Image BMP (*.bmp);;"
                                                      "Image GIF (*.gif);;"
                                                      "Image JPG (*.jpg);;"
                                                      "Image JPEG (*.jpeg);;"
                                                      "Image PNG (*.png);;"
                                                      "Image PPM (*.ppm);;"
                                                      "Image XBM (*.xbm);;"
                                                      "Image XPM (*.xpm);;"));

    if (!newPath.isEmpty()) {

        QFile file(newPath);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, tr(WINDOW_CRITICAL), tr("Unable to save image."));
            return;
        }

        //Save image to new path
        rightPixmapItem->pixmap().save(newPath);
        //        rightImage->save(newPath);
    }
}

/******************************************************************************
 *                        Exit the program
 *
 *****************************************************************************/
void MainWindow::on_actionExit_triggered()
{
    qApp->quit();
}




/******************************************************************************
 *                              Greyscale
 *****************************************************************************/
void MainWindow::on_actionGrayscale_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImage = Tools::GreyScale(rightImage.toImage());
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}



/******************************************************************************
 *                  Adjust the image size to fit the window
 *
 *****************************************************************************/
void MainWindow::on_actionAdjust_triggered()
{
    // left
    int height = leftPixmapItem->pixmap().height();
    int width = leftPixmapItem->pixmap().width();
    int max_height = ui->leftGraphicsView->height();
    int max_width = ui->leftGraphicsView->width();
    int size,max_size,fact=0;
    double val=0;


    size = qMin(width,height);
    max_size = qMin(max_width,max_height);


    if (size < max_size) {
        while ((size*val) < max_size)
            val = pow(1.2,fact++);
        val = pow(1.2,fact-2);
        ui->leftGraphicsView->setFactor(fact-2);
    }

    else {
        val = 1;
        while ((size*val) > max_size)
            val = pow(1.2,fact--);
        val = pow(1.2,fact+1);
        ui->leftGraphicsView->setFactor(fact+1);
    }

    ui->leftGraphicsView->scale(val,val);


    // right
    height = leftPixmapItem->pixmap().height();
    width = leftPixmapItem->pixmap().width();
    max_height = ui->rightGraphicsView->height();
    max_width = ui->rightGraphicsView->width();
    size = max_size = fact = 0;
    val=0;


    size = qMin(width,height);
    max_size = qMin(max_width,max_height);


    if (size < max_size) {
        while ((size*val) < max_size)
            val = pow(1.2,fact++);
        val = pow(1.2,fact-2);
        ui->rightGraphicsView->setFactor(fact-2);
    }

    else {
        val = 1;
        while ((size*val) > max_size)
            val = pow(1.2,fact--);
        val = pow(1.2,fact+1);
        ui->rightGraphicsView->setFactor(fact+1);
    }

    ui->rightGraphicsView->scale(val,val);
}




/******************************************************************************
 *                   Restore the image, both size and rotate
 *****************************************************************************/
void MainWindow::on_actionRestore_triggered()
{
    on_actionNormal_triggered();

}

/******************************************************************************
 *                           绘制图像直方图
 *****************************************************************************/
void MainWindow::on_actionHistogram_triggered()
{

    QDialog * hstgrmDialog = new QDialog(this);
    QScrollArea * scrollArea = new QScrollArea(hstgrmDialog);
    Histogram * hstgrm = new Histogram(scrollArea);
    hstgrm->computeHstgrm(rightPixmapItem->pixmap().toImage());

    if (hstgrm == nullptr)
        return;


    scrollArea->setWidget(hstgrm);

    QHBoxLayout * layout = new QHBoxLayout;
    layout->addWidget(scrollArea);
    hstgrmDialog->setLayout(layout);

    hstgrm->resize(800, 780);
    hstgrmDialog->setFixedWidth(820);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->adjustSize();

    hstgrmDialog->setWindowTitle("Histogram - ImageQt");

    hstgrmDialog->show();
}


/******************************************************************************
 *                              Add frame
 *****************************************************************************/
void MainWindow::on_actionMovie_frame_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage frame = QImage(":/img/frame_3.png");
    QImage newImage = Tools::DrawFrame(rightImage.toImage(), frame);
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}

void MainWindow::on_actionClassic_frame_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage frame = QImage(":/img/frame_1.png");
    QImage newImage = Tools::DrawFrame(rightImage.toImage(), frame);
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}

void MainWindow::on_actionFlower_frame_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage frame = QImage(":/img/frame_2.png");
    QImage newImage = Tools::DrawFrame(rightImage.toImage(), frame);
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}

/******************************************************************************
 *                          Add metal texture
 *****************************************************************************/
void MainWindow::on_actionMetal_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImage = Tools::Metal(rightImage.toImage());
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}

/******************************************************************************
 *                              Cool
 *****************************************************************************/
void MainWindow::on_actionCool_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImage = Tools::Cool(30, rightImage.toImage());
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}

/******************************************************************************
 *                              Warm
 *****************************************************************************/
void MainWindow::on_actionWarm_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImage = Tools::Warm(30, rightImage.toImage());
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}




/******************************************************************************
 *                             简单平滑
 *****************************************************************************/
void MainWindow::on_actionSimple_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImage = Tools::SimpleSmooth(rightImage.toImage());
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}

/******************************************************************************
 *                             高斯平滑
 *****************************************************************************/
void MainWindow::on_actionGauss_triggered()
{
    GaussianBlurDialog dialog;
    connect(&dialog, SIGNAL(sendData(int, double)), this,
            SLOT(receiveGaussianFactor(int, double)));

    dialog.exec();
}

/******************************************************************************
 *                              中值滤波
 *****************************************************************************/
void MainWindow::on_actionMeida_Filter_triggered()
{
    bool ok;
    int value = QInputDialog::getInt(this, tr("Media Filter"), "Input a value for radius(1~30)",3,1,30,1,&ok);
    if (ok)
    {
        QPixmap rightImage = rightPixmapItem->pixmap();
        QImage newImage = Tools::MeidaFilter(rightImage.toImage(), value);
        rightImage.convertFromImage(newImage);

        updateRightImage(rightImage);
    }
}


/******************************************************************************
 *                     on Action tools->zoom triggered
 *****************************************************************************/
void MainWindow::on_zoomAction_triggered()
{

    bool ok;
    int factor = QInputDialog::getInt(this, tr("Zoom"), "Input a value for zoom ratio(%)",100,10,1000,10,&ok);
    if (ok)
    {
        if (factor != 100)
        {
            QPixmap rightImage = rightPixmapItem->pixmap();

            int cur_width = rightImage.width();
            int cur_height = rightImage.height();

            QPixmap newPixmap = rightImage.scaled(cur_width*factor/100, cur_height*factor/100);

            updateRightImage(newPixmap);
        }
        else
        {
            return;
        }
    }

}

/******************************************************************************
 *                          Flip Horizontal
 *****************************************************************************/
void MainWindow::on_actionHorizontal_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImage = Tools::Horizontal(rightImage.toImage());
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}

/******************************************************************************
 *                          Flip Vertical
 *****************************************************************************/
void MainWindow::on_actionVertical_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImage = Tools::Vertical(rightImage.toImage());
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}




/******************************************************************************
 *                           灰度线性变换 y = ax + b
 *****************************************************************************/
void MainWindow::on_actionLinear_level_transformation_triggered()
{
    LinearGrayDialog dialog;
    connect(&dialog, SIGNAL(sendData(double, double)),
            this, SLOT(receiveLinearGreyParameter(double,double)));
    dialog.exec();
}

/******************************************************************************
 *                             灰度幂次变换
 *****************************************************************************/
void MainWindow::on_actionPower_transformation_triggered()
{
    DialogPowerGrey dialog;
    connect(&dialog, SIGNAL(sendData(double, double, double)),
            this, SLOT(receivePowerGreyParamter(double,double,double)));
    dialog.exec();
}

/******************************************************************************
 *                       灰度对数变换 y = log(b+x)/log(a)
 *****************************************************************************/
void MainWindow::on_actionLogarithm_grey_level_transformation_triggered()
{
    DialogLogGrey dialog;
    connect(&dialog, SIGNAL(sendData(double, double)),
            this, SLOT(receiveLogGreyParamter(double,double)));
    dialog.exec();
}

/******************************************************************************
 *                             灰度指数变换
 *****************************************************************************/
void MainWindow::on_actionExp_transfrom_triggered()
{
    DialogExpTransform dialog;
    connect(&dialog, SIGNAL(sendData(double, double, double)),
            this, SLOT(receiveExpGreyParamter(double,double,double)));
    dialog.exec();
}

/******************************************************************************
 *                             灰度双阈值变换
 *****************************************************************************/
void MainWindow::on_actionTwo_thresholds_transform_triggered()
{
    DialogThresholdTransform dialog;
    connect(&dialog, SIGNAL(sendData(int, int, int)),
            this, SLOT(receiveTwoThresholdParamter(int,int,int)));
    dialog.exec();
}

/******************************************************************************
 *                             灰度拉伸变换
 *****************************************************************************/
void MainWindow::on_actionStretch_transformation_triggered()
{
    DialogStretchTransform dialog;
    connect(&dialog, SIGNAL(sendData(int,int,double,double,double,double,double)),
            this, SLOT(receiveStretchParamter(int,int,double,double,double,double,double)));
    dialog.exec();
}

/******************************************************************************
 *                           laplace sharpen
 *****************************************************************************/
void MainWindow::on_actionLaplace_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImage = Tools::LaplaceSharpen(rightImage.toImage());
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}

void MainWindow::on_actionSobel_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImage = Tools::SobelEdge(rightImage.toImage());
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}


void MainWindow::on_actionBinaryzation_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImage = Tools::Binaryzation(rightImage.toImage());
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}



/******************************************************************************
 *                          调整亮度
 *****************************************************************************/
void MainWindow::on_actionAdjust_brightness_triggered()
{
    bool ok;
    int delta = QInputDialog::getInt(this,
                                     tr("Brightness"),
                                     "Input a value for brightness(+/-)",
                                     0,-1000,1000,10,&ok);
    if (ok)
    {
        if (delta != 100)
        {
            QPixmap rightImage = rightPixmapItem->pixmap();

            QImage newImage = Tools::Brightness(delta, rightImage.toImage());
            rightImage.convertFromImage(newImage);

            updateRightImage(rightImage);
        }
        else
        {
            return;
        }
    }

}


/******************************************************************************
 *                              To do
 *****************************************************************************/
void MainWindow::on_actionNormal_triggered()
{
    QPixmap leftImage = leftPixmapItem->pixmap();
    updateRightImage(leftImage);
    ui->rightGraphicsView->resetTransform();
}




/******************************************************************************
 *                              “关于”窗口
 *****************************************************************************/
void MainWindow::on_actionAbout_triggered()
{
    QMessageBox message(QMessageBox::NoIcon, tr(WINDOW_ABOUT), "<h1>ImageQt</h1>"
                                                               "Powered By Qt 5.12.0.");
    message.setIconPixmap(QPixmap(":/img/logo_1.png"));
    message.exec();
}


/******************************************************************************
 *                           获得当前用户的用户名
 *****************************************************************************/
QString MainWindow::getUserName()
{
    QString userPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString userName = userPath.section("/", -1, -1);
    return userName;
}

/******************************************************************************
 *                              获得当前用户的家目录
 *****************************************************************************/
QString MainWindow::getUserPath()
{
    QString userPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    return userPath;
}

//void MainWindow::on_actionT_triggered()
//{
//    QLabel* l = new QLabel;
//    if (!rightPixmapItem->pixmap().isNull()) {
//        qDebug() << "hello";
//        l->setPixmap(rightPixmapItem->pixmap());
//        l->show();
//    }
//}

/******************************************************************************
 *                              Prewitt边缘检测
 *****************************************************************************/
void MainWindow::on_actionPrewitt_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImage = Tools::PrewittEdge(rightImage.toImage());
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}


/******************************************************************************
 *                              轮廓提取法
 *****************************************************************************/
void MainWindow::on_actionContour_extraction_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImage = Tools::ContourExtraction(rightImage.toImage());
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}

void MainWindow::on_actionArea_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImg = rightImage.toImage();
    QImage binImg = Tools::Binaryzation(newImg);
    int area = 0;
    for(int x=0; x<binImg.width(); x++)
    {
        for(int y=0; y<binImg.height(); y++)
        {
            if (QColor(binImg.pixel(x,y)).red() == 0)
                area ++;
        }
    }

    QMessageBox *message =new QMessageBox(QMessageBox::NoIcon,QObject::tr("面积计算"),"连通区域的面积为："+QString::number(area));
    message->show();
}


void MainWindow::on_actionCircumference_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage newImg = rightImage.toImage();
    QImage sobelImg = Tools::SobelEdge(newImg);
    sobelImg = Tools::Binaryzation(sobelImg);
    int c = 0;
    for(int x=0; x<sobelImg.width(); x++)
    {
        for(int y=0; y<sobelImg.height(); y++)
        {
            if (QColor(sobelImg.pixel(x,y)).red() == 0)
                c ++;
        }
    }
    QMessageBox *message =new QMessageBox(QMessageBox::NoIcon,QObject::tr("周长计算"),"连通区域的周长为："+QString::number(c));
    message->show();
}



void MainWindow::on_actionDilate_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage binaryImage = Tools::Binaryzation(rightImage.toImage());
    QImage newImage = Tools::Dilate(binaryImage);
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}

void MainWindow::on_actionExpansion_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage binaryImage = Tools::Binaryzation(rightImage.toImage());
    QImage newImage = Tools::Expansion(binaryImage);
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}

/*****************************************************************************
 *                                 开运算
 * **************************************************************************/
void MainWindow::on_actionOpening_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage binaryImage = Tools::Binaryzation(rightImage.toImage());
    QImage newImage = Tools::Opening(binaryImage);
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}


/*****************************************************************************
 *                                 闭运算
 * **************************************************************************/
void MainWindow::on_actionClosing_triggered()
{

    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage binaryImage = Tools::Binaryzation(rightImage.toImage());
    QImage newImage = Tools::Closing(binaryImage);
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);
}

/*****************************************************************************
 *                                 图像细化
 * **************************************************************************/
void MainWindow::on_actionThinning_triggered()
{
    QPixmap rightImage = rightPixmapItem->pixmap();
    QImage imgTmp =Tools::GreyScale(rightImage.toImage());
    imgTmp=imgTmp.convertToFormat(QImage::Format_Grayscale8);
    if (imgTmp.isNull() || imgTmp.format() != QImage::Format_Grayscale8) {
        QMessageBox::warning(this, "警告", + "The input image must be a non-null grayscale image.", QMessageBox::Ok);
        //            throw std::invalid_argument("The input image must be a non-null grayscale image.");
        return;
    }
    QImage newImage = Tools::Thinning(imgTmp);
    rightImage.convertFromImage(newImage);

    updateRightImage(rightImage);

}


//void MainWindow::on_actionRGB2HSV_triggered()
//{
//    QPixmap rightImage = rightPixmapItem->pixmap();
//    QImage newImage = Tools::RGB2HSV(rightImage.toImage());
//    rightImage.convertFromImage(newImage);

//    updateRightImage(rightImage);
//}

//void MainWindow::on_actionRGB2HSL_triggered()
//{
//    QPixmap rightImage = rightPixmapItem->pixmap();
//    QImage newImage = Tools::RGB2HSL(rightImage.toImage());
//    rightImage.convertFromImage(newImage);

//    updateRightImage(rightImage);
//}

//void MainWindow::on_actionRGB2Cmyk_triggered()
//{
//    QPixmap rightImage = rightPixmapItem->pixmap();
//    QImage newImage = Tools::RGB2CMYK(rightImage.toImage());
//    rightImage.convertFromImage(newImage);

//    updateRightImage(rightImage);
//}

void MainWindow::on_actionRotate_triggered()
{
    bool ok;
    int factor = QInputDialog::getInt(this, tr("旋转"), "请输入要旋转的角度（正数向右，负数向左）",0,-360,360,10,&ok);
    if (ok)
    {
        if (factor != 0)
        {
            QPixmap rightImage = rightPixmapItem->pixmap();

            QImage *imgRotate = new QImage;
            QMatrix matrix;
            matrix.rotate(factor);
            *imgRotate = rightImage.toImage().transformed(matrix);
            QPixmap newPixmap;
            newPixmap = QPixmap::fromImage(*imgRotate);
            updateRightImage(newPixmap);
        }
        else
        {
            return;
        }
    }
}

/*****************************dzy******************************
                            三点标定
***************************************************************/

void  MainWindow::on_actioncaliFrom3Pts_triggered(){



  ///初始化结果输出
  if(ui->rightGraphicsView->figureChosed==figure::POINT){
      ///第一次点击
        setDrawActionStatus(false);
        this->rightPixmapItem->grabMouse();
        this->ImgDqe.push(this->rightPixmapItem->pixmap().toImage());
      ui->rightGraphicsView->pts.clear();
      ui->rightGraphicsView->figureChosed=figure::CALI3PTS;
      this->rightPixmapItem->figureChosed =figure::CALI3PTS;

//      auto item =std::make_unique<Mygraphicsitem>();
//      rightScene->addItem(item.get());
//      auto item =new Mygraphicsitem();
    }
  else if((ui->rightGraphicsView->figureChosed==figure::CALI3PTS) && \
          (ui->rightGraphicsView->pts.size()==3)){
      ///弹出dialog设置分辨率
      QPixmap rightImage = rightPixmapItem->pixmap();
      CaliFrom3PtsDlg dialog;
      QString name ="";
      connect(&dialog, &CaliFrom3PtsDlg::sendData, this, [this,&name](QString nameTmp,double x) {

          // 显示计算得到的实际距离
          QMessageBox::information(this, "计算得到的实际距离（um）",
                                   QString::number(x) + "(um)", QMessageBox::Ok);
          this->curReslution=x;
          name=nameTmp;

        });

      dialog.exec();
      auto[newImage,lenPix]  = Tools::PaintLineAPt(rightImage.toImage(),\
              QLineF(ui->rightGraphicsView->pts.at(0),\
              ui->rightGraphicsView->pts.at(1)),\
              ui->rightGraphicsView->pts.at(2),\
              this->curReslution,\
              "calibration",\
              &this->painter);
              rightImage.convertFromImage(newImage);
              updateRightImage(rightImage);
              this->curReslution/=lenPix;
              this->resolution.get()->insert({name,this->curReslution});
      ui->rightGraphicsView->figureChosed=figure::POINT;
      setDrawActionStatus(true);
      this->rightPixmapItem->ungrabMouse();
      this->rightPixmapItem->figureChosed =figure::POINT;

    }
  else{
      ui->rightGraphicsView->figureChosed=figure::POINT;
      this->rightPixmapItem->figureChosed =figure::POINT;
      return;
    }
  QString name;
  if(curReslution!=0.0){
      std::for_each(this->resolution->begin(),this->resolution->end(),[this,&name](std::pair<QString,double> resolutionEle){
          if(resolutionEle.second==curReslution){
              name=resolutionEle.first;
          }
      });
  }
  this->curResolutionName.get()->setText("当前标定命名："+name);

  //    while(pts.size()<3){
  //        QMouseEvent *e = nullptr;
  //        ui->leftGraphicsView->mousePressEvent(e);
  //        if(ui->leftGraphicsView->pts.size()==3){
  //            std::copy(ui->leftGraphicsView->pts.begin(),ui->leftGraphicsView->pts.end(),pts.begin());
  //            break;
  //        }
  //    }
  ///画图
  //    QPainter painter;

  //    QPointF scenePos1 = pts.at(0);
  //    QPointF scenePos2 = pts.at(1);
  //    painter.drawLine(scenePos1,scenePos2);

  //    QPointF scenePos3 = pts.at(2);
  //    double k=(scenePos3.x()-scenePos1.x())*(scenePos2.x()-scenePos1.x())+\
  //            (scenePos3.y()-scenePos1.y())*(scenePos2.y()-scenePos1.y())/\
  //            pow((scenePos2.x()-scenePos1.x()),2)+pow(scenePos2.y()-scenePos1.y(),2);
  //    painter.drawLine(QPointF(scenePos1.x()+k*(scenePos2.x()-scenePos1.x()),scenePos1.y()+k*(scenePos2.y()-scenePos1.y())),scenePos3);
  //    double len =QLineF(QPointF(scenePos1.x()+k*(scenePos2.x()-scenePos1.x()),scenePos1.y()+k*(scenePos2.y()-scenePos1.y())),scenePos3).length();
  //    painter.drawText(QRect(QPoint(scenePos1.x()+k*(scenePos2.x()-scenePos1.x()),scenePos1.y()+k*(scenePos2.y()-scenePos1.y())),scenePos3.toPoint()),QString::number(len));

  //    QPixmap rightImage = rightPixmapItem->pixmap();
  //    QImage binaryImage = Tools::Binaryzation(rightImage.toImage());
  //    QImage newImage = Tools::Opening(binaryImage);
  //    rightImage.convertFromImage(newImage);

  //    updateRightImage(rightImage);
  //    ui->leftGraphicsView->ptNum=1;
}
/************************************************************
 *                          两点距离
 * *************************************************************/
void MainWindow::on_actiondistancePP_triggered(){


    ///初始化结果输出

    if(ui->rightGraphicsView->figureChosed==figure::POINT){
            setDrawActionStatus(false);
            this->rightPixmapItem->grabMouse();
            this->rightPixmapItem->figureChosed =figure::LINE;

//            this->ImgTmp=this->rightPixmapItem->pixmap().toImage().copy();
            this->ImgDqe.push(this->rightPixmapItem->pixmap().toImage());


        ui->rightGraphicsView->pts.clear();
        ui->rightGraphicsView->figureChosed=figure::LINE;
    }
    else if((ui->rightGraphicsView->figureChosed==figure::LINE) && \
            (ui->rightGraphicsView->pts.size()==2)){
        ui->rightGraphicsView->figureChosed=figure::POINT;
        QPixmap rightImage = rightPixmapItem->pixmap();
        auto[newImage,lenPix]  = Tools::PaintLine(rightImage.toImage(),\
                QLineF(ui->rightGraphicsView->pts.at(0),\
                ui->rightGraphicsView->pts.at(1)),\
                this->curReslution,
                &this->painter);
                rightImage.convertFromImage(newImage);
                updateRightImage(rightImage);
//                double lenPixActual=lenPix*this->curReslution;
                if(lenPix==0){
            //没有进行过标定
            QMessageBox::information(this, "计算得到的实际距离（um）",
                                     "请先进行标定", QMessageBox::Ok);
        }
        else{
            QMessageBox::information(this, "计算得到的实际距离（um）",
                                     QString::number(lenPix*this->curReslution) + "(um)", QMessageBox::Ok);
        }

        setDrawActionStatus(true);
        this->rightPixmapItem->ungrabMouse();
        this->rightPixmapItem->figureChosed =figure::POINT;



    }
    else{
        ui->rightGraphicsView->figureChosed=figure::POINT;
        this->rightPixmapItem->figureChosed =figure::POINT;
        return;
    }

}






/*****************************dzy******************************
                            三点测量
***************************************************************/
void  MainWindow::on_actionmeasureFrom3Pts_triggered(){


    ///初始化结果输出
    if(ui->rightGraphicsView->figureChosed==figure::POINT){
           setDrawActionStatus(false);
           this->rightPixmapItem->grabMouse();
           this->rightPixmapItem->figureChosed =figure::MS3PTS;

           this->ImgDqe.push(this->rightPixmapItem->pixmap().toImage());


        ui->rightGraphicsView->pts.clear();
        ui->rightGraphicsView->figureChosed=figure::MS3PTS;
    }
    else if((ui->rightGraphicsView->figureChosed==figure::MS3PTS) && (ui->rightGraphicsView->pts.size()==3)){
        ui->rightGraphicsView->figureChosed=figure::POINT;
        QPixmap rightImage = rightPixmapItem->pixmap();
        auto[newImage,lenPix]  = Tools::PaintLineAPt(rightImage.toImage(),\
                QLineF(ui->rightGraphicsView->pts.at(0),\
                ui->rightGraphicsView->pts.at(1)),\
                ui->rightGraphicsView->pts.at(2),\
                this->curReslution,
                "",
                &this->painter);
                rightImage.convertFromImage(newImage);
                updateRightImage(rightImage);
   if(lenPix==0){
            //没有进行过标定
            QMessageBox::information(this, "计算得到的实际距离（um）",\
                                     "请先进行标定", QMessageBox::Ok);
        }
        else{
            QMessageBox::information(this, "计算得到的实际距离（um）",
                                     QString::number(lenPix*this->curReslution) + "(um)", QMessageBox::Ok);
        }
        setDrawActionStatus(true);
        this->rightPixmapItem->ungrabMouse();
        this->rightPixmapItem->figureChosed =figure::POINT;


    }
    else{
        ui->rightGraphicsView->figureChosed=figure::POINT;
        this->rightPixmapItem->figureChosed =figure::POINT;
        return;
    }
}

/*****************************************************************
                            无角度矩形面积
  *******************************************************************/
void  MainWindow::on_actionrect1Area_triggered(){

    ///初始化结果输出
    if(ui->rightGraphicsView->figureChosed==figure::POINT){
        setDrawActionStatus(false);
//        this->ImgTmp=this->rightPixmapItem->pixmap().toImage().copy();
        this->ImgDqe.push(this->rightPixmapItem->pixmap().toImage());


        ui->rightGraphicsView->pts.clear();
        ui->rightGraphicsView->figureChosed=figure::RECT1;
    }
    else if((ui->rightGraphicsView->figureChosed==figure::RECT1) && (ui->rightGraphicsView->pts.size()==2)){
        QPixmap rightImage = rightPixmapItem->pixmap();
        auto [newImage,AreaPix] =Tools::PaintRect1(rightImage.toImage(),\
                ui->rightGraphicsView->pts.at(0),\
                ui->rightGraphicsView->pts.at(1),\
                this->curReslution,\
                &this->painter);
//                double AreaActual=AreaPix*pow(this->curReslution,2);
                rightImage.convertFromImage(newImage);
                updateRightImage(rightImage);
                if(AreaPix==0){
            //没有进行过标定
            QMessageBox::information(this, "计算得到的面积（um²）",
                                     "请先进行标定", QMessageBox::Ok);
        }
        else{
            QMessageBox::information(this, "计算得到的面积（um²）",
                                     QString::number(AreaPix) + "(um²)", QMessageBox::Ok);
        }
        setDrawActionStatus(true);
        ui->rightGraphicsView->figureChosed=figure::POINT;

    }

    else{
        ui->rightGraphicsView->figureChosed=figure::POINT;
        return;
    }
}

/*********************************************************************
                              多边形面积
  **********************************************************************/
void  MainWindow::on_actionpolyArea_triggered(){

    ///初始化结果输出
    if(ui->rightGraphicsView->figureChosed==figure::POINT){
        setDrawActionStatus(false);
//        this->ImgTmp=this->rightPixmapItem->pixmap().toImage().copy();
        this->ImgDqe.push(this->rightPixmapItem->pixmap().toImage());



        ui->rightGraphicsView->pts.clear();
        ui->rightGraphicsView->figureChosed=figure::POLY;
        ///弹出窗口记录多边形顶点数
        ///
        PtsNumRecordDlg  dialog;
        connect(&dialog,&PtsNumRecordDlg::sendData,this,[this](int x){
            ui->rightGraphicsView->ptsNumRecord=x;
        });
        dialog.exec();

    }
    else if((ui->rightGraphicsView->figureChosed==figure::POLY) && \
            (ui->rightGraphicsView->pts.size()==ui->rightGraphicsView->ptsNumRecord)){
        QPixmap rightImage = rightPixmapItem->pixmap();
        auto [newImage,AreaPix] =Tools::PaintPoly(rightImage.toImage(),\
                ui->rightGraphicsView->pts,\
                this->curReslution,\
                &this->painter);
//                double AreaActual=AreaPix*pow(this->curReslution,2);
                rightImage.convertFromImage(newImage);
                updateRightImage(rightImage);
                if(AreaPix==0){
            //没有进行过标定
            QMessageBox::information(this, "计算得到的实际面积（um²）",
                                     "请先进行标定", QMessageBox::Ok);
        }
        else{
            QMessageBox::information(this, "计算得到的实际面积（um²）",
                                     QString::number(AreaPix) + "(um²)", QMessageBox::Ok);
        }
        ui->rightGraphicsView->figureChosed=figure::POINT;
        setDrawActionStatus(true);
    }
    else{
        ui->rightGraphicsView->figureChosed=figure::POINT;
        return;
    }

}
/********************************************************
 *                     三点角度
 * ******************************************************/

void  MainWindow::on_action3ptsMsAngle_triggered(){

    ///初始化结果输出
    if(ui->rightGraphicsView->figureChosed==figure::POINT){
        setDrawActionStatus(false);
//        this->ImgTmp=this->rightPixmapItem->pixmap().toImage().copy();
        this->ImgDqe.push(this->rightPixmapItem->pixmap().toImage());



        ui->rightGraphicsView->pts.clear();
        ui->rightGraphicsView->figureChosed=figure::PTS3MSAGL;
    }
    else if((ui->rightGraphicsView->figureChosed==figure::PTS3MSAGL) && \
            (ui->rightGraphicsView->pts.size()==3)){
        QPixmap rightImage = rightPixmapItem->pixmap();
        auto[newImage,angle]  =Tools::PaintAngle(rightImage.toImage(),\
                ui->rightGraphicsView->pts,
                &this->painter);
                rightImage.convertFromImage(newImage);
                updateRightImage(rightImage);

                QMessageBox::information(this, "计算得到的实际角度（deg）",\
                QString::number(angle) + QString("(°)"), QMessageBox::Ok);

                ui->rightGraphicsView->figureChosed=figure::POINT;
                setDrawActionStatus(true);
    }
                else{
            ui->rightGraphicsView->figureChosed=figure::POINT;
            return;
        }
    }



    /*************************************************************
     *                      海康相机链接操作
     * **************************************************************/

    /*
    ///ip连接
    void MainWindow::on_actionconnect_triggered(){

        ///获取两个ip设置成默认值
        ///
        /// todo


        ///枚举，选择相机[0]，将获取参数导入到成员变量
        do{
            MV_CC_DEVICE_INFO_LIST stDeviceList;
            memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
            this->nRet=MV_CC_EnumDevices(MV_CAMERALINK_DEVICE, &stDeviceList);

            ////本函数只使用于工控机一拖一相机，其他情况需要重写
            ///枚举相机失败 或者没有相机
            HKcamConnectDlg dialog;
            if(MV_OK!=this->nRet or stDeviceList.nDeviceNum<=0){
                QMessageBox::warning(this,"警告","未找到相机", QMessageBox::Ok);
                break;
            }
            ///成功枚举相机

                ///获取相机信息
                this->stDevInfo=stDeviceList.pDeviceInfo[0];
                dialog.init(QVector<uint32_t>{1,2,3,4},QVector<uint32_t>{1,2,3,4});




            //        HKcamConnectDlg dialog;
            connect(&dialog,&HKcamConnectDlg::sendData,this,[this]\
                    (unsigned int x1,unsigned int x2,unsigned int x3,unsigned int x4,\
                    unsigned int y1,unsigned int y2,unsigned int y3,unsigned int y4){
                uint16_t deviceIp = (x1<<24)|(x2<<16)|(x3<<8)|x4;
                uint16_t pcIp = (y1<<24)|(y2<<16)|(y3<<8)|y4;
                this->stGigEDev->nCurrentIp = deviceIp;
                this->stGigEDev->nNetExport = pcIp;

                ///GigE camera only
                this->stDevInfo->nTLayerType = MV_GIGE_DEVICE;// Only support GigE camera

                this->stDevInfo->SpecialInfo.stGigEInfo = *this->stGigEDev;

            });
            dialog.exec();
        }while (0);

    }

    */


    ///打开相机
    void MainWindow::on_actionopenDevice_triggered(){
        do
        {
            setHKcamActionStatus(false);
            ///如果相机只是暂停了，并没有关闭
            ///
            if((this->HkHandle!=nullptr)&&(this->hkStopFlg==true)){
                on_actionstopGrab_triggered();
                break;
            }


            MV_CC_DEVICE_INFO_LIST stDeviceList;
            //如果相机在链接中，直接跳出
            if(this->hkStopFlg==FALSE){
                QMessageBox::warning(this,"警告","请先停止相机"+QString::number(this->nRet), QMessageBox::Ok);
                break;
            }

            memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
            this->nRet=MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);

            ///枚举相机失败 或者没有相机
            if((MV_OK!=this->nRet)||(stDeviceList.nDeviceNum<=0) ){
                QMessageBox::warning(this,"警告",QString("找到%1相机,枚举失败"+QString::number(this->nRet)).arg(stDeviceList.nDeviceNum), QMessageBox::Ok);
                break;
            }
            ///成功枚举相机
            ///获取相机信息
            this->stDevInfo=stDeviceList.pDeviceInfo[0];
            // Select device and create handle
            ///创建相机句柄

            this->nRet = MV_CC_CreateHandle(&this->HkHandle,this->stDevInfo);
            if (MV_OK != this->nRet)
            {
                QMessageBox::warning(this,"警告","相机句柄创建失败"+QString::number(this->nRet), QMessageBox::Ok);
                break;
            }

            // Open device
            ///打开相机
            this->nRet = MV_CC_OpenDevice(this->HkHandle);
            if (MV_OK != this->nRet)
            {
                QMessageBox::warning(this,"警告","相机打开失败"+QString::number(this->nRet), QMessageBox::Ok);
                break;
            }
            ///相机已开启
            this->hkStopFlg=false;
            ///
            /// Detection network optimal package size(It only works for the GigE camera)
            ///如果是GigE camera
            if (this->stDevInfo->nTLayerType == MV_GIGE_DEVICE)
            {
                int nPacketSize = MV_CC_GetOptimalPacketSize(this->HkHandle);
                if (nPacketSize > 0)
                {
                    this->nRet = MV_CC_SetIntValue(this->HkHandle,"GevSCPSPacketSize",nPacketSize);
                    if(this->nRet != MV_OK)
                    {
                        QMessageBox::warning(this,"警告",\
                                             "Warning: Set Packet Size fail nRet"+\
                                             QString::number(this->nRet), QMessageBox::Ok);

                    }
                }
                else
                {
                    QMessageBox::warning(this,"警告","Get Packet Size fail nRet"+\
                                         QString::number(nPacketSize), QMessageBox::Ok);

                }
            }

            // Set trigger mode as off
            ///更改触发模式为自由触发

            this->nRet = MV_CC_SetEnumValue(this->HkHandle, "TriggerMode", MV_TRIGGER_MODE_OFF);
            if (MV_OK != this->nRet)
            {
                QMessageBox::warning(this,"警告","Set Trigger Mode fail! nRet"+\
                                     QString::number(this->nRet), QMessageBox::Ok);
                break;
            }

            ///获取相机图像类型
            this->nRet =MV_CC_GetEnumValue(this->HkHandle,"PixelFormat",this->HKImgFmt.get());
            if (MV_OK != this->nRet)
            {
                QMessageBox::warning(this,"警告","get Pixel Format fail! nRet"+\
                                     QString::number(this->nRet), QMessageBox::Ok);
                break;
            }

            ///获取相机的自动状态 ：曝光、增益、白平衡
            ///
            //            memset(this->exposureMode,0,sizeof (MVCC_ENUMVALUE));
            this->nRet=MV_CC_GetEnumValue(this->HkHandle,"ExposureAuto", this->exposureMode.get());
            if(MV_OK!=this->nRet)
            {
                QMessageBox::warning(this,"警告","Get exposure Mode fail! nRet"+ \
                                     QString::number(this->nRet), QMessageBox::Ok);
                break;
            }
            //            memset(this->gainMode,0,sizeof (MVCC_ENUMVALUE));
            this->nRet=MV_CC_GetEnumValue(this->HkHandle,"GainAuto", this->gainMode.get());

            if(MV_OK!=this->nRet){
                QMessageBox::warning(this,"警告","Get Gain Mode fail! nRet"+ \
                                     QString::number(this->nRet), QMessageBox::Ok);
                break;
            }
            //            memset(this->balanceWH,0,sizeof (MVCC_ENUMVALUE));
            this->nRet=MV_CC_GetEnumValue(this->HkHandle,"BalanceWhiteAuto", this->balanceWH.get());

            if(MV_OK!=this->nRet){
                QMessageBox::warning(this,"警告","Get exposure Mode fail! nRet"+ \
                                     QString::number(this->nRet), QMessageBox::Ok);
                break;
            }


            ///清空图像窗口
            if (this->size)
            {
                delete this->size;
                this->size = new QLabel;
                ui->statusBar->addPermanentWidget(this->size);
            }
            this->setWindowTitle(WINDOW_TITLE);
            setActionStatus(false);




            // Start grab image
            this->nRet = MV_CC_StartGrabbing(this->HkHandle);
            if (MV_OK != this->nRet)
            {
                QMessageBox::warning(this,"警告","Start Grabbing fail! nRet"+\
                                     QString::number(this->nRet), QMessageBox::Ok);
                break;
            }

            this->grabImgThread =new TgrabImg(this,this->HkHandle,this->HKImgFmt);
            connect(this->grabImgThread,&TgrabImg::newImageCaptured,this,&MainWindow::updateLeftFromCam);
            this->grabImgThread->startCapturing();
        }while(0);
        setHKcamActionStatus(true);
    }

    ///刷新左边图像的函数
    void MainWindow::updateLeftFromCam(QImage image,const QString& str)
    {
        if(str!="成功取图"){
            QMessageBox::warning(this, "错误", str, QMessageBox::Ok);
            this->hkStopFlg=true;
            this->nRet =MV_CC_StopGrabbing(this->HkHandle);

            return; // 如果有错误，不处理图像
        }

        QPixmap leftImage = QPixmap::fromImage(image);
        leftPixmapItem = leftScene->addPixmap(leftImage);
        leftScene->setSceneRect(QRectF(leftImage.rect()));


        this->setWindowTitle( "HIKVISION - ImageQt");

        setActionStatus(true);

        size->setText(QString::number(leftPixmapItem->pixmap().width())
                      + " x " + QString::number(leftPixmapItem->pixmap().height()));
        ///显示当前分辨率的名字


        QString name;
        if(curReslution!=0.0){
            std::for_each(this->resolution->begin(),this->resolution->end(),[this,&name](std::pair<QString,double> resolutionEle){
                if(resolutionEle.second==curReslution){
                    name=resolutionEle.first;
                }
            });
        }
        this->curResolutionName.get()->setText("当前标定命名："+name);
}
    /*
          * cameraThread = new CameraThread(this->HkHandle);
            connect(cameraThread, &CameraThread::newImageCaptured, this, &MainWindow::updateGraphicsView);
            cameraThread->startCapturing();
        }
        */
    /*
            ///线程ID
            unsigned int nThreadID = 0;
            ///线程handle
            ///

            void* hThreadHandle = (void*) _beginthreadex( NULL , 0 , [](void* pUser){
                MainWindow* pMainWindow = static_cast<MainWindow*>(pUser);
                return pMainWindow->WorkThread(pUser);
            }
            , this->HkHandle, 0 , &nThreadID );
            if (NULL == hThreadHandle)
            {
                break;
            }


*/



    /*

    //__stdcall
inline static unsigned int __stdcall WorkThread(void* pUser)
    {
        while(true)
        {
            this->nRet = MV_CC_GetImageBuffer(pUser, this->stOutFrame, 1000);
            ///成功取图
            if (this->nRet == MV_OK)
            {
                qDebug("Get Image Buffer: Width[%d], Height[%d], FrameNum[%d]\n",\
                       this->stOutFrame->stFrameInfo.nWidth,\
                       this->stOutFrame->stFrameInfo.nHeight, \
                       this->stOutFrame->stFrameInfo.nFrameNum);
                //                printf("Get Image Buffer: Width[%d], Height[%d], FrameNum[%d]\n",
                //                    this->stOutFrame->stFrameInfo.nWidth, this->stOutFrame->stFrameInfo.nHeight, this->stOutFrame->stFrameInfo.nFrameNum);

                ///拿图像，发信号
                QImage image(this->stOutFrame->pBufAddr,\
                             this->stOutFrame->stFrameInfo.nWidth,\
                             this->stOutFrame->stFrameInfo.nHeight,\
                             QImage::Format::Format_Mono);

                updateLeftFromCam(image);
                this->nRet = MV_CC_FreeImageBuffer(pUser, this->stOutFrame);
                if(nRet != MV_OK)
                {
                    QMessageBox::warning(this,"警告","释放相机图像缓存失败 nRet"+QString::number(this->nRet), QMessageBox::Ok);
                }
            }
            ///取图失败
            else
            {
                QMessageBox::warning(this,"警告","取图失败 nRet"+QString::number(this->nRet), QMessageBox::Ok);

            }
            if(this->hkStopFlg)
            {
                break;
            }
        }

        return 0;
    }

*/





    ///相机暂停
    ///
    void MainWindow::on_actionstopGrab_triggered(){
        ///相机在运行中
        if((this->hkStopFlg==false)&&(this->HkHandle!=nullptr))
        {
            freeTgrabImg();
            this->hkStopFlg=true;
            this->nRet =MV_CC_StopGrabbing(this->HkHandle);
            if(MV_OK!=this->nRet){
                QMessageBox::warning(this,"警告","相机暂停失败"+QString::number(this->nRet), QMessageBox::Ok);
            }
            else{
                this->hkStopFlg=true;
            }
        }
        ///相机暂停
        else if ((this->hkStopFlg==true) &&(this->HkHandle!=nullptr)){
            // Start grab image
            this->nRet = MV_CC_StartGrabbing(this->HkHandle);
            if (MV_OK != this->nRet)
            {
                QMessageBox::warning(this,"警告","Start Grabbing fail! nRet"+\
                                     QString::number(this->nRet), QMessageBox::Ok);
            }
            else{
                this->hkStopFlg=false;

            }
            this->grabImgThread =new TgrabImg(this,this->HkHandle,this->HKImgFmt);
            connect(this->grabImgThread,&TgrabImg::newImageCaptured,this,&MainWindow::updateLeftFromCam);
            this->grabImgThread->startCapturing();


        }
        else{
            QMessageBox::warning(this,"警告","请先打开相机", QMessageBox::Ok);

        }
    }


    ///相机停止
    ///
    void MainWindow::on_actiondisconnect_triggered(){
        do{
            /*
            freeTgrabImg();
            this->hkStopFlg=true;
            this->nRet =MV_CC_StopGrabbing(this->HkHandle);
            if(MV_OK!=this->nRet)
                QMessageBox::warning(this,"警告","相机暂停失败"+QString::number(this->nRet), QMessageBox::Ok);
                */

            ///如果相机没有打开
            if((this->nRet!=MV_OK) && (this->HkHandle==nullptr)){
                QMessageBox::warning(this,"警告","请先打开相机"+QString::number(this->nRet), QMessageBox::Ok);
                break;
            }
            ///相机打开则暂停
            if(this->hkStopFlg==false){
                on_actionstopGrab_triggered();
            }
            ///关闭相机
            this->nRet=MV_CC_CloseDevice(this->HkHandle);
            if(MV_OK!=this->nRet)
            {
                QMessageBox::warning(this,"警告","相机停止失败"+QString::number(this->nRet), QMessageBox::Ok);
                break;
            }
            ///释放 handle
            this->nRet =MV_CC_DestroyHandle(this->HkHandle);
            if(MV_OK!=this->nRet){
                QMessageBox::warning(this,"警告","相机句柄释放失败"+QString::number(this->nRet), QMessageBox::Ok);
                break;
            }
            this->HkHandle=nullptr;
        }while (0);

        if (this->nRet != MV_OK)
        {
            if (this->HkHandle != nullptr)
            {
                MV_CC_DestroyHandle(this->HkHandle);
                this->HkHandle = nullptr;
            }
        }
    }

    ///设置白平衡和曝光界面弹出
    void MainWindow::on_actionsetSpecInfo_triggered(){
        do{

            ///如果相机没有打开
            if((this->nRet!=MV_OK) && (this->HkHandle==nullptr)){
                QMessageBox::warning(this,"警告","请先打开相机"+QString::number(this->nRet), QMessageBox::Ok);
                break;
            }
            ///相机打开则暂停
            if(this->hkStopFlg==false){
                on_actionstopGrab_triggered();
            }



            ///获取白平衡和曝光
            /// MV_CC_FRAME_SPEC_INFO::fExposureTime
            /// MV_CC_FRAME_SPEC_INFO::fGain
            /// MV_CC_FRAME_SPEC_INFO::nRed nGreen nBlue



//            std::unique_ptr<MVCC_FLOATVALUE> fexposure=std::make_unique<MVCC_FLOATVALUE>();
//            std::unique_ptr<MVCC_FLOATVALUE> fgain=std::make_unique<MVCC_FLOATVALUE>();

            MVCC_FLOATVALUE* fexposure=new MVCC_FLOATVALUE();
            MVCC_FLOATVALUE* fgain= new MVCC_FLOATVALUE();
            MVCC_INTVALUE* nred =new MVCC_INTVALUE();
            MVCC_INTVALUE* ngreen =new MVCC_INTVALUE();
            MVCC_INTVALUE* nblue =new MVCC_INTVALUE();



            ///设置到默认对话框上

            if(MV_OK!=MV_CC_GetExposureTime(this->HkHandle,fexposure)){
                QMessageBox::warning(this,"警告","设置曝光时间错误"+QString::number(this->nRet), QMessageBox::Ok);
                break;
            }
            if(MV_OK!=MV_CC_GetGain(this->HkHandle,fgain)){
                QMessageBox::warning(this,"警告","设置增益错误"+QString::number(this->nRet), QMessageBox::Ok);
                break;
            }
            if(MV_OK!=MV_CC_GetBalanceRatioRed(this->HkHandle,nred)){
                QMessageBox::warning(this,"警告","设置白平衡红色错误"+QString::number(this->nRet), QMessageBox::Ok);
                break;
            }
            if(MV_OK!=MV_CC_GetBalanceRatioGreen(this->HkHandle,ngreen)){
                QMessageBox::warning(this,"警告","设置白平衡绿色错误"+QString::number(this->nRet), QMessageBox::Ok);
                break;
            }

            if(MV_OK!=MV_CC_GetBalanceRatioBlue(this->HkHandle,nblue)){
                QMessageBox::warning(this,"警告","设置白平衡蓝色错误"+QString::number(this->nRet), QMessageBox::Ok);
                break;
            }

            SetHKSpecInfoDlg dlg;
            dlg.init(fexposure->fCurValue,fgain->fCurValue,nred->nCurValue,ngreen->nCurValue,nblue->nCurValue,\
                     bool(this->exposureMode.get()->nCurValue!=MV_EXPOSURE_AUTO_MODE_OFF),\
                     bool(this->gainMode.get()->nCurValue!=MV_GAIN_MODE_OFF),\
                     bool(this->balanceWH.get()->nCurValue!=MV_BALANCEWHITE_AUTO_OFF));

            ///将重新设置的参数设置到相机上
            connect(&dlg,&SetHKSpecInfoDlg::sendData,this,&MainWindow::setPara2Cam);
            //            connect(&dlg,&SetHKSpecInfoDlg::pb_getAutoBWH,this,&MainWindow::getPara2Dlg)
            dlg.exec();

            ///继续
            if(this->hkStopFlg==true){
                on_actionstopGrab_triggered();
            }

        }while (0);

    }

    ///将参数设置到相机
    void MainWindow::setPara2Cam(float fexposure,float fgain,unsigned int nred,unsigned int ngreen,unsigned int nblue,\
                                 bool exposureMode,bool gainMode,bool balanceMode){

        do{
            if( exposureMode?false:MV_OK!=MV_CC_SetExposureTime(this->HkHandle,fexposure)){
                QMessageBox::warning(this,"警告","设置曝光时间错误"+QString::number(this->nRet), QMessageBox::Ok);
                break;
            }
            this->exposureMode.get()->nCurValue=exposureMode?MV_EXPOSURE_AUTO_MODE_OFF:MV_EXPOSURE_AUTO_MODE_CONTINUOUS;
            if(gainMode?false:MV_OK!=MV_CC_SetGain(this->HkHandle,fgain)){
                QMessageBox::warning(this,"警告","设置增益错误"+QString::number(this->nRet), QMessageBox::Ok);
                break;
            }
            this->gainMode.get()->nCurValue=gainMode?MV_GAIN_MODE_OFF:MV_GAIN_MODE_CONTINUOUS;
            if(balanceMode?false:MV_OK!=MV_CC_SetBalanceRatioRed(this->HkHandle,nred)){
                QMessageBox::warning(this,"警告","设置白平衡红色错误"+QString::number(this->nRet), QMessageBox::Ok);
                break;
            }
            if(balanceMode?false:MV_OK!=MV_CC_SetBalanceRatioGreen(this->HkHandle,ngreen)){
                QMessageBox::warning(this,"警告","设置白平衡绿色错误"+QString::number(this->nRet), QMessageBox::Ok);
                break;
            }

            if(balanceMode?false:MV_OK!=MV_CC_SetBalanceRatioBlue(this->HkHandle,nblue)){
                QMessageBox::warning(this,"警告","设置白平衡蓝色错误"+QString::number(this->nRet), QMessageBox::Ok);
                break;
            }
            this->balanceWH.get()->nCurValue=balanceMode?MV_BALANCEWHITE_AUTO_OFF:MV_BALANCEWHITE_AUTO_CONTINUOUS;
        }while (0);
    }

    //    void MainWindow::getPara2Dlg(){
    //        do{

    //            MVCC_ENUMVALUE* EMAutoBWH=nullptr;
    //            if(MV_OK!=MV_CC_GetBalanceWhiteAuto(this->HkHandle,EMAutoBWH)){
    //                QMessageBox::warning(this,"警告","自动获取白平衡错误", QMessageBox::Ok);
    //                break;
    //            }

    // //            if(MV_OK!=MV_CC_SetBalanceRatioGreen(this->HkHandle,ngreen)){
    // //                QMessageBox::warning(this,"警告","设置白平衡绿色错误", QMessageBox::Ok);
    // //                break;
    // //            }

    // //            if(MV_OK!=MV_CC_SetBalanceRatioBlue(this->HkHandle,nblue)){
    // //                QMessageBox::warning(this,"警告","设置白平衡蓝色错误", QMessageBox::Ok);
    // //                break;
    //            }
    //        }while (0);
    //    }


    ///将左边的图像捕获到右侧
    ///dzy1025
    void MainWindow::on_actioncapture_triggered(){
        static size_t idx=0;

        if(leftPixmapItem==nullptr){
            return;
        }
        QPixmap leftPix = leftPixmapItem->pixmap();

        rightPixmapItem->setPixmap(leftPix);
        rightScene->setSceneRect(QRectF(leftPix.rect()));
        this->ImgDqe.clear();

        this->savedImage.addImage(this->rightPixmapItem->pixmap().toImage(),QString::number(idx));
        qDebug()<<"图像已保存";
        idx++;
        this->savedShowIdx++;
    }



    void  MainWindow::freeTgrabImg(){
        if(this->grabImgThread!=nullptr){
            grabImgThread->stopCapturing(); // 要求线程停止抓取
            delete grabImgThread;
            grabImgThread =nullptr;
        }
    }

void MainWindow::on_actionresolutionManage_triggered()
{

    ResolutionManagerDlg dlg(this,this->resolution.get(),&this->curReslution);
    connect(&dlg, &ResolutionManagerDlg::sendData,[this](double res){
        this->curReslution=res;
    });
    dlg.exec();

    QString name;
    if(curReslution!=0.0){
        std::for_each(this->resolution->begin(),this->resolution->end(),[this,&name](std::pair<QString,double> resolutionEle){
            if(resolutionEle.second==curReslution){
                name=resolutionEle.first;
            }
        });
    }
    this->curResolutionName.get()->setText("当前标定命名："+name);

}

void MainWindow::on_actionpicBefore_triggered()
{
    if(this->savedImage.getImageCount()==0){
        return;
    }
    ///更新图像
    QPixmap rightPixmap =QPixmap::fromImage(this->savedImage.getImage(this->savedShowIdx));
    updateRightImage(rightPixmap);
    ///更新名称
    this->setWindowTitle(this->savedImage.getImageName(this->savedShowIdx) + " - ImageQt");

    if(this->savedShowIdx!=0){
        this->savedShowIdx--;
    }
}

void MainWindow::on_actionpicNext_triggered()
{
    if(this->savedImage.getImageCount()==0){
        return;
    }

    if(this->savedShowIdx!=savedImage.getImageCount()-1){
        this->savedShowIdx++;
    }
    QPixmap rightPixmap =QPixmap::fromImage(this->savedImage.getImage(this->savedShowIdx));
    updateRightImage(rightPixmap);
}



void MainWindow::on_actionimageLeap_triggered()
{
    ImgLeapDlg dlg(this,&savedImage);
    connect(&dlg, &ImgLeapDlg::sendData,[this](QString str){
        QPixmap rightPixmap =QPixmap::fromImage(this->savedImage.getImageInfoByName(str).savedImg);
        updateRightImage(rightPixmap);
    });
    dlg.exec();
}



void MainWindow::on_actioneraserLast_triggered()
{
    /*
    if(this->ImgTmp.isNull()){
        return;
    }
    QPixmap pixmalTmp =QPixmap::fromImage(this->ImgTmp);
    this->rightPixmapItem->setPixmap(pixmalTmp);
    updateRightImage(pixmalTmp);
    */
    if(this->ImgDqe.isEmpty()){
        return;
    }

    QPixmap pixmalTmp =QPixmap::fromImage(this->ImgDqe.peek().copy());
    this->rightPixmapItem->setPixmap(pixmalTmp);
    updateRightImage(pixmalTmp);
    this->ImgDqe.pop_back();
}
