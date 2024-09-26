#ifndef DIALOG_PTSNUMRECORD_H
#define DIALOG_PTSNUMRECORD_H

#include <QDialog>

namespace Ui {
class PtsNumRecordDlg;
}

class PtsNumRecordDlg : public QDialog
{
    Q_OBJECT

public:
    explicit PtsNumRecordDlg(QWidget *parent = nullptr);
    ~PtsNumRecordDlg();

private:
    Ui::PtsNumRecordDlg *ui;
signals:
    void sendData(int);
private slots:
    void on_buttonBox_accepted();
};

#endif // DIALOG_PTSNUMRECORD_H
