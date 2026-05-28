#ifndef COLVIEW_H
#define COLVIEW_H

#include "ui_colview.h"
#include <QVideoWidget>
#include <QCamera>
#include <QMediaDevices>
#include <QMediaCaptureSession>
class ColView : public QWidget, private Ui::ColView
{
    Q_OBJECT

public:
    explicit ColView(QWidget *parent = nullptr);
    QVideoWidget *video;
    QCamera *camera;
    QMediaCaptureSession *captureSession;
};

#endif // COLVIEW_H
