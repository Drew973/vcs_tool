#include "comboboxdelegate.h"


#include <QComboBox>


comboboxDelegate::comboboxDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
}



QWidget *comboboxDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const
    {
        QComboBox * b = new QComboBox(parent);

        if (not itemList.isEmpty())
        {
            b->addItems(itemList);
        }


        if(mod)
        {
            b->setModel(mod);
            if (col>=0){b->setModelColumn(col);}
        }

        return b;


    }


void comboboxDelegate::setItems(QStringList items)
    {
    itemList = items;
    }



void comboboxDelegate::setModel(QAbstractItemModel * model)
    {
    mod = model;
    }


void comboboxDelegate::setModelColumn(int visibleColumn)
    {
    col = visibleColumn;
    }
