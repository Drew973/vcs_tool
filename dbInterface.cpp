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
            number int primary key\
            ,project text\
            ,direction text\
            ,job_no text\
            ,date text\
            ,client text\
            ,contractor text\
            ,label text\
            ,surveyor text\
            ,weather text\
            ,start_lon float\
            ,start_lat float\
            ,end_lon float\
            ,end_lat float\
            ,length_surveyed float\
            ,photo_folder text)";


    QSqlQuery q(db);

    if( not q.exec(initSectionsQuery))
        {
        qDebug() << "Failed query:" << initSectionsQuery <<" .error was:"<<q.lastError().databaseText();
        return false;
        }


    QString initFeaturesQuery = "create table features(\
        lane text\
        ,s_ch float\
        ,e_ch float\
        ,width float\
        ,feature text\
        ,location text\
        ,photo text\
        ,section_number int\
        ,photo_number int\
        ,foreign key(section_number) references sections(number))";

    if( not q.exec(initFeaturesQuery))
        {
        qDebug() << "Failed query:" << initFeaturesQuery <<" .error was:"<<q.lastError().databaseText();
        return false;
        }


        return true;
    }
