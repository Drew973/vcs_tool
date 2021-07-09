#ifndef VCSTOOL_H
#define VCSTOOL_H

#include "comboboxdelegate.h"
#include "filewidgetdelegate.h"
#include "addfeaturedialog.h"
#include "sectionsModel.h"
#include "insertDialog.h"

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QString>
#include <QObject>


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
        sectionsModel * sectModel=nullptr;
        QSqlTableModel * featuresModel=nullptr;

        comboboxDelegate * laneDelegate = new comboboxDelegate(this,lanes);
        comboboxDelegate * defectDelegate = new comboboxDelegate(this,defects);
        comboboxDelegate * locationDelegate = new comboboxDelegate(this,locations);
        fileWidgetDelegate * photoDelegate = new fileWidgetDelegate(this,"Images (*.png *.bmp *.jpg)");


        addFeatureDialog * afd =new addFeatureDialog(this,db,laneDelegate,defectDelegate,locationDelegate,photoDelegate);


    signals:
        void databaseSet(QSqlDatabase database);

    public slots:
        void openDb();//handles open database... action.
        void newDb();//handles new database... action. create new.db then connect models to it.


        void setDataBase(QSqlDatabase dataBase);//open dataBase. set db to this.

        void connectSectModel();//warning if table doesn't exist
        void connectFeaturesModel();//warning if table doesn't exist

        void setSec(int index);
        void addFeature();//show addFeatureDialog
        void dropSelectedFeatures();
        void addSection();

    private:
        Ui::vcsTool *ui;
        QSqlDatabase db =QSqlDatabase();//test if connected with .isOpen(). test if set with .isValid().
        insertDialog addSectionDialog = insertDialog();

};
#endif // VCSTOOL_H


/*
QSqlQuery requires QSqlDatabase
 */

