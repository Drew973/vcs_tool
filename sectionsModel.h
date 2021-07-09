#ifndef SECTIONSMODEL
#define SECTIONSMODEL

#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QVariant>

class sectionsModel : public QSqlTableModel
{
public:
    explicit sectionsModel(QObject *parent = nullptr,QSqlDatabase db = QSqlDatabase());

    bool addSection(QVariant number,QVariant project,QVariant direction,QVariant job_no,QVariant date,QVariant client,QVariant contractor,QVariant label
                    ,QVariant surveyor,QVariant weather,QVariant start_lon,QVariant start_lat,QVariant end_lon,QVariant end_lat,QVariant length_surveyed);
};

#endif // SECTIONSMODEL
