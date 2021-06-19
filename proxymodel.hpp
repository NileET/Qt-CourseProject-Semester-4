#ifndef PROXYMODEL_HPP
#define PROXYMODEL_HPP

#include <QSortFilterProxyModel>


class ProxyModel : public QSortFilterProxyModel
{
  Q_OBJECT
public:
  /**
   * @brief ProxyModel - конструктор класса
   */
  ProxyModel(QObject* parent = nullptr);

protected:
  /**
   * @brief lessThan - переопределенный метод для задания правил сортировки, сравнивая два параметра
   * @param source_left - первый сравниваемый параметр
   * @param source_right - первый сравниваемый параметр
   * @return Если первое значение больше второго, то возвращает true, в противном случае - false
   */
  bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;
};

#endif // PROXYMODEL_HPP
