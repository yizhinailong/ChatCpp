#include <QApplication>
#include <QFile>

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

    MainWindow window;
    window.show();

    return application.exec();
}
