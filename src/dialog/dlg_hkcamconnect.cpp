#include "dlg_hkcamconnect.h"
#include "ui_dlg_hkcamconnect.h"

HKcamConnectDlg::HKcamConnectDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HKcamConnectDlg)
{
    ui->setupUi(this);
}
void HKcamConnectDlg::init(const QVector<uint32_t>& x,const QVector<uint32_t>& y){
    ui->x1->setValue(x.at(0));
    ui->x2->setValue(x.at(1));
    ui->x3->setValue(x.at(2));
    ui->x3->setValue(x.at(3));
    ui->y1->setValue(y.at(0));
    ui->y2->setValue(y.at(1));
    ui->y3->setValue(y.at(2));
    ui->y4->setValue(y.at(3));
}
void HKcamConnectDlg::on_buttonBox_accepted()
{
    emit sendData(ui->x1->value(),ui->x2->value(),ui->x3->value(),ui->x4->value(),\
                  ui->y1->value(),ui->y2->value(),ui->y3->value(),ui->y4->value());

}
HKcamConnectDlg::~HKcamConnectDlg()
{
    delete ui;
}
