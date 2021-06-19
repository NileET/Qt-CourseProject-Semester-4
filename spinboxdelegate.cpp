#include "spinboxdelegate.hpp"

#include <QSpinBox>
#include <QApplication>
#include <QAbstractItemView>


SpinBoxDelegate::SpinBoxDelegate(QWidget *parent) :
  QStyledItemDelegate(parent)
{ }

QWidget *SpinBoxDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &option,
                                       const QModelIndex &index) const
{
  Q_UNUSED(option);
  Q_UNUSED(index);

  // Создаем виджет-редактор
  QSpinBox *editor = new QSpinBox(parent);

  // Убираем рамку
  editor->setFrame(false);

  if (index.column() == 3)
      // Устанавливаем min и max значения
      editor->setRange(0, 100);
  else if (index.column() == 6) {
      // Устанавливаем минимальное значение
      editor->setRange(0, 2'147'483'647);
      editor->setSingleStep(100);
      // Устанавливаем суффикс
      editor->setSuffix(" ₽");
    }

  return editor;
}

void SpinBoxDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
  int value = 0;

  // Извлекаем данные
  if (index.column() == 3) {
      value = index.model()->data(index, Qt::EditRole).toInt();
    }
  else if (index.column() == 6) {
      QString strValue = index.model()->data(index, Qt::EditRole).toString();
      strValue.chop(2);
      value = strValue.toInt();
    }


  QSpinBox *spinBox = qobject_cast<QSpinBox *>(editor);

  // Устанавливаем значение в spinbox
  spinBox->setValue(value);
}

void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
  QSpinBox *spinBox = qobject_cast<QSpinBox *>(editor);

  // Если со времени последней интерпретации текст изменился, испускаются сигналы
  spinBox->interpretText();

  // Устанавливаем значение в ячейку таблицы
  model->setData(index, spinBox->value(), Qt::EditRole);
}

void SpinBoxDelegate::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &index) const
{
  Q_UNUSED(index);

  // Указываем, что используемое нами поле ввода должно находится
  // на месте той ячейке, которую мы редактируем
  editor->setGeometry(option.rect);
}
