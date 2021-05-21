#include "tablemodel.hpp"

TableModel::TableModel(QObject *parent) :
  QAbstractTableModel(parent), columns(7)
{ }

int TableModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return _switches.count();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return columns;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
      if (index.column() == 0)
          return _switches.at(index.row()).getManufacturer().c_str();
      if (index.column() == 1)
          return _switches.at(index.row()).getModelName().c_str();
      if (index.column() == 2) {
          auto speed = _switches.at(index.row()).getBaseSpeed();
          return QString("%1, %2").arg(speed.first).arg(speed.second);
        }
      if (index.column() == 3)
          return QString::number(_switches.at(index.row()).getPortCount());
      if (index.column() == 4)
          return _switches.at(index.row()).getHasPoE() ? tr("Yes") : tr("No");
      if (index.column() == 5) {
          auto size =_switches.at(index.row()).getModelSize();
          return QString("%1x%2x%3").arg(size.__width).arg(size.__length).arg(size.__high);
        }
      if (index.column() == 6)
          return QString::number(_switches.at(index.row()).getPrice()) + " ₽";
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
      auto sw =_switches.at(index.row());

      switch (index.column()) {
        case 0:
          sw.setManufacturer(value.toString().toStdString()); break;
        case 1:
          sw.setModelName(value.toString().toStdString()); break;
        case 2:
          {
            auto speedList = value.toStringList();
            std::pair speed = std::make_pair(speedList[0].toInt(), speedList[1].toInt());
            sw.setBaseSpeed(speed); break;
          }
        case 3:
          sw.setPortCount(value.toInt()); break;
        case 4:
          {
            QString strPoE = value.toString();
            bool PoE = strPoE == tr("Yes") ? true : false;
            sw.setHasPoE(PoE); break;
          }
        case 5:
          {
            QStringList listSize = value.toString().split("x");
            double width  = listSize[0].toDouble(),
                   length = listSize[1].toDouble(),
                   high   = listSize[2].toDouble();
            sw.setModelSize({width, length, high});
          }
        case 6:
          sw.setPrice(value.toInt()); break;
        }

      _switches.replace(index.row(), sw);
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
          return tr("Manufacturer");
        case 1:
          return tr("Model");
        case 2:
          return tr("Base baud rate");
        case 3:
          return tr("Number of ports");
        case 4:
          return tr("PoE support");
        case 5:
          return tr("Dimensions");
        case 6:
          return tr("Price");
        }
    }
  return QVariant();
}

void TableModel::insertValue(const Switch &value)
{
  _switches << value;
  emit layoutChanged();
}
