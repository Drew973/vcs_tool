#include "insertableproxymodel.h"
#include <QVariant>


insertableProxyModel::insertableProxyModel()
{

}





int insertableProxyModel::rowCount()
{
   return QIdentityProxyModel::rowCount()+1;
}




QVariant insertableProxyModel::data(const QModelIndex &index, int role)
{
  if (index.row()<rowCount())
      {
      return QIdentityProxyModel::data(index, role);
      }
  else
      {
      return QIdentityProxyModel::data(index.siblingAtRow(index.row()-1), role);
      }

}




bool insertableProxyModel::setData(const QModelIndex &index, const QVariant &value, int role) {

    if (index.row() == rowCount()) {
        return true;//not yet imlemented will do the insert
    }
    else
        return QIdentityProxyModel::setData (index, value, role);
    }
