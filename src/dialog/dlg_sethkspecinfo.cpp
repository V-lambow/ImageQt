#include "dlg_sethkspecinfo.h"
#include "ui_dlg_sethkspecinfo.h"

SetHKSpecInfoDlg::SetHKSpecInfoDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetHKSpecInfoDlg)
{
    ui->setupUi(this);
    ui->fexposure->setDecimals(6); // 设置小数点后的位数以接近float的精度
    ui->fexposure->setSingleStep(0.0001); // 设置步长以增加精度控制
    ui->fexposure->setAccelerated(true); // 启用自动增加步长
    ui->fgain->setDecimals(6); // 设置小数点后的位数以接近float的精度
    ui->fgain->setSingleStep(0.0001); // 设置步长以增加精度控制
    ui->fgain->setAccelerated(true); // 启用自动增加步长
    ui->fexposure->setEnabled(!ui->autoExposure);
    ui->fgain->setEnabled(!ui->autoGain);
    ui->nred->setEnabled(!ui->autoBalanceWH);
    ui->ngreen->setEnabled(!ui->autoBalanceWH);
    ui->nblue->setEnabled(!ui->autoBalanceWH);
}

SetHKSpecInfoDlg::~SetHKSpecInfoDlg()
{
    delete ui;
}
void SetHKSpecInfoDlg::init(float fexposure,float fgain,unsigned int nred,unsigned int ngreeen,unsigned int nblue,bool exposureMode,bool gainMode,bool balanceWH) const {

    ///
    ui->autoExposure->setChecked(exposureMode);
    ui->autoGain->setChecked(gainMode);
    ui->autoBalanceWH->setChecked(balanceWH);
    ///
    ui->fexposure->setValue(fexposure);
    ui->fgain->setValue(fgain);
    ui->nred->setValue(nred);
    ui->nblue->setValue(nblue);
    ui->ngreen->setValue(ngreeen);
    ///
    ui->fexposure->setEnabled(!exposureMode);
    ui->fgain->setEnabled(!gainMode);
    ui->nred->setEnabled(!balanceWH);
    ui->nblue->setEnabled(!balanceWH);
    ui->ngreen->setEnabled(!balanceWH);

}
void SetHKSpecInfoDlg::on_buttonBox_accepted(){
    emit sendData(ui->fexposure->value(),ui->fgain->value(),ui->nred->value(),ui->ngreen->value(),ui->nblue->value(),\
                  ui->autoExposure->isChecked(),ui->autoGain->isChecked(),ui->autoBalanceWH->isChecked());
}
void SetHKSpecInfoDlg::on_autoBlanceWH(){
    emit pb_getAutoBWH();
}
