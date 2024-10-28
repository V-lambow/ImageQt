#ifndef DLG_IMGLEAP_H
#define DLG_IMGLEAP_H

#include <QDialog>
#include "ImageSaver.hpp"
namespace Ui {
class ImgLeapDlg;
}

class ImgLeapDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ImgLeapDlg(QWidget *parent = nullptr,ImageSaver *savedImg=nullptr);
    ~ImgLeapDlg();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ImgLeapDlg *ui;
    ImageSaver m_savedImg;
signals:
    void sendData(QString);
};

#endif // DLG_IMGLEAP_H
