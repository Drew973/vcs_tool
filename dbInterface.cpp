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
            section_number int primary key not null\
            ,project text\
            ,direction text\
            ,job_no text\
            ,date text\
            ,client text\
            ,contractor text\
            ,label text unique not null\
            ,surveyor text\
            ,weather text\
            ,start_lon float\
            ,start_lat float\
            ,end_lon float\
            ,end_lat float\
            ,length_surveyed float\
            ,photo_folder text)";

//section_label is also unique and could be pk

    QSqlQuery q(db);

    if( not q.exec(initSectionsQuery))
        {
        qDebug() << "Failed query:" << initSectionsQuery <<" .error was:"<<q.lastError().databaseText();
        return false;
        }


    QString initFeaturesQuery = "create table features(\
        pk INTEGER PRIMARY KEY not null--huge bug in sqlite. primary key can all be null. Should autoincrement\
        ,lane text\
        ,s_ch float\
        ,e_ch float\
        ,width float\
        ,feature text\
        ,location text\
        ,photo text\
        ,section_label text\
        ,photo_number int\
        ,foreign key(section_label) references sections(label))";

    if( not q.exec(initFeaturesQuery))
        {
        qDebug() << "Failed query:" << initFeaturesQuery <<" .error was:"<<q.lastError().databaseText();
        return false;
        }


        return true;
    }
