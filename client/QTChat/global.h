#ifndef GLOBAL_H
#define GLOBAL_H

#include <QByteArray>
#include <QNetworkReply>
#include <QRegularExpression>
#include <QWidget>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>

#include "QStyle"

/* refresh qss */
extern std::function<void(QWidget*)> repolish;

/* request id */
enum ReqId {
    ID_GET_VARIFY_CODE = 1001, /* getting a CAPTCHA */
    ID_REG_USER = 1002,        /* register user */
};

enum Modules {
    REGISTERMOD = 0, /* user register module */
};

enum ErrorCodes {
    SUCCESS = 0,
    ERR_JSON = 1, /* Json parsing failed */
    ERR_NETWORK = 2,
};

#endif // GLOBAL_H
