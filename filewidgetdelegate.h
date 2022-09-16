#ifndef FILEWIDGETDELEGATE_H
#define FILEWIDGETDELEGATE_H



#include "filewidget.h"
#include <QStyledItemDelegate>
#include <QString>


class fileWidgetDelegate : public QStyledItemDelegate
{
public:
    explicit fileWidgetDelegate(QObject *parent = nullptr,QString filter="");

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const override;


     // setTextEditable(false);
     // setFilter("Images (*.png *.bmp *.jpg)");


    void setTextEditable(bool editable);
    void setFilter(QString filt);


    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,const QModelIndex &/* index */) const override;


    bool textEditable=true;
    QString filter="";



};

#endif // FILEWIDGETDELEGATE_H
