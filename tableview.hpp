#ifndef TABLEVIEW_HPP
#define TABLEVIEW_HPP

#include <QTableView>

class TableView : public QTableView
{
  Q_OBJECT
public:
  TableView(QWidget *parent = nullptr);

protected:
  void mouseMoveEvent(QMouseEvent *event);

private:
  QPoint startPosition;
};

#endif // TABLEVIEW_HPP
