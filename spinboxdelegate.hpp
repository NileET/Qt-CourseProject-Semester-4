#ifndef SPINBOXDELEGATE_HPP
#define SPINBOXDELEGATE_HPP

#include <QStyledItemDelegate>


class SpinBoxDelegate : public QStyledItemDelegate
{
public:
  /**
   * @brief SpinBoxDelegate  - конструктор класса
   */
  explicit SpinBoxDelegate(QWidget *parent = nullptr);

  /**
   * @brief createEditor - создает виджет-редактор с QSpinBox
   * @return Возвращает указатель на созданный виджет-редактор
   */
  QWidget *createEditor(QWidget *parent,
                        const QStyleOptionViewItem &option,
                        const QModelIndex &index) const override;

  /**
   * @brief setEditorData - передает значение из ячейки таблицы в виджет-редактор
   * @param editor - принимаемый виджет-редактор
   * @param index - редактируемая ячейка таблицы
   */
  void setEditorData(QWidget *editor,
                     const QModelIndex &index) const override;

  /**
   * @brief setModelData - передает значение из виджета-редактора в ячейку таблицы
   * @param editor - принимаемый виджет-редактор
   * @param model - модель таблицы, хранящая все данные
   * @param index - редактируемая ячейка таблицы
   */
  void setModelData(QWidget *editor,
                    QAbstractItemModel *model,
                    const QModelIndex &index) const override;

  /**
   * @brief updateEditorGeometry - определяет расположение виджета-редактора в таблице
   * @param editor - принимаемый виджет-редактор
   * @param option - принимаемые опции ячейки
   */
  void updateEditorGeometry(QWidget *editor,
                            const QStyleOptionViewItem &option,
                            const QModelIndex &index) const override;
};

#endif // SPINBOXDELEGATE_HPP
