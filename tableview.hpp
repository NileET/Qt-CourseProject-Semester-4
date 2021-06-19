#ifndef TABLEVIEW_HPP
#define TABLEVIEW_HPP

#include <QTableView>


class TableView : public QTableView
{
  Q_OBJECT
public:
  /**
   * @brief TableView - конструктор класса
   */
  explicit TableView(QWidget *parent = nullptr);

protected:
  /**
   * @brief mouseMoveEvent - позволяет выполнить drag&drop при зажатии ЛКМ и движении мыши
   * @param event - принимаемое действие
   */
  void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // TABLEVIEW_HPP
