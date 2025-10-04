#include "datadrag.h"
#include "./ui_datadrag.h"

#include <QApplication>
#include <QFileIconProvider>
#include <QDebug>
#include <QDrag>
#include <QList>
#include <QMimeData>
#include <QUrl>

DataDrag::DataDrag(QWidget *parent)
    : QWidget(parent), ui(new Ui::DataDrag), m_dragable(false) {
  ui->setupUi(this);
  setAcceptDrops(true);
  setStyleSheet("border: 2px solid red;");
}
DataDrag::~DataDrag() { delete ui; }

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
        add_item(file.toLocalFile());
      } else {
        qDebug() << "url:" << file << " is not local file.";
      }
    }
  }
}

void DataDrag::dragLeaveEvent(QDragLeaveEvent *event) {}

void DataDrag::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    m_dragStartPos = event->pos();
  }
}

void DataDrag::mouseMoveEvent(QMouseEvent *event) {
  if (m_dragable && event->buttons() & Qt::LeftButton &&
      check_drag_distance(event)) {
    start_drag(ui->selector->currentText());
  }
}

bool DataDrag::check_drag_distance(QMouseEvent *event) {
  return (event->pos() - m_dragStartPos).manhattanLength() >=
         QApplication::startDragDistance();
}

void DataDrag::start_drag(QString path) {
  QDrag *drag = new QDrag(this);
  QMimeData *data = new QMimeData;
  data->setUrls({QUrl::fromLocalFile(path)});
  drag->setMimeData(data);

  // only copy action is allowed, keep file exist in original place.
  Qt::DropAction result = drag->exec(Qt::CopyAction);
}
void DataDrag::add_item(QString path) {
  static QFileIconProvider icon_provider;
  QIcon icon = icon_provider.icon(QFileInfo(path));
  ui->selector->addItem(icon,path,QVariant(path));
  m_dragable=true;
}