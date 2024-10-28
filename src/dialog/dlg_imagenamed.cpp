#include "dlg_imagenamed.h"
#include "ui_dlg_imagenamed.h"

imageNamedDlg::imageNamedDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::imageNamedDlg)
{
    ui->setupUi(this);
}

imageNamedDlg::~imageNamedDlg()
{
    delete ui;
}

void imageNamedDlg::on_buttonBox_accepted()
{
    emit sendData(ui->lineEdit->text());
}
