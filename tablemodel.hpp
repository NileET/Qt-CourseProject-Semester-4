#ifndef TABLEMODEL_HPP
#define TABLEMODEL_HPP

#include <QAbstractTableModel>
#include <QList>
#include "switch.hpp"

class TableModel : public QAbstractTableModel
{
  Q_OBJECT

  QList<Switch> _switches;

public:
  TableModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role);
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
  bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

  // Удаление всех данных
  void clear();
  // Добавление записи со значением в конец
  void insertValue(const Switch &value);
  // Конвертирование в QList
  QList<Switch> toQList() const {return _switches;}
};

#endif // TABLEMODEL_HPP
