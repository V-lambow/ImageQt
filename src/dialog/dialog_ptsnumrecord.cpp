#include "dialog_ptsnumrecord.h"
#include "ui_dialog_ptsnumrecord.h"

PtsNumRecordDlg::PtsNumRecordDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PtsNumRecordDlg)
{
    ui->setupUi(this);
}

PtsNumRecordDlg::~PtsNumRecordDlg()
{
    delete ui;
}
void PtsNumRecordDlg::on_buttonBox_accepted()
{
    emit sendData(ui->x->value());
}
