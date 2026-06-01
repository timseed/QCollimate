#include "colview.h"

ColView::ColView(QWidget *parent) : QWidget(parent) {
  setupUi(this);
  // We need to set the Ring Widget Id's
  rw_1->setId(0);
  rw_2->setId(1);
  rw_3->setId(2);

  CameraPermission();
}

bool ColView::connect_camera_granted() {

  // 1. Set up the Graphics Scene and View
  m_scene = new QGraphicsScene(this);
  m_view = new QGraphicsView(m_scene, this);
  qDebug() << "try and add m_view to layout";

  frame_video->layout()->addWidget(m_view);
  qDebug() << "Added view to the layout";
  //  ui->frame_vid->setLayout(layout);
  qDebug() << "layout placed on form ";

  //  resize(800, 600);
  // 2. Setup Camera
  qDebug() << "Trying to use... "
           << QMediaDevices::defaultVideoInput().description();
  m_camera = new QCamera(QMediaDevices::defaultVideoInput());
  m_captureSession = new QMediaCaptureSession(this);

  // 3. Connect the pipeline
  // Create the Video Item and add it to the scene
  m_videoItem = new QGraphicsVideoItem();
  m_scene->addItem(m_videoItem);
  // Optional: Give the video item a fixed size so the scene knows how big it is
  m_videoItem->setSize(QSizeF(640, 480));

  // 4. Connect the pipeline
  m_captureSession->setCamera(m_camera);
  // Note: We use setVideoOutput just like before, but pass the graphics item
  m_captureSession->setVideoOutput(m_videoItem);
  //================= Overlay Section Stars ========================
  // 5. Create and overlay the rectangle
  // Parameters: x, y, width, height
  QGraphicsRectItem *rectItem = new QGraphicsRectItem(100, 100, 200, 150);

  // Style the rectangle (e.g., a 3-pixel thick red outline, no fill)
  QPen redPen(Qt::red);
  redPen.setWidth(3);
  rectItem->setPen(redPen);

  // CRITICAL: Ensure the rectangle renders on top of the video
  // The default Z-value is 0. Setting it to 1 puts it above the video item.
  rectItem->setZValue(1);
  //================= Overlay Section Ends ========================
  m_scene->addItem(rectItem);
  // 4. Start the camera feed
  qDebug() << "About to start camera";
  m_camera->start();
  qDebug() << "Camera started";
  return true;
}

bool ColView::CameraPermission() {
  QCameraPermission cameraPermission;
  switch (qApp->checkPermission(cameraPermission)) {
  case Qt::PermissionStatus::Undetermined:
    qApp->requestPermission(cameraPermission, this, &ColView::CameraPermission);
    return false;
  case Qt::PermissionStatus::Denied:
    qDebug() << "Permission denied";
    return false;
  case Qt::PermissionStatus::Granted:
    return connect_camera_granted();
  }
  return true;
}
