#include "tableview.hpp"
#include "spinboxdelegate.hpp"
#include "checkboxdelegate.hpp"

#include <QApplication>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include <QDir>
#include <QTextStream>

TableView::TableView(QWidget *parent) :
  QTableView(parent)
{
  // Включение сортировки
  setSortingEnabled(true);
  // Задаем делегаты для нужных столбцов
  setItemDelegateForColumn(3, new SpinBoxDelegate(3, this));
  setItemDelegateForColumn(6, new SpinBoxDelegate(6, this));
  setItemDelegateForColumn(4, new CheckBoxDelegate(this));
  // Построчное выделение
  setSelectionBehavior(QAbstractItemView::SelectRows);
  // Задаем кастомное контекстное меню
  setContextMenuPolicy(Qt::CustomContextMenu);
  // Задаем Drag
  setDragEnabled(true);
  setDropIndicatorShown(true);
}

void TableView::mouseMoveEvent(QMouseEvent *event)
{
  // Если таблица пустая, то Drag&Drop не сработает
  if (model()->rowCount() == 0)
    return;

  if (event->buttons() & Qt::LeftButton) {
      int distance = (event->pos() - startPosition).manhattanLength();
      if (distance >= QApplication::startDragDistance()) {
          QModelIndex index = currentIndex();
          QString manufacturer = index.siblingAtColumn(0).data().toString();
          QString modelName    = index.siblingAtColumn(1).data().toString();
          QString baseSpeed    = index.siblingAtColumn(2).data().toString();
          QString portCount    = index.siblingAtColumn(3).data().toString();
          QString hasPoE       = index.siblingAtColumn(4).data().toString();
          QString size         = index.siblingAtColumn(5).data().toString();
          QString price        = index.siblingAtColumn(6).data().toString();

          price.chop(2);

          QFile eXport(QDir::tempPath() + "/" + manufacturer + ' ' + modelName + ".txt");

          if (eXport.open(QFile::WriteOnly | QFile::Text)) {
              QTextStream out(&eXport);

              out << " Device's manufacturer: " << manufacturer << '\n'
                  << " Device's model: "        << modelName    << '\n'
                  << " Base baud rate: "        << baseSpeed    << " (Mbps)\n"
                  << " Number of ports: "       << portCount    << '\n'
                  << " PoE support: "           << hasPoE       << '\n'
                  << " Dimensions: "            << size         << " (mm)\n"
                  << " Price: "                 << price        << " rubles\n";

            }

          QMimeData* mimeData = new QMimeData;
          mimeData->setUrls(QList<QUrl>() << QUrl::fromLocalFile(eXport.fileName()));

          eXport.close();

          QDrag *drag = new QDrag(this);
          drag->setMimeData(mimeData);
          drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
        }

      QWidget::mouseMoveEvent(event);
    }
}
