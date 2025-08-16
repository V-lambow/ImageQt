#ifndef DLG_RESOLUTIONMANAGER_H
#define DLG_RESOLUTIONMANAGER_H

#include <QDialog>

namespace Ui {
class ResolutionManagerDlg;
}

class ResolutionManagerDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ResolutionManagerDlg(QWidget *parent = nullptr);
    explicit ResolutionManagerDlg(QWidget *parent = nullptr,std::map<QString,double>* resolution=nullptr,double* curresolution=nullptr);
    ~ResolutionManagerDlg();

private:
    Ui::ResolutionManagerDlg *ui;
    std::map<QString,double>m_resolution;
    double  m_curresolution=0.0;
signals:
    void sendData(double);
private slots:
    void on_pb_delete_clicked();
    void on_pushButton_clicked();
};

#endif // DLG_RESOLUTIONMANAGER_H
