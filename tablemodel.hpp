#ifndef TABLEMODEL_HPP
#define TABLEMODEL_HPP

#include <QAbstractTableModel>
#include <QList>
#include "switch.hpp"


class TableModel : public QAbstractTableModel
{
  Q_OBJECT

  /**
   * @brief _switches - двусвязный список, хранящий все данные
   */
  QList<Switch> _switches;

public:
  /**
   * @brief TableModel - конструктор класса
   */
  explicit TableModel(QObject *parent = nullptr);

  /**
   * @brief rowCount - определяет количество строк в таблице
   * @return Возвращает целое число
   */
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  /**
   * @brief columnCount - определяет количество столбцов в таблице
   * @return Возвращает целое число
   */
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  /**
   * @brief data - отображает значения двусвязного списка
   * @param index - отображаемая ячейка
   * @param role - роль, при которой происходит отображение данных
   * @return Возвращает значение из двусвязного списка в типе QVariant
   */
  QVariant data(const QModelIndex &index, int role) const override;

  /**
   * @brief setData - задает значение редактируемой ячейки
   * @param index - редактируемая ячейка
   * @param value - задаваемое значение
   * @param role - роль, при которой происходит радактирование данных
   * @return Возвращает true, если редактированиие прошло успешно, в противном случае - false
   */
  bool setData(const QModelIndex &index, const QVariant &value, int role) override;

  /**
   * @brief flags - комбинация флагов, принадлежащих ячейке
   * @param index - принимаемая ячейка
   * @return Возвращает флаги элементов для данной ячейки
   */
  Qt::ItemFlags flags(const QModelIndex &index) const override;

  /**
   * @brief headerData - отображает горизонтальные заголовки
   * @param section - номер секции
   * @param orientation - выбор ориентации заголовков
   * @param role - выбранная роль
   * @return
   */
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

  /**
   * @brief insertRows - позволяет вставлять новые строки в таблицу со значением по умолчанию
   * @return Если вставка прошла успешно, то возвращает true, иначе - false
   */
  bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

  /**
   * @brief removeRows - позволяет удалить выбранную строку таблицы
   * @return Если удаление прошло успешно, то возвращает true, иначе - false
   */
  bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

  /**
   * @brief clear - удаляет все данные двусвязного свиска
   */
  void clear();

  /**
   * @brief insertValue  - позволяет вставлять новые строки в конец таблицы с необходимым значениемч
   * @param value - вставляемое значение
   */
  void insertValue(const Switch &value);

  /**
   * @brief toQList - получение значений таблицы в типе QList
   * @return Возвращает _switches
   */
  QList<Switch> toQList() const {return _switches;}
};

#endif // TABLEMODEL_HPP
