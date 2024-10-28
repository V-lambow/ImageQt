#ifndef DLG_HKCAMCONNECT_H
#define DLG_HKCAMCONNECT_H

#include <QDialog>

namespace Ui {
class HKcamConnectDlg;
}

class HKcamConnectDlg : public QDialog
{
    Q_OBJECT

public:
    explicit HKcamConnectDlg(QWidget *parent = nullptr);
    ~HKcamConnectDlg();
    void init(const QVector<uint32_t>& x,const QVector<uint32_t>& y);

private:
    Ui::HKcamConnectDlg *ui;
    void on_buttonBox_accepted();
signals:
    void sendData(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
};

#endif // DLG_HKCAMCONNECT_H
