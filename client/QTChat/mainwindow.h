#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class LoginDialog;
class RegisterDialog;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void slotSwitchRegister();

private:
    Ui::MainWindow* ui;
    LoginDialog* _login_dialog;
    RegisterDialog* _register_dialog;
};
#endif // MAINWINDOW_H
