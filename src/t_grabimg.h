#ifndef TGRABIMG_H
#define TGRABIMG_H

#include <QWidget>
#include <QThread>
#include "MvCameraControl.h"
#include <QDebug>


class TgrabImg : public QThread
{
    Q_OBJECT
public:
    void* m_HkHandle;
    bool m_running=false;
    MVCC_ENUMVALUE m_PixelFormat;
    explicit TgrabImg(QObject *parent = nullptr);
    explicit TgrabImg(QObject *parent = nullptr,void * handle =nullptr,std::shared_ptr<MVCC_ENUMVALUE> PixelFormat=nullptr);
    void run() override;
    void startCapturing();
    void stopCapturing();
    std::unordered_map<uint16_t,QImage::Format>PixelFormatTab={
        { 0x01080001/*Mono8*/,QImage::Format_Indexed8},\
        { 0x02180014/*RGB8Packed*/,QImage::Format_RGB888},\
        { 0x01080009/*BayerRG8*/,QImage::Format_Indexed8}
    };

signals:
    void newImageCaptured(QImage image,const QString& str);

};

#endif // TGRABIMG_H
