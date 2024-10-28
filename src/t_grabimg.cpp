#include "t_grabimg.h"

TgrabImg::TgrabImg(QObject *parent) : QThread(parent)
{

}
TgrabImg::TgrabImg(QObject *parent,void * handle,std::shared_ptr<MVCC_ENUMVALUE> PixelFormat )
    : QThread(parent), m_HkHandle(handle), m_running(false),m_PixelFormat(*PixelFormat.get()){

}

void TgrabImg::run(){
    while (this->m_running) {
        // 获取图像的逻辑，假设使用 MV_CC_GetImage
        MV_FRAME_OUT frameData;
        memset(&frameData, 0, sizeof(MV_FRAME_OUT));

        // 从相机中获取图像
        uint16_t nRet = MV_CC_GetImageBuffer(this->m_HkHandle, &frameData, 1000);

        QImage::Format fmt(this->PixelFormatTab[this->m_PixelFormat.nCurValue]);

        QImage img;

        ///成功取图
        if (nRet == MV_OK) {
            ///将图像转换为 QImage
            img=QImage(static_cast<const uchar*>(frameData.pBufAddr), \
                               frameData.stFrameInfo.nWidth, \
                               frameData.stFrameInfo.nHeight,\
                               fmt);


            // 发出信号，更新图像
            emit newImageCaptured(img,QString("成功取图"));
            qDebug()<<"来了一张图";
        }
        else{
            emit newImageCaptured(img,"获取图像失败，错误代码: " + QString::number(nRet));
            qDebug()<<"拿图失败了";
            break;
        }
        nRet = MV_CC_FreeImageBuffer(this->m_HkHandle, &frameData);
        if(nRet != MV_OK)
        {
//                printf("Free Image Buffer fail! nRet [0x%x]\n", nRet);
            emit newImageCaptured(img,"释放图像缓存失败，错误代码: " + QString::number(nRet));
            break;
        }
        QThread::msleep(1000);
    }
}
void TgrabImg::startCapturing() {
    this->m_running = true;
    start();
}
void TgrabImg::stopCapturing() {
    m_running = false;
    wait(); // 等待线程结束
}
