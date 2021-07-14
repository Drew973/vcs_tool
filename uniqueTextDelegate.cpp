#include "uniqueTextDelegate.h"
#include "blacklistValidator.h"
#include <QLineEdit.h>

uniqueTextDelegate::uniqueTextDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}


QWidget *uniqueTextDelegate::createEditor(QWidget* parent,const QStyleOptionViewItem &option,const QModelIndex &index) const
{
     QLineEdit* edit = new QLineEdit(parent);
     //blacklistValidator* v = new blacklistValidator(parent,mod,index.column());
   //  edit->setValidator(v);
     edit->setValidator( new blacklistValidator(parent,index));

     return edit;
}
