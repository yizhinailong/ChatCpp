#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

namespace Ui {
    class RegisterDialog;
}

class RegisterDialog : public QDialog {
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget* parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_get_code_btn_clicked();

private:
    void showTip(QString str, bool ok);
    Ui::RegisterDialog* ui;
};

#endif // REGISTERDIALOG_H
