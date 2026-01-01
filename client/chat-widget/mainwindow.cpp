#include "mainwindow.hpp"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow) {
    ui->setupUi(this);

    m_login_dialog = new LoginDialog(this);
    m_register_dialog = new RegisterDialog(this);

    // 在主窗口中居中显示登录页面 LoginDialog
    setCentralWidget(m_login_dialog);

    // 创建和注册消息链接
    connect(m_login_dialog, &LoginDialog::signal_switch_register, this, &MainWindow::slot_switch_register);

    // 设置窗口的特性
    m_login_dialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    m_register_dialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    m_register_dialog->hide();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::slot_switch_register() {
    setCentralWidget(m_register_dialog);
    m_login_dialog->hide();
    m_register_dialog->show();
}
