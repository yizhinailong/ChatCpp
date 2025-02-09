#include "logindialog.h"

#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::LoginDialog) {
    ui->setupUi(this);

    /* send button register_btn click events */
    connect(ui->register_btn, &QPushButton::clicked, this, &LoginDialog::switchRegister);
}

LoginDialog::~LoginDialog() {
    delete ui;
}
