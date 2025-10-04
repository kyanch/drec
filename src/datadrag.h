#pragma once

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QLabel>
#include <QMouseEvent>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class DataDrag;
}
QT_END_NAMESPACE

class DataDrag : public QWidget {
  Q_OBJECT
public:
  DataDrag(QWidget *parent = nullptr);
  ~DataDrag();

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
  void add_item(QString path);

private:
  Ui::DataDrag *ui;
  bool m_dragable;
  QString m_path;
  QPoint m_dragStartPos;
};