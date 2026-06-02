#ifndef COLVIEW_H
#define COLVIEW_H
#include <QApplication>
#include <QBrush>
#include <QCamera>
#include <QColor>
#include <QGraphicsProxyWidget>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QGraphicsView>
#include <QMediaCaptureSession>
#include <QMediaDevices>
#include <QObject>
#include <QPen>
#include <QPermissions>
#include <QVideoWidget>

#include "ui_colview.h"
class ColView : public QWidget, private Ui::ColView {
  Q_OBJECT

public:
  explicit ColView(QWidget *parent = nullptr);
  bool connect_camera_granted();
  bool CameraPermission();

  QGraphicsView *view;
  // QGraphicsScene *scene;
  QGraphicsProxyWidget *videoProxy;
  //
  QCamera *m_camera;
  QMediaCaptureSession *m_captureSession;
  // Replaced QVideoWidget with Graphics View components
  QGraphicsScene *m_scene;
  QGraphicsView *m_view;
  QGraphicsVideoItem *m_videoItem;

  public slots:
  void RingChanged(RingDef rd);

};

#endif // COLVIEW_H
