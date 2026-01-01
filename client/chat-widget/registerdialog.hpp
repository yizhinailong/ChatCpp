#pragma once

#include <QDialog>

#include "global.hpp"

namespace Ui {
    class RegisterDialog;
}

class RegisterDialog : public QDialog {
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget* parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_verify_button_clicked();
    void slot_register_mod_finish(RequestId id, QString res, ErrorCodes error);

private:
    Ui::RegisterDialog* ui;

    void InitHttpHandlers();
    void ShowTip(QString str, bool b_ok);

    QMap<RequestId, std::function<void(const QJsonObject&)>> m_handlers;
};
