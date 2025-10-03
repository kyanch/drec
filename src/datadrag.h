#pragma once

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QLabel>
#include <QMouseEvent>
#include <QWidget>

class DataDrag : public QWidget {
public:
  DataDrag(QWidget *parent = nullptr);

protected:
  void dragEnterEvent(QDragEnterEvent *event) override;
  void dragMoveEvent(QDragMoveEvent *event) override;
  void dragLeaveEvent(QDragLeaveEvent *event) override;
  void dropEvent(QDropEvent *event) override;

  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

private:
  inline bool check_drag_distance(QMouseEvent *event);
  void start_drag(QString path);

private:
  QString m_path;
  QPoint m_dragStartPos;
};