#ifndef VCSTOOL_H
#define VCSTOOL_H

#include "comboboxdelegate.h"
#include "filewidgetdelegate.h"

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QString>

const QStringList defects = { "HRA", "TSSC", "HFSC", "I(G)","I(MH)", "J","Trench Failure","FT","SD(1)","SD(2)","PF","CZ(1)","CZ(2)","POT","LJ(O)","MJ","PJ","LOOPS","PA","CR(1)","CR(2)","TC(1)","TC(2)"};
const QStringList lanes =  { "CL1", "CL2", "CL3", "CL1&CL2","CL2&CL3", "CL1&CL2&CL3"};
const QStringList locations =  { "F", "L", "R", "N"};

QT_BEGIN_NAMESPACE
namespace Ui { class vcsTool; }
QT_END_NAMESPACE

class vcsTool : public QMainWindow
{
    Q_OBJECT

    public:
        vcsTool(QWidget *parent = nullptr);
        ~vcsTool();
        QSqlTableModel * sectionsModel;
        QSqlTableModel * featuresModel;
     //   QSqlDatabase db;
        int testInt;

        comboboxDelegate * laneDelegate = new comboboxDelegate(this,lanes);
        comboboxDelegate * defectDelegate = new comboboxDelegate(this,defects);
        comboboxDelegate * locationDelegate = new comboboxDelegate(this,locations);
        fileWidgetDelegate * photoDelegate = new fileWidgetDelegate(this,"Images (*.png *.bmp *.jpg)");

    public slots:
        void openDb();
        void newDb();
        bool connectToDb(QSqlDatabase db);
        void setSec(int index);
        bool addFeature();

    private:
        Ui::vcsTool *ui;
};
#endif // VCSTOOL_H
