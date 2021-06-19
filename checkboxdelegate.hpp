#ifndef CHECKBOXDELEGATE_HPP
#define CHECKBOXDELEGATE_HPP

#include <QStyledItemDelegate>


class CheckBoxDelegate : public QStyledItemDelegate
{
public:
  /**
   * @brief CheckBoxDelegate - конструктор класса
   */
  explicit CheckBoxDelegate(QWidget *parent = nullptr);

  /**
   * @brief createEditor - создает виджет-редактор с QCheckBox
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

  /**
   * @brief paint - описываtn поведение прорисовки в ячейке таблицы
   * @param painter - принимаемый "художник"
   * @param option - принимаемые опции ячейки
   * @param index - принимаемая ячейка
   */
  void paint(QPainter *painter,
             const QStyleOptionViewItem &option,
             const QModelIndex &index) const override;

  /**
   * @brief editorEvent - описываtn поведение ячейки
   * @param event - принимаемое событие
   * @param model - модель таблицы, хранящая все данные
   * @param index - принимаемая ячейка
   * @return Если галочка поставлена, то возвращает true, иначе - false
   */
  bool editorEvent(QEvent *event,
                   QAbstractItemModel *model,
                   const QStyleOptionViewItem &option, const QModelIndex &index) override;
};

#endif // CHECKBOXDELEGATE_HPP
