#ifndef INSERTABLEPROXYMODEL_H
#define INSERTABLEPROXYMODEL_H

#include <QIdentityProxyModel>
#include <QVariant>


class insertableProxyModel : public QIdentityProxyModel


{
public:
    insertableProxyModel();
    int rowCount();
    QVariant data(const QModelIndex &index, int role);
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
};







#endif // INSERTABLEPROXYMODEL_H
