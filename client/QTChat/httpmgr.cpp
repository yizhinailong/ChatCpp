#include "httpmgr.h"

HttpMgr::~HttpMgr() {
}

HttpMgr::HttpMgr() {
    connect(this, &HttpMgr::sig_http_finish, this, &HttpMgr::slot_http_finish);
}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod) {
    QByteArray data = QJsonDocument(json).toJson();

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));

    auto self = shared_from_this();

    QNetworkReply* reply = _manager->post(request, data);
    QObject::connect(reply, &QNetworkReply::finished, [self, reply, req_id, mod]() {
        /* handing errors */
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << reply->errorString();
            /* sending a signal notifies completion */
            emit self->sig_http_finish(req_id, "", ErrorCodes::ERR_NETWORK, mod);
            reply->deleteLater();
            return;
        }

        QString res = reply->readAll();
        emit self->sig_http_finish(req_id, res, ErrorCodes::SUCCESS, mod);
        reply->deleteLater();
        return;
    });
}

void HttpMgr::slot_http_finish(ReqId id, QString str, ErrorCodes err, Modules mod) {
    if (mod == Modules::REGISTERMOD) {
        emit sig_register_mod_finish(id, str, err);
    }
}
