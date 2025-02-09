#include "mainwindow.h"

#include "logindialog.h"
#include "registerdialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    /* load the login page  */
    _login_dialog = new LoginDialog();
    setCentralWidget(_login_dialog);
    _login_dialog->show();

    /* receive events from LoginDialog */
    connect(_login_dialog, &LoginDialog::switchRegister, this, &MainWindow::slotSwitchRegister);
    /* load the Register page */
    _register_dialog = new RegisterDialog();
}

MainWindow::~MainWindow() {
    delete ui;

    if (_login_dialog) {
        delete _login_dialog;
        _login_dialog = nullptr;
    }

    if (_register_dialog) {
        delete _register_dialog;
        _register_dialog = nullptr;
    }
}

void MainWindow::slotSwitchRegister() {
    setCentralWidget(_register_dialog);
    _login_dialog->hide();
    _register_dialog->show();
}
