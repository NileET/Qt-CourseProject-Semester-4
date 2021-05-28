#include "tablemodel.hpp"

TableModel::TableModel(QObject *parent) :
  QAbstractTableModel(parent), _columns(8)
{ }

int TableModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return _switches.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return _columns;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  const Switch& sw = _switches[index.row()];

  switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
      if (index.column() == 0)
          return index.row();
      if (index.column() == 1)
          return sw.getManufacturer().c_str();
      if (index.column() == 2)
          return sw.getModelName().c_str();
      if (index.column() == 3) {
          auto speed = sw.getBaseSpeed();
          return QString("%1, %2").arg(speed.first).arg(speed.second);
        }
      if (index.column() == 4)
          return QString::number(sw.getPortCount());
      if (index.column() == 5)
          return sw.getHasPoE() ? tr("Yes") : tr("No");
      if (index.column() == 6) {
          auto size = sw.getModelSize();
          return QString("%1x%2x%3").arg(size.__width).arg(size.__length).arg(size.__high);
        }
      if (index.column() == 7)
          return QString::number(sw.getPrice()) + " ₽";
      break;
    default:
      return QVariant();
    }

  return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (!index.isValid())
    return false;

  if (role == Qt::EditRole) {
      Switch& sw =_switches[index.siblingAtColumn(0).data().toInt()];

      switch (index.column()) {
        case 1:
          sw.setManufacturer(value.toString().toStdString()); break;
        case 2:
          sw.setModelName(value.toString().toStdString()); break;
        case 3:
          {
            auto speedList = value.toStringList();
            std::pair speed = std::make_pair(speedList[0].toInt(), speedList[1].toInt());
            sw.setBaseSpeed(speed); break;
          }
        case 4:
          sw.setPortCount(value.toInt()); break;
        case 5:
          {
            QString strPoE = value.toString();
            bool PoE = strPoE == tr("Yes") ? true : false;
            sw.setHasPoE(PoE); break;
          }
        case 6:
          {
            QStringList listSize = value.toString().split("x");
            double width  = listSize[0].toDouble(),
                   length = listSize[1].toDouble(),
                   high   = listSize[2].toDouble();
            sw.setModelSize({width, length, high});
          }
        case 7:
          sw.setPrice(value.toInt()); break;
        }

      return true;
    }

  return false;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
  if (index.isValid())
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
  else
    return Qt::NoItemFlags;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
      switch (section) {
        case 0:
          return "ID";
        case 1:
          return tr("Manufacturer");
        case 2:
          return tr("Model");
        case 3:
          return tr("Base baud rate");
        case 4:
          return tr("Number of ports");
        case 5:
          return tr("PoE support");
        case 6:
          return tr("Dimensions");
        case 7:
          return tr("Price");
        }
    }
  return QVariant();
}

void TableModel::clear()
{
  _switches.clear();
  emit layoutChanged();
}

void TableModel::removeValue(const int &tableID)
{
  _switches.remove(tableID);

  for (auto it = _switches.begin(); it != _switches.end(); ++it) {
      int id = it.key();
      if (id > tableID)
        _switches[id - 1] = it.value();
    }

  int lastID = _switches.size() - 1;
  _switches.remove(lastID);

  emit layoutChanged();
}

void TableModel::insertValue(const Switch &value)
{
  _switches.insert(_switches.size(), value);
  emit layoutChanged();
}


