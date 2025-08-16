#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QLabel>
#include <QDebug>
#include <QStandardPaths>
#include <QTranslator>
#include <QMessageBox>
#include <QDebug>
#include <QScrollBar>
#include "graphicsview.h"
#include "limitedDqe.hpp"
#include "../dialog/dialog_gaussianblur.h"
#include "../utils/tools.h"
#include "../utils/histogram.h"
#include "../utils/gaussianblur.h"
#include "../utils/medianfilter.h"
#include "../dialog/dialog_linear_gray.h"
#include "../dialog/dialog_log_grey.h"
#include "../dialog/dialog_power_grey.h"
#include "../dialog/dialog_exp_transform.h"
#include "../dialog/dialog_two_threshold_transform.h"
#include "../dialog/dialog_stretch_transform.h"
#include "../dialog/dialog_califrom3pts.h"
#include "../dialog/dialog_ptsnumrecord.h"
//#include "../dialog/dlg_hkcamconnect.h"
#include "../dialog/dlg_sethkspecinfo.h"
#include "../t_grabimg.h"
#include "../dialog/dlg_resolutionmanager.h"
#include "../utils/ImageSaver.hpp"
#include "../dialog/dlg_imgleap.h"
#include "../dialog/dlg_imagenamed.h"
#include "../mainwindow/mygraphicspixmapitem.h"
#include "param.h"

///海康
///
#include "MvCameraControl.h"
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <process.h>
///


#define WINDOW_TITLE    "ImageQt"
#define WINDOW_CRITICAL "Error - ImageQt"
#define WINDOW_WARNING  "Notice - ImageQt"
#define WINDOW_ABOUT    "About - ImageQt"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateRightImage(QPixmap &pixmap);
    void cleanImage(QString whichSide);

    void setActionStatus(bool);
    void setHKcamActionStatus(bool);
    void createToolBar();
    void createAction();
    void setDrawActionStatus(bool);


private slots:

    // 从子对话框中接收数据
    void receiveGaussianFactor(int radius, double sigma);
    void receiveLinearGreyParameter(double, double);
    void receivePowerGreyParamter(double, double, double);
    void receiveLogGreyParamter(double, double);
    void receiveExpGreyParamter(double, double, double);
    void receiveTwoThresholdParamter(int, int, int);
    void receiveStretchParamter(int, int, double,double,double,double,double);
//    void receiveCaliFrom3ptsParamter(double,double y);

    // On action triggered
    void on_actionOpen_triggered();
    void on_actionClose_triggered();        // Clear both left and right Scene
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();      // Save as
    void on_actionExit_triggered();         // Exit the program

    void on_actionGrayscale_triggered();    // Grayscale
    void on_actionAdjust_brightness_triggered();

    void on_actionRestore_triggered();      // Restore to the original image
    void on_actionHistogram_triggered();

    void on_actionMovie_frame_triggered();
    void on_actionClassic_frame_triggered();
    void on_actionFlower_frame_triggered();
    void on_actionMetal_triggered();
    void on_actionCool_triggered();
    void on_actionWarm_triggered();

    void on_actionSimple_triggered();
    void on_actionGauss_triggered();
    void on_actionMeida_Filter_triggered();

    void on_zoomAction_triggered();         // Zoom action with dialog
    void on_actionHorizontal_triggered();
    void on_actionVertical_triggered();

    void on_actionLinear_level_transformation_triggered();
    void on_actionPower_transformation_triggered();
    void on_actionLogarithm_grey_level_transformation_triggered();
    void on_actionExp_transfrom_triggered();
    void on_actionTwo_thresholds_transform_triggered();
    void on_actionStretch_transformation_triggered();

    void on_actionAdjust_triggered();       // Adjust to fit the window size
    void on_actionNormal_triggered();       // Restore the right image to original size


    void on_actionAbout_triggered();        // Show "About" dialog

//    void on_actionT_triggered();

    void on_actionLaplace_triggered();

