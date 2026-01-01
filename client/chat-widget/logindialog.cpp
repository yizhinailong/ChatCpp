#include "logindialog.hpp"

#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget* parent)
    : QDialog(parent),
      ui(new Ui::LoginDialog) {
    ui->setupUi(this);

    // 创建注册按钮和注册页面的绑定
    connect(ui->register_button, &QPushButton::clicked, this, &LoginDialog::signal_switch_register);
}

LoginDialog::~LoginDialog() {
    delete ui;
}
