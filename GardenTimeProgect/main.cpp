#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QFontDatabase>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFontDatabase::addApplicationFont(":/fonts/Fixedsys.ttf");
    MainWindow w;
    QFile file(":/qss/styles.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        a.setStyleSheet(styleSheet);
        file.close();
    }
    w.show();
    return a.exec();
}

