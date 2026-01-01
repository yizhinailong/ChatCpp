#include "httpmgr.hpp"

#include <QByteArray>
#include <QDebug>
#include <QNetworkReply>
#include <QString>

HttpMgr::~HttpMgr() {
}

HttpMgr::HttpMgr() {
    connect(this, &HttpMgr::signal_http_finish, this, &HttpMgr::slot_http_finish);
}

void HttpMgr::PostHttpRequest(QUrl url, QJsonObject json, RequestId request_id, Modules mod) {
    QByteArray data = QJsonDocument(json).toJson();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));
    auto self = shared_from_this(); // 用于防止提前释放指针的情况
    QNetworkReply* reply = m_manger.post(request, data);
    QObject::connect(reply, &QNetworkReply::finished, [self, reply, request_id, mod]() {
        // 处理错误情况
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << reply->errorString();
            // 发送信号通知请求完成
            emit self->signal_http_finish(request_id, "", ErrorCodes::ERROR_NETWORK, mod);
            reply->deleteLater();
            return;
        }
        // 无错误
        QString res = reply->readAll();
        // 发送信号通知请求完成
        emit self->signal_http_finish(request_id, res, ErrorCodes::SUCCESS, mod);
        reply->deleteLater();
        return;
    });
}

void HttpMgr::slot_http_finish(RequestId id, QString res, ErrorCodes error, Modules mod) {
    if (mod == Modules::REGISTER_MODULE) {
        // 发送信号通知指定模块 Http 的响应结束了
        emit signal_register_mod_finish(id, res, error);
    }
}
