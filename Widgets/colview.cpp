#include "colview.h"

ColView::ColView(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    CameraPermission();
}

bool ColView::connect_camera_granted()
{
    video = new QVideoWidget(w_video);
    video->show();
    video->setStyleSheet("background:red;");

    // 1. Create the main window and video widget
    video->resize(480, 480);
    video->showMaximized();
    video->show();

    // 2. Access the default system camera
    qDebug() << "Trying to use "<< QMediaDevices::defaultVideoInput().description();
    camera = new QCamera(QMediaDevices::defaultVideoInput());

    // 3. Create the media session to link camera and output
    captureSession = new QMediaCaptureSession();
    captureSession->setCamera(camera);
    captureSession->setVideoOutput(video);

    // 4. Start the camera feed
    camera->start();
    return true;
}

bool ColView::CameraPermission()
{
    QCameraPermission cameraPermission;
    switch (qApp->checkPermission(cameraPermission)) {
    case Qt::PermissionStatus::Undetermined:
        qApp->requestPermission(cameraPermission, this,
                                &ColView::CameraPermission);
        return false;
    case Qt::PermissionStatus::Denied:
        qDebug() << "Permission denied";
        return false;
    case Qt::PermissionStatus::Granted:
        return connect_camera_granted();
    }
    return true;
}
