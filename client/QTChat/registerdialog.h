#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

#include "global.h"

namespace Ui {
    class RegisterDialog;
}

class RegisterDialog : public QDialog {
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget* parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_get_code_btn_clicked();
    void slot_register_mod_finish(ReqId id, QString str, ErrorCodes err);

private:
    void showTip(QString str, bool ok);
    void initHttpHandlers();

    Ui::RegisterDialog* ui;
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
};

#endif // REGISTERDIALOG_H
