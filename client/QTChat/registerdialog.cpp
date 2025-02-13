#include "registerdialog.h"

#include "global.h"
#include "httpmgr.h"
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

    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_register_mod_finish,
            this, &RegisterDialog::slot_register_mod_finish);

    initHttpHandlers();
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
        // TODO: send https request
        QJsonObject json_obj;
        json_obj["email"] = email;
        HttpMgr::GetInstance()->PostHttpReq(
            QUrl(gate_url_prefix + "/get_varifycode"), json_obj, ReqId::ID_GET_VARIFY_CODE, Modules::REGISTERMOD);
    } else {
        showTip(tr("email format error"), false);
    }
}

void RegisterDialog::slot_register_mod_finish(ReqId id, QString str, ErrorCodes err) {
    if (err != ErrorCodes::SUCCESS) {
        showTip(tr("network request error"), false);
        return;
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(str.toUtf8());
    if (jsonDoc.isEmpty() || !jsonDoc.isObject()) {
        showTip(tr("Json parsing error"), false);
        return;
    }

    _handlers[id](jsonDoc.object());
    return;
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

void RegisterDialog::initHttpHandlers() {
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](const QJsonObject& jsonObj) {
        int error = jsonObj["error"].toInt();
        if (error != ErrorCodes::SUCCESS) {
            showTip(tr("parameter error"), false);
            return;
        }

        auto email = jsonObj["email"].toString();
        showTip(tr("the email has been sent, please check it"), true);
        qDebug() << "the email is " << email;
    });
}
