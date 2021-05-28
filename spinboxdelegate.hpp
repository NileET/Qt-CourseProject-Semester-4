#ifndef SPINBOXDELEGATE_HPP
#define SPINBOXDELEGATE_HPP

#include <QStyledItemDelegate>


class SpinBoxDelegate : public QStyledItemDelegate
{
  int _column;
public:
  explicit SpinBoxDelegate(int column, QWidget *parent = nullptr);

  // Метод, создающий виджет-редактор с QSpinBox
  QWidget *createEditor(QWidget *parent,
                        const QStyleOptionViewItem &option,
                        const QModelIndex &index) const;

  // Метод, передающий значение из таблицы в виджет-редактор
  void setEditorData(QWidget *editor,
                     const QModelIndex &index) const;

  // Метод, передающий значение из виджета-редактора в таблицу
  void setModelData(QWidget *editor,
                    QAbstractItemModel *model,
                    const QModelIndex &index) const;

  // Метод, определяющий расположение виджета-редактора в таблице
  void updateEditorGeometry(QWidget *editor,
                            const QStyleOptionViewItem &option,
                            const QModelIndex &index) const;
};

#endif // SPINBOXDELEGATE_HPP
