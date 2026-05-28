#include "colview.h"

ColView::ColView(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    video = new QVideoWidget(w_video);
    video->show();


    // 1. Create the main window and video widget
    video->resize(480, 480);
    video->showMaximized();
    video->show();

    // 2. Access the default system camera
    camera = new QCamera(QMediaDevices::defaultVideoInput());

    // 3. Create the media session to link camera and output
    captureSession = new QMediaCaptureSession();
    captureSession->setCamera(camera);
    captureSession->setVideoOutput(video);

    // 4. Start the camera feed
    camera->start();


}
