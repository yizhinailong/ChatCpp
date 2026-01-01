#pragma once

#include <QDialog>

namespace Ui {
    class LoginDialog;
}

class LoginDialog : public QDialog {
    Q_OBJECT

public:
    explicit LoginDialog(QWidget* parent = nullptr);
    ~LoginDialog();

signals:
    void signal_switch_register();

private:
    Ui::LoginDialog* ui;
};
