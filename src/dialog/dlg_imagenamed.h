#ifndef DLG_IMAGENAMED_H
#define DLG_IMAGENAMED_H

#include <QDialog>

namespace Ui {
class imageNamedDlg;
}

class imageNamedDlg : public QDialog
{
    Q_OBJECT

public:
    explicit imageNamedDlg(QWidget *parent = nullptr);
    ~imageNamedDlg();

private:
    Ui::imageNamedDlg *ui;


signals:
    void sendData(QString);
private slots:
    void on_buttonBox_accepted();
};

#endif // DLG_IMAGENAMED_H
