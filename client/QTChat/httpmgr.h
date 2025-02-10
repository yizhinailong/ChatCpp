#ifndef HTTPMGR_H
#define HTTPMGR_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QObject>
#include <QString>
#include <QUrl>

#include "singleton.h"

class HttpMgr
    : public QObject,
      public Singleton<HttpMgr>,
      public std::enable_shared_from_this<HttpMgr> {

    Q_OBJECT

public:
    ~HttpMgr();

private:
    friend class Singleton<HttpMgr>;
    HttpMgr();

    QNetworkAccessManager* _manager;

    void PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod);

private slots:
    void slot_http_finish(ReqId id, QString str, ErrorCodes err, Modules mod);

signals:
    void sig_http_finish(ReqId id, QString str, ErrorCodes err, Modules mod);
    void sig_register_mod_finish(ReqId id, QString str, ErrorCodes err);
};

#endif // HTTPMGR_H
