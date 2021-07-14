#ifndef UNIQUETEXTDELEGATE_H
#define UNIQUETEXTDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>



/*
 *delegate that creates QlineEdit with validator that does not allow setting to item in same column.
*/


class uniqueTextDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit uniqueTextDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const override;

};


















#endif // UNIQUETEXTDELEGATE_H
