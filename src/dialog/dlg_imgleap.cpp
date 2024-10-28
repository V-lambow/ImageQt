#include "dlg_imgleap.h"
#include "ui_dlg_imgleap.h"

ImgLeapDlg::ImgLeapDlg(QWidget *parent,ImageSaver* savedImg) :
    QDialog(parent),
    ui(new Ui::ImgLeapDlg),
    m_savedImg(*savedImg)
{
    ui->setupUi(this);

    QStringList imgNameList=m_savedImg.getAllImageNames();
    ui->comboBox->addItems(imgNameList);
}

ImgLeapDlg::~ImgLeapDlg()
{
    delete ui;
}

void ImgLeapDlg::on_buttonBox_accepted()
{
    sendData(ui->comboBox->currentText());
}
