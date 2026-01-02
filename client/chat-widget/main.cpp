#include <QApplication>
#include <QDir>
#include <QFile>
#include <QSettings>

#include "mainwindow.hpp"

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);

    QFile qss(":/style/stylesheet.qss");
    if (qss.open(QFile::ReadOnly)) {
        qDebug() << "Open style file success.";
        QString style = QLatin1String(qss.readAll());
        application.setStyleSheet(style);
        qss.close();
    } else {
        qDebug() << "Open style file failed.";
    }

    QString config_file = "config.ini";
    QString app_path = QCoreApplication::applicationDirPath();
    QString config_path = QDir::toNativeSeparators(app_path + QDir::separator() + config_file);
    QSettings settings(config_path, QSettings::IniFormat);
    QString gate_host = settings.value("GateServer/host").toString();
    QString gate_port = settings.value("GateServer/port").toString();
    gate_url_prefix = "http://" + gate_host + ":" + gate_port;
    qDebug() << "The GateServer url is " << gate_url_prefix;

    MainWindow window;
    window.show();

    return application.exec();
}
