#ifndef FILEWIDGETDELEGATE_H
#define FILEWIDGETDELEGATE_H



#include "filewidget.h"
#include <QStyledItemDelegate>



class fileWidgetDelegate : public QStyledItemDelegate
{
public:
    explicit fileWidgetDelegate(QObject *parent = nullptr);
};

#endif // FILEWIDGETDELEGATE_H
