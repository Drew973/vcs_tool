#include "sectionsModel.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


sectionsModel::sectionsModel(QObject *parent,QSqlDatabase db) : QSqlTableModel(parent)
{

}



bool sectionsModel::addSection(QVariant number,QVariant project,QVariant direction,QVariant job_no,QVariant date,QVariant client,QVariant contractor,QVariant label
                               ,QVariant surveyor,QVariant weather,QVariant start_lon,QVariant start_lat,QVariant end_lon,QVariant end_lat,QVariant length_surveyed)
{
     QSqlQuery q=QSqlQuery(database());
     qDebug() << q.prepare("insert into sections(number,project,direction,job_no,date,client,contractor,label,surveyor,weather,start_lon,start_lat,end_lon,end_lat,length_surveyed)"
     "values(:number,:project,:direction,:job_no,:date,:client,:contractor,:label,:surveyor,:weather,:start_lon,:start_lat,:end_lon,:end_lat,:length_surveyed)");

     q.bindValue(":number",number);
     q.bindValue(":project",project);
     q.bindValue(":direction",direction);
     q.bindValue(":job_no",job_no);
     q.bindValue(":date",date);
     q.bindValue(":client",client);
     q.bindValue(":contractor",contractor);
     q.bindValue(":label",label);
     q.bindValue(":surveyor",surveyor);
     q.bindValue(":weather",weather);
     q.bindValue(":start_lon",start_lon);
     q.bindValue(":start_lat",start_lat);
     q.bindValue(":end_lon",end_lon);
     q.bindValue(":end_lat",end_lat);
     q.bindValue(":length_surveyed",length_surveyed);


    if (q.exec())
    {
        return true;
    }
    else
    {
        qDebug() << "insert query failed:"<<q.lastError().databaseText();
        return false;
    }

}

