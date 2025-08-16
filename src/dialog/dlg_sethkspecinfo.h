#ifndef DLG_SETHKSPECINFO_H
#define DLG_SETHKSPECINFO_H

#include <QDialog>

namespace Ui {
class SetHKSpecInfoDlg;
}

class SetHKSpecInfoDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SetHKSpecInfoDlg(QWidget *parent = nullptr);
    ~SetHKSpecInfoDlg();
    void init(float fexposure,float fgain,unsigned int nred,unsigned int ngreeen,unsigned int nblue,\
              bool exposureMode,bool gainMode,bool balanceWH)const ;
private:
    Ui::SetHKSpecInfoDlg *ui;
signals:
    void sendData(float,float,unsigned int,unsigned int,unsigned int,bool,bool,bool);
    void pb_getAutoBWH();
private slots:
    void on_buttonBox_accepted();
    void on_autoBlanceWH();

};

#endif // DLG_SETHKSPECINFO_H
