#ifndef TABLEMODEL_HPP
#define TABLEMODEL_HPP

#include <QAbstractTableModel>
#include <QMap>
#include "switch.hpp"

class TableModel : public QAbstractTableModel
{
  Q_OBJECT

  QMap<int, Switch> _switches;
  int _columns;

public:
  TableModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent) const;
  int columnCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role);
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  // Удаление всех данных
  void clear();
  // Удаление одной записи
  void removeValue(const int &tableID);
  // Добавление записи в конец
  void insertValue(const Switch &value);

  QMap<int, Switch> toQMap() const {return _switches;}

};

#endif // TABLEMODEL_HPP
