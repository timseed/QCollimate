#include "mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QCoreApplication>
#include <QPermissions>
#include <QThread>
int main(int argc, char *argv[]) {
    qDebug() << "QCollimate starting";
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow();
    w->show();
    return a.exec();

}
