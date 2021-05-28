#include "checkboxdelegate.hpp"

#include <QCheckBox>
#include <QApplication>
#include <QPainter>

CheckBoxDelegate::CheckBoxDelegate(QWidget *parent) :
  QStyledItemDelegate(parent)
{ }

QWidget *CheckBoxDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
  Q_UNUSED(option);
  Q_UNUSED(index);

  // Создаем виджет-редактор
  QCheckBox *editor = new QCheckBox(parent);

  return editor;
}

void CheckBoxDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
{
  // Извлекаем данные
  bool value = index.model()->data(index, Qt::DisplayRole).toBool();

  QCheckBox *checkBox = qobject_cast<QCheckBox *>(editor);

  // Устанавливаем значение в checkbox
  checkBox->setChecked(value);
}

void CheckBoxDelegate::setModelData(QWidget *editor,
                                    QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
  model->setData(index, qobject_cast<QCheckBox *>(editor)->isChecked(), Qt::EditRole);
}

void CheckBoxDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
  Q_UNUSED(index);
  // Для переноса checkbox в центр ячейки создаем объект
  // и изменяем его свойства
  QStyleOptionButton newEditorOption;
  QRect rectIndicator =
          QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator,
                                                &newEditorOption);
  newEditorOption.rect = option.rect;
  newEditorOption.rect.setLeft(option.rect.x() +
                               option.rect.width()/2 -
                               rectIndicator.width()/2);

  editor->setGeometry(newEditorOption.rect);
}

void CheckBoxDelegate::paint(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    // Обрабатываем прорисовку элемента CheckBoxIndicator с центрированием
    QStyleOptionButton newEditorOption;
    QRect rectIndicator =
            QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator,
                                                  &newEditorOption);
    newEditorOption.rect = option.rect;
    newEditorOption.rect.setLeft(option.rect.x() +
                                 option.rect.width()/2 -
                                 rectIndicator.width()/2);

    // Конвертируем имеющиеся значение в тип данных bool
    if (index.data().toBool())
        // Если это возможно и значение является истинным (true),
        // то рисуем флажок, через побитовое "ИЛИ" с присвоением
        newEditorOption.state |= QStyle::State_On;

    else
        // Если это возможно, но значение является ложным (false),
        // то стираем флажок QCheckBox
        newEditorOption.state |= QStyle::State_Off;


    // Для сохранения возможности выделения ячейки без её редактирования
    // с использованием побитового "И" проверяем флаг State_Selected
    if (option.state & QStyle::State_Selected)
        // Если он стоит, то оставляем подсветку ячейки в случае выделения мышью
        painter->fillRect(option.rect, option.palette.highlight());

    // Перерисовываем ячейку согласно новым правилам
    QApplication::style()->drawControl(QStyle::CE_CheckBox,
                                       &newEditorOption,
                                       painter);
}

bool CheckBoxDelegate::editorEvent(QEvent *event,
                                   QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index)
{
  Q_UNUSED(option);

  // При отпускании ЛКМ
  if (event->type() == QEvent::MouseButtonRelease)
  {
      // Смена состояния флажка QCheckBox
      model->setData(index, !index.data().toBool());

      return true;
  }

  return false;
}
