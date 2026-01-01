#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QObject>
#include <QString>
#include <QUrl>

#include "global.hpp"
#include "singleton.hpp"

// CRTP
class HttpMgr
    : public QObject,
      public Singleton<HttpMgr>,
      public std::enable_shared_from_this<HttpMgr> {
    Q_OBJECT

public:
    ~HttpMgr(); // 用于触发 Singleton 的 m_instance 共享指针的析构函数

    void PostHttpRequest(QUrl url, QJsonObject json, RequestId request_id, Modules mod);

signals:
    void signal_http_finish(RequestId id, QString res, ErrorCodes error, Modules mod);
    void signal_register_mod_finish(RequestId id, QString res, ErrorCodes error);

private slots:
    void slot_http_finish(RequestId id, QString res, ErrorCodes error, Modules mod);

private:
    friend class Singleton<HttpMgr>; // 赋予 Singleton 访问 HttpMgr 的权限
    HttpMgr();                       // 单例构造函数设置为私有的

    QNetworkAccessManager m_manger;
};
