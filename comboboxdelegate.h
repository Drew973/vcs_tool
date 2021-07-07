#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H


#include <QStyledItemDelegate>
#include <QStringList>


class comboboxDelegate : public QStyledItemDelegate
{
public:
    explicit comboboxDelegate(QObject *parent = nullptr,QStringList items=QStringList(),QAbstractItemModel * model =nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const override;

    void setItems(QStringList items);

    void setModel(QAbstractItemModel * model);
    void setModelColumn(int visibleColumn);


    QStringList itemList = QStringList();//initialize to empty list
    QAbstractItemModel * mod =nullptr;
    int col=-1;

};

#endif // COMBOBOXDELEGATE_H
