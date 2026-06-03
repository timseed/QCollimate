#include "colview.h"

ColView::ColView(QWidget *parent) : QWidget(parent) {
  setupUi(this);

  // Now set the Diameter and Width
  rw_1->gui_start_values(80,10);
  rw_2->gui_start_values(50,7);
  rw_3->gui_start_values(30,3);
  // We need to set the Ring Widget Id's
  rw_1->setId(0);
  rw_2->setId(1);
  rw_3->setId(2);
  // We need to wire up the Signal from the 3 Ring Widgets
  // These need to trigger a method here
  connect(rw_1,SIGNAL(RingSize(RingDef)),this,SLOT(RingChanged(RingDef)));
  connect(rw_2,SIGNAL(RingSize(RingDef)),this,SLOT(RingChanged(RingDef)));
  connect(rw_3,SIGNAL(RingSize(RingDef)),this,SLOT(RingChanged(RingDef)));
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
  qDebug() << "About to start camera. Overlay Handled on receipt of a Signal.";
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

void ColView::UpdateScene()
{
    qDebug() <<" Entering UpdateScene";
    QGraphicsScene *oldScene = m_view->scene();
    QGraphicsScene *newScene = new QGraphicsScene(this); //m_scene->addItem(m_videoItem);
    newScene->addItem(m_videoItem);
    qDebug() << "There are currently "<<m_scene->items().count()<<" Items on the m_scene";
    qDebug() << "There are currently "<<newScene->items().count()<<" Items on the newScene";
    for (auto [key, value] : _rings.asKeyValueRange())
    {
        if (value.b_active)
        {
            qDebug() <<"Adding Ring id: "<<key;
            QGraphicsEllipseItem *elipseItem = new QGraphicsEllipseItem(m_videoItem->size().width()/2-value.diameter/2,
                                                                        m_videoItem->size().height()/2-value.diameter/2,
                                                                        value.diameter,
                                                                        value.diameter);
            // Style the rectangle (e.g., a 3-pixel thick red outline, no fill)
            QPen redPen(Qt::red);
            redPen.setWidth(value.thickness);
            elipseItem->setPen(redPen);


            elipseItem->setZValue(1);
            newScene->addItem(elipseItem);
            qDebug() << "Added Elipse X:"<<m_videoItem->size().width()/2<<" Y:"<<
                m_videoItem->size().height()/2 << " H/W: "<<value.diameter;
        }
    }
    m_view->setScene(newScene);
}

void ColView::RingChanged(RingDef rd)
    /**
     * @brief Handled the Signal indicating something has changed with the Ring parameters.
     * This needs to update the central storage (A Hash) of the Rings.
     */
{
    qDebug() << "Got Signal that a ring changed Ring Id is "<<rd.id;
    if (_rings.contains(rd.id))
    {
        // We have a Definition for this
        // Delete the stored one
        _rings.remove(rd.id);
    }
    // Add data
    _rings.insert(rd.id,rd);

    UpdateScene();

}
