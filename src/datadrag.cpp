#include "datadrag.h"
#include <QApplication>
#include <QList>
#include <QDrag>
#include <QMimeData>
#include <QUrl>
#include <QDebug>

DataDrag::DataDrag(QWidget *parent) : QWidget(parent) {
  setAcceptDrops(true);
  setStyleSheet("background-color:blue");
}

void DataDrag::dragEnterEvent(QDragEnterEvent *event) {
  if (event->mimeData()->hasUrls()) {
    // TODO: validate files existance
    event->acceptProposedAction();
  } else {
    event->ignore();
  }
}
void DataDrag::dragMoveEvent(QDragMoveEvent *event) {
  if (event->mimeData()->hasUrls())
    event->acceptProposedAction();
}
void DataDrag::dropEvent(QDropEvent *event) {
  if (event->mimeData()->hasUrls()) {
    auto files = event->mimeData()->urls();
    for (QUrl file : files) {
      if (file.isLocalFile()) {
        m_path = file.toLocalFile();
      } else {
        qDebug() << "url:" << file << " is not local file.";
      }
    }
  }
}

void DataDrag::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    m_dragStartPos = event->pos();
  }
}

void DataDrag::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() & Qt::LeftButton && check_drag_distance(event)) {
    start_drag(m_path);
  }
}

bool DataDrag::check_drag_distance(QMouseEvent *event) {
  return (event->pos() - m_dragStartPos).manhattanLength() >=
         QApplication::startDragDistance();
}

void DataDrag::start_drag(QString path) {
    QDrag *drag = new QDrag(this);
    QMimeData* data = new QMimeData;
    data->setUrls({QUrl::fromLocalFile(path)});
    drag->setMimeData(data);

    // only copy action is allowed, keep file exist in original place.
    Qt::DropAction result = drag->exec(Qt::CopyAction);
}