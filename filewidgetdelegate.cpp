#include "filewidgetdelegate.h"
#include "filewidget.h"


fileWidgetDelegate::fileWidgetDelegate(QObject *parent,QString filter) : QStyledItemDelegate(parent)
{
    if (not filter.isEmpty()){setFilter(filter);}
}




QWidget *fileWidgetDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const
{
     fileWidget * w = new fileWidget(parent);
     w->setTextEditable(textEditable);
     w->setFilter(filter);
     return w;
}


//see https://doc.qt.io/qt-5/qtwidgets-itemviews-spinboxdelegate-example.html
void fileWidgetDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    fileWidget * fw = static_cast<fileWidget*>(editor);//editor to fileWidget *
    fw->setText(index.data().toString());
}


void fileWidgetDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
{
    fileWidget * fw = static_cast<fileWidget*>(editor);//editor to fileWidget *
    model->setData(index, fw->currentFile(), Qt::EditRole);
}



void fileWidgetDelegate::setTextEditable(bool editable)
{
    textEditable=editable;
}



void fileWidgetDelegate::setFilter(QString filt)
{
    filter=filt;
}
