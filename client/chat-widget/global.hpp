#pragma once

#include <QRegularExpression>
#include <QStyle>
#include <QWidget>
#include <functional>

/**
 * @brief repolish 用来刷新 stylesheel.qss
 */
extern std::function<void(QWidget*)> repolish;

enum class RequestId {
    ID_GET_VERIFY_CODE,
    ID_REGISTER_USER,
};

enum class Modules {
    REGISTER_MODULE,
};

enum class ErrorCodes {
    SUCCESS,
    ERROR_JSON,
    ERROR_NETWORK,
};
