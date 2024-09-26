#ifndef DIALOG_CALIFROM3PTS_H
#define DIALOG_CALIFROM3PTS_H

#include <QDialog>
#include <QIntValidator>

namespace Ui {
class CaliFrom3PtsDlg;
}

class CaliFrom3PtsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CaliFrom3PtsDlg(QWidget *parent = nullptr);
    ~CaliFrom3PtsDlg();

private:
    Ui::CaliFrom3PtsDlg *ui;
signals:
    void sendData(double);
private slots:
    void on_buttonBox_accepted();

};

#endif // DIALOG_CALIFROM3PTS_H
