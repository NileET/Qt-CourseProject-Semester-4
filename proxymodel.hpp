#ifndef PROXYMODEL_HPP
#define PROXYMODEL_HPP

#include <QSortFilterProxyModel>

class ProxyModel : public QSortFilterProxyModel
{
  Q_OBJECT
public:
  ProxyModel(QObject* parent = nullptr);

protected:
  bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const;
};

#endif // PROXYMODEL_HPP
