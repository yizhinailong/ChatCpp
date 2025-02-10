#include "registerdialog.h"

#include "global.h"
#include "ui_registerdialog.h"

RegisterDialog::RegisterDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::RegisterDialog) {

    ui->setupUi(this);

    /* set the password display mode */
    ui->pass_edit->setEchoMode(QLineEdit::Password);
    ui->confirm_edit->setEchoMode(QLineEdit::Password);

    /* set the style transfer for hint */
    ui->error_tip->setProperty("state", "normal");
    repolish(ui->error_tip);
}

RegisterDialog::~RegisterDialog() {
    delete ui;
}

void RegisterDialog::on_get_code_btn_clicked() {
    auto email = ui->email_edit->text();

    /* a regular expression to validate email */
    static QRegularExpression regex(R"(([a-zA-Z0-9_.+-]+)@([a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+))");

    bool match = regex.match(email).hasMatch();

    if (match) {
        showTip(tr("send CAPTCHA"), true);
        // TODO: send https request
    } else {
        showTip(tr("email format error"), false);
    }
}

void RegisterDialog::showTip(QString str, bool ok) {
    if (ok) {
        ui->error_tip->setProperty("state", "normal");
    } else {
        ui->error_tip->setProperty("state", "error");
    }
    ui->error_tip->setText(str);
    repolish(ui->error_tip);
}
