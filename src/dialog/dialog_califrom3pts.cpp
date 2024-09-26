#include "dialog_califrom3pts.h"
#include "ui_dialog_califrom3pts.h"

CaliFrom3PtsDlg::CaliFrom3PtsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CaliFrom3PtsDlg)
{
    ui->setupUi(this);

}

CaliFrom3PtsDlg::~CaliFrom3PtsDlg()
{
    delete ui;
}
void CaliFrom3PtsDlg::on_buttonBox_accepted()
{
    emit sendData(ui->x->value());
}
