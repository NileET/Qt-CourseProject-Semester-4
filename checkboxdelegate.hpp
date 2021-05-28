#ifndef CHECKBOXDELEGATE_HPP
#define CHECKBOXDELEGATE_HPP

#include <QStyledItemDelegate>

class CheckBoxDelegate : public QStyledItemDelegate
{
public:
  explicit CheckBoxDelegate(QWidget *parent = nullptr);

  // Метод, создающий виджет-редактор с QCheckBox
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

  // Метод, описывающий как должна быть нарисована ячейка таблицы
  void paint(QPainter *painter,
             const QStyleOptionViewItem &option,
             const QModelIndex &index) const;

  // Метод, описывающий поведение ячейки
  bool editorEvent(QEvent *event,
                   QAbstractItemModel *model,
                   const QStyleOptionViewItem &option, const QModelIndex &index);
};

#endif // CHECKBOXDELEGATE_HPP
