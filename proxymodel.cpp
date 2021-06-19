#include "proxymodel.hpp"


ProxyModel::ProxyModel(QObject *parent) :
  QSortFilterProxyModel(parent)
{ }

bool ProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
  QString leftString = sourceModel()->data(source_left).toString();
  QString rightString = sourceModel()->data(source_right).toString();

  switch (source_left.column()) {
    // Сортировка по скорости
    case 2:
      {
        QStringList leftList = leftString.split(", ");
        QStringList rightList = rightString.split(", ");
        return std::make_tuple(leftList[0].toInt(), leftList[1].toInt()) <
            std::make_tuple(rightList[0].toInt(), rightList[1].toInt());
      }
    // Сортировка по количеству портов
    case 3:
      return leftString.toInt() < rightString.toInt();
    // Сортировка по по размеру
    case 5:
      {
        QStringList leftList = leftString.split("x");
        QStringList rightList = rightString.split("x");
        return std::make_tuple(leftList[0].toDouble(), leftList[1].toDouble(), leftList[2].toDouble()) <
            std::make_tuple(rightList[0].toDouble(), rightList[1].toDouble(), rightList[2].toDouble());
      }
    // Сортировка по цене
    case 6:
      return leftString.split(" ")[0].toInt() < rightString.split(" ")[0].toInt();
    // Лекскикографическая сортировка для остальных столбцов
    default:
      return QString::localeAwareCompare(leftString, rightString) < 0;
    }
}
