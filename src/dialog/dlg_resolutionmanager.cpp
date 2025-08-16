#include "dlg_resolutionmanager.h"
#include "ui_dlg_resolutionmanager.h"

ResolutionManagerDlg::ResolutionManagerDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResolutionManagerDlg)
{
    ui->setupUi(this);
}

ResolutionManagerDlg::~ResolutionManagerDlg()
{
    delete ui;
}
ResolutionManagerDlg::ResolutionManagerDlg(QWidget *parent,std::map<QString,double>* resolution,double* curresolution):
    QDialog(parent),
    ui(new Ui::ResolutionManagerDlg),
    m_resolution(*resolution),
    m_curresolution(*curresolution)

{
    ui->setupUi(this);
//    ui->resolution->setText(QString::number(m_resolution[ui->name->currentText()]));
    connect(ui->name,&QComboBox::currentTextChanged,this,[this](){
        ui->resolution->setText(QString::number(this->m_resolution[ui->name->currentText()]));
    });
    size_t idx =0;
    std::for_each(m_resolution.begin(),m_resolution.end(),[this,&idx](std::pair<QString,double> resolutionEle){
        ui->name->addItem(resolutionEle.first);
        if(resolutionEle.second==m_curresolution){
            ui->name->setCurrentIndex(idx);
        }
        idx++;
    });


}





void ResolutionManagerDlg::on_pb_delete_clicked()
{

    if(this->m_resolution[ui->name->currentText()]==m_curresolution){
        m_curresolution=0.0;
    }

    this->m_resolution.erase(ui->name->currentText());
    ui->resolution->clear();
    ui->name->removeItem(ui->name->currentIndex());


}

void ResolutionManagerDlg::on_pushButton_clicked()
{
    emit sendData(m_resolution[ui->name->currentText()]);
    close();
}
