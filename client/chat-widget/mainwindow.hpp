#pragma once

#include <QMainWindow>

#include "logindialog.hpp"
#include "registerdialog.hpp"

QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void slot_switch_register();

private:
    Ui::MainWindow* ui;
    LoginDialog* m_login_dialog;
    RegisterDialog* m_register_dialog;
};
