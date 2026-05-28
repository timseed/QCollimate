#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <QPermissions>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
// We tried to do this in the Info.plist - but that was not enough.
    qApp->requestPermission(
        QCameraPermission{}, [](const QPermission &permission) {
            if (permission.status() == Qt::PermissionStatus::Granted) {
                qDebug() << "Camera granted";
            } else {
                qDebug() << "Camera denied";
            }
        });
    MainWindow w;
    w.show();
    return a.exec();
}