//    void on_actionEdge_Detection_triggered();

    void on_actionSobel_triggered();

    void on_actionBinaryzation_triggered();

    void on_actionPrewitt_triggered();

    void on_actionContour_extraction_triggered();

    void on_actionArea_triggered();

    void on_actionCircumference_triggered();


    void on_actionDilate_triggered();

    void on_actionExpansion_triggered();

    void on_actionOpening_triggered();

    void on_actionClosing_triggered();

    void on_actionThinning_triggered();

//    void on_actionRGB2HSV_triggered();
//    void on_actionRGB2HSL_triggered();
//    void on_actionRGB2Cmyk_triggered();

    void on_actionRotate_triggered();
/****************************************
 ****************** dzy*****************/

    void  on_actioncaliFrom3Pts_triggered();
    void  on_actionmeasureFrom3Pts_triggered();
    void  on_actionrect1Area_triggered();
    void  on_actionpolyArea_triggered();
    void on_actiondistancePP_triggered();
    void  on_action3ptsMsAngle_triggered();
    /********************************
     * **************************/
//    void on_actionconnect_triggered();
    void on_actionstopGrab_triggered();
    void on_actiondisconnect_triggered();
    void on_actionopenDevice_triggered();
    //__stdcall
//    inline static unsigned int __stdcall WorkThread(void* pUser);
    void updateLeftFromCam(QImage image,const QString& str);
    void on_actionsetSpecInfo_triggered();
    void on_actioncapture_triggered();
    void setPara2Cam(float fexposure,float fgain,unsigned int nred,unsigned int ngreen,unsigned int nblue,\
                     bool exposureMode,bool gainMode,bool balanceMode);
///todo
//    void updateLeftGraphicsView(const QImage &image);
//    void getPara2Dlg();



    void on_actionresolutionManage_triggered();

    void on_actionpicBefore_triggered();

    void on_actionpicNext_triggered();


    void on_actionimageLeap_triggered();


    void on_actioneraserLast_triggered();

private:
    QAction *finalEx;

    Ui::MainWindow       *ui;
    QGraphicsScene       *leftScene;
    QGraphicsScene       *rightScene;

    //dzy1025
    QGraphicsPixmapItem* leftPixmapItem;
    MyGraphicsPixmapItem* rightPixmapItem;

    QLabel          *size;
    std::unique_ptr<QLabel> curResolutionName=std::make_unique<QLabel>();


    QFileInfo       *info;

    ///当前分辨率
    double curReslution=0.0;
    ///分辨率列表
    std::shared_ptr<std::map<QString,double>> resolution=std::make_shared<std::map<QString,double>>();
    ///画家
    QPainter painter;
    ///图片缓存（用于撤回上一步）
    QImage ImgTmp;
    LimitedDqe<QImage> ImgDqe{10};

    ImageSaver savedImage;
    int savedShowIdx=savedImage.getImageCount()-1;
    //  double resolution=0.0;

    /********************/
    ///海康
    void *  HkHandle = nullptr;
    uint16_t nRet =MV_OK;
    MV_CC_DEVICE_INFO *stDevInfo = nullptr;
    MV_GIGE_DEVICE_INFO *stGigEDev = nullptr;
    bool hkStopFlg = true;
    TgrabImg* grabImgThread=nullptr;


    ///自动白平衡状态

    std::shared_ptr<MVCC_ENUMVALUE>HKImgFmt = std::make_shared<MVCC_ENUMVALUE>();
    std::unique_ptr<MVCC_ENUMVALUE>gainMode = std::make_unique<MVCC_ENUMVALUE>();
    std::unique_ptr<MVCC_ENUMVALUE>exposureMode = std::make_unique<MVCC_ENUMVALUE>();
    std::unique_ptr<MVCC_ENUMVALUE>balanceWH = std::make_unique<MVCC_ENUMVALUE>();

    void  freeTgrabImg();

//    MVCC_ENUMVALUE *gainMode =nullptr;
//    MVCC_ENUMVALUE *exposureMode=nullptr;
//    MVCC_ENUMVALUE *balanceWH=nullptr;

    ///图像输出
    MV_FRAME_OUT * stOutFrame=nullptr;


    QString getUserName();
    QString getUserPath();





//    void mousePressEvent(QMouseEvent *e) override;
//    friend class GraphicsView;
};

#endif // MAINWINDOW_H
