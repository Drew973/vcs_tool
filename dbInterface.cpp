#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>


bool createNewDb(QSqlDatabase db)
    {

    if (not db.isOpen())
        {
        if (not db.open())
            {
            qDebug() << "could not open database:";
            return false;
            }
        }

    QString initSectionsQuery = "create table if not exists sections(\
            number int\
            ,project text\
            ,direction text\
            ,job_no text\
            ,date text\
            ,client text\
            ,contractor text\
            ,label text primary key not null\
            ,surveyor text\
            ,weather text\
            ,start_lon float\
            ,start_lat float\
            ,end_lon float\
            ,end_lat float\
            ,length_surveyed float\
            )";

//section_label is also unique and could be pk

    QSqlQuery q(db);

    if( not q.exec(initSectionsQuery))
        {
        qDebug() << "Failed query:" << initSectionsQuery <<" .error was:"<<q.lastError().databaseText();
        return false;
        }


    QString initFeaturesQuery = "create table features(\
        pk INTEGER PRIMARY KEY not null--huge bug in sqlite. any/all primary key can be null. Should autoincrement\
        ,lane text\
        ,s_ch float\
        ,e_ch float\
        ,width float\
        ,feature text\
        ,location text\
        ,photo text\
        ,section_label text\
        ,photo_number int\
        ,foreign key(section_label) references sections(label) on update cascade)";

    if( not q.exec(initFeaturesQuery))
        {
        qDebug() << "Failed query:" << initFeaturesQuery <<" .error was:"<<q.lastError().databaseText();
        return false;
        }


        return true;
    }




bool addFeature(QSqlDatabase db,QVariant sec,QVariant lane,QVariant s_ch,QVariant e_ch,QVariant width,QVariant feature,QVariant location,QVariant photo)
{
     QSqlQuery q=QSqlQuery(db);
     qDebug() << q.prepare("insert into features(section_label,lane,s_ch,e_ch,width,feature,location,photo)"
     "values(:sec,:lane,:s_ch,:e_ch,:width,:feature,:location,:photo)");

     q.bindValue(":sec",sec);
     q.bindValue(":lane",lane);
     q.bindValue(":s_ch",s_ch);
     q.bindValue(":e_ch",e_ch);
     q.bindValue(":width",width);
     q.bindValue(":feature",feature);
     q.bindValue(":location",location);
     q.bindValue(":photo",photo);


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
