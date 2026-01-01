#include "registerdialog.hpp"

#include "ui_registerdialog.h"

#include "global.hpp"
#include "httpmgr.hpp"

RegisterDialog::RegisterDialog(QWidget* parent)
    : QDialog(parent),
      ui(new Ui::RegisterDialog) {
    ui->setupUi(this);
    ui->passwd_edit->setEchoMode(QLineEdit::Password);
    ui->confirm_passwd_edit->setEchoMode(QLineEdit::Password);
    ui->error_tip->setProperty("state", "normal");
    repolish(ui->error_tip);

    connect(HttpMgr::GetInstance().get(),
            &HttpMgr::signal_register_mod_finish,
            this,
            &RegisterDialog::slot_register_mod_finish);

    InitHttpHandlers();
}

RegisterDialog::~RegisterDialog() {
    delete ui;
}

void RegisterDialog::on_verify_button_clicked() {
    auto email = ui->email_edit->text();
    QRegularExpression regex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    bool match = regex.match(email).hasMatch();
    if (match) {
        ShowTip(tr("邮箱地址正确"), true);
        // TODO 发送验证码
    } else {
        ShowTip(tr("邮箱地址不正确"), false);
    }
}

void RegisterDialog::slot_register_mod_finish(RequestId id, QString res, ErrorCodes error) {
    if (error != ErrorCodes::SUCCESS) {
        ShowTip(tr("网络请求错误"), false);
    }

    // 解析 Json 字符串
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if (jsonDoc.isNull()) {
        ShowTip(tr("Json 解析为空"), false);
        return;
    }
    // Json 解析错误
    if (!jsonDoc.isObject()) {
        ShowTip(tr("Json 解析错误"), false);
        return;
    }
    // Json 解析成功
    m_handlers[id](jsonDoc.object());
    return;
}

void RegisterDialog::InitHttpHandlers() {
    // 注册获取验证码会熬的逻辑
    m_handlers.insert(RequestId::ID_GET_VERIFY_CODE, [this](const QJsonObject& json_obj) {
        int error = json_obj["error"].toInt();
        if (static_cast<ErrorCodes>(error) != ErrorCodes::SUCCESS) {
            ShowTip(tr("参数错误"), false);
            return;
        }

        auto email = json_obj["email"].toString();
        ShowTip(tr("验证码已经发送到邮箱，请注意查收"), true);
        qDebug() << "Email is " << email;
    });
}

void RegisterDialog::ShowTip(QString str, bool b_ok) {
    if (b_ok) {
        ui->error_tip->setProperty("state", "normal");
    } else {
        ui->error_tip->setProperty("state", "error");
    }
    ui->error_tip->setText(str);
    repolish(ui->error_tip);
}
