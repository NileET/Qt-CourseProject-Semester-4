#ifndef TABLEMODEL_HPP
#define TABLEMODEL_HPP

#include <QAbstractTableModel>
#include <QList>
#include "switch.hpp"

class TableModel : public QAbstractTableModel
{
  Q_OBJECT

  QList<Switch> _switches;
  int columns;

public:
  TableModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent) const;
  int columnCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role);
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  void insertValue(const Switch &value);
  void removeValue();

  QList<Switch> getList() const {return _switches;}

};

#endif // TABLEMODEL_HPP
