#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#endif // DBINTERFACE_H
#include <QSqlDatabase>

//move this to model subclasses
bool createNewDb(QSqlDatabase db);


bool addFeature(QSqlDatabase db,QVariant sec,QVariant lane,QVariant s_ch,QVariant e_ch,QVariant width,QVariant feature,QVariant location,QVariant photo);


