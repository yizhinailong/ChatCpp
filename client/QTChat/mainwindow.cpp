#include "mainwindow.h"

#include "logindialog.h"
#include "registerdialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    /* load the login page  */
    _login_dialog = new LoginDialog(this);
    setCentralWidget(_login_dialog);
    _login_dialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    /* receive events from LoginDialog */
    connect(_login_dialog, &LoginDialog::switchRegister, this, &MainWindow::slotSwitchRegister);
    /* load the Register page */
    _register_dialog = new RegisterDialog(this);
    _register_dialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    _register_dialog->hide();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::slotSwitchRegister() {
    setCentralWidget(_register_dialog);
    _login_dialog->hide();
    _register_dialog->show();
}
