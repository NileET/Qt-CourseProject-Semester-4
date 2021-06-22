#include "tablemodel.hpp"


TableModel::TableModel(QObject *parent) :
  QAbstractTableModel(parent)
{ }

int TableModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return _switches.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return 7;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (index.row() < 0 || index.row() >= _switches.size())
    return QVariant();

  switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
      {
        const Switch& sw = _switches.at(index.row());

        if (index.column() == 0)
            return sw.getManufacturer().c_str();
        if (index.column() == 1)
            return sw.getModelName().c_str();
        if (index.column() == 2) {
            auto speed = sw.getBaseSpeed();
            return QString("%1, %2").arg(speed.first).arg(speed.second);
          }
        if (index.column() == 3)
            return QString::number(sw.getPortCount());
        if (index.column() == 4)
            return sw.getHasPoE();
        if (index.column() == 5) {
            auto size = sw.getModelSize();
            return QString("%1x%2x%3").arg(size.__width).arg(size.__length).arg(size.__high);
          }
        if (index.column() == 6)
            return QString::number(sw.getPrice()) + " ₽";
        break;
      }
    default:
      return QVariant();
    }

  return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (index.isValid() && role == Qt::EditRole) {
      Switch& sw = _switches[index.row()];

      switch (index.column()) {
        case 0:
            sw.setManufacturer(value.toString().toStdString()); break;
        case 1:
            sw.setModelName(value.toString().toStdString()); break;
        case 2:
          {
            QRegExp rx1("^(\\d{1,5}\\,|\\d{1,5}\\ \\,|\\d{1,5}\\,\\ )\\d{1,5}$");
            QRegExp rx2("^\\d{1,5}\\ \\d{1,5}$");

            QString val = value.toString();
            QStringList speedList;
            if (rx1.indexIn(val) != -1)
              speedList = val.split(",");
            else if (rx2.indexIn(val) != -1)
              speedList = val.split(" ");
            else
              return false;

            std::pair speed = std::make_pair(speedList[0].toInt(), speedList[1].toInt());
            sw.setBaseSpeed(speed); break;
          }
        case 3:
            sw.setPortCount(value.toInt()); break;
        case 4:
            sw.setHasPoE(value.toBool()); break;
        case 5:
          {
            QRegExp rx1("^(\\d{1,4}x){2}\\d{1,4}$");
            QRegExp rx2("^(\\d{1,4}\\ ){2}\\d{1,4}$");

            QString val = value.toString();
            QStringList sizeList;
            if (rx1.indexIn(val) != -1)
                sizeList = val.split("x");
            else if (rx2.indexIn(val) != -1)
                sizeList = val.split(" ");
            else
              return false;

            double width  = sizeList[0].toDouble(),
                   length = sizeList[1].toDouble(),
                   high   = sizeList[2].toDouble();

            sw.setModelSize(Switch::Size{width, length, high});
            break;
          }
        case 6:
            sw.setPrice(value.toInt()); break;
        default:
          return false;
        }

      emit dataChanged(index, index);
      emit wasModified();

      return true;
    }

  return false;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
  if (index.isValid())
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable
                             | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
  return Qt::NoItemFlags | Qt::ItemIsDropEnabled;
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

bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
  Q_UNUSED(parent);
  beginInsertRows(QModelIndex(), row, row + count - 1);

  for (int i = 0; i < count; ++i) {
      _switches.insert(row, Switch());
    }

  endInsertRows();

  return true;
}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
  Q_UNUSED(parent);
  beginRemoveRows(QModelIndex(), row, row + count - 1);

  for (int i = 0; i < count; ++i) {
    _switches.removeAt(row);
  }

  endRemoveRows();

  return true;
}


void TableModel::clear()
{
  _switches.clear();
  emit layoutChanged();
}

void TableModel::insertValue(const Switch &value)
{
  _switches << value;
  emit layoutChanged();
}
