

#ifndef VCSTOOL_H
#define VCSTOOL_H

#include <QMainWindow>
#include "comboboxdelegate.h"
#include "filewidgetdelegate.h"
#include "addfeaturedialog.h"
#include "sectionsModel.h"
#include "insertDialog.h"
#include "addfeaturedialog.h"

#include <QMainWindow>
#include <QObject>

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QString>




QT_BEGIN_NAMESPACE
namespace Ui { class vcsTool; }
QT_END_NAMESPACE


const QStringList defects = { "HRA", "TSSC", "HFSC", "I(G)","I(MH)", "J","Trench Failure","FT","SD(1)","SD(2)","PF","CZ(1)","CZ(2)","POT","LJ(O)","MJ","PJ","LOOPS","PA","CR(1)","CR(2)","TC(1)","TC(2)"};
const QStringList lanes =  { "CL1", "CL2", "CL3", "CL1&CL2","CL2&CL3", "CL1&CL2&CL3"};
const QStringList locations =  { "F", "L", "R", "N"};




class vcsTool : public QMainWindow
{
    Q_OBJECT

public:
    vcsTool(QWidget *parent = nullptr);
    ~vcsTool();

private:
    Ui::vcsTool *ui;
    QSqlDatabase db =QSqlDatabase();//test if connected with .isOpen(). test if set with .isValid().

    comboboxDelegate * laneDelegate = new comboboxDelegate(this,lanes);
    comboboxDelegate * defectDelegate = new comboboxDelegate(this,defects);
    comboboxDelegate * locationDelegate = new comboboxDelegate(this,locations);
    fileWidgetDelegate * photoDelegate = new fileWidgetDelegate(this,"Images (*.png *.bmp *.jpg)");

    sectionsModel * sectModel=nullptr;
    QSqlTableModel * featuresModel=nullptr;
    addFeatureDialog * afd =new addFeatureDialog(this,db,laneDelegate,defectDelegate,locationDelegate,photoDelegate);
 //   insertDialog * addSectionDialog = new addSectionDialog(this);


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


signals:
    void databaseSet(QSqlDatabase database);

};
#endif // VCSTOOL_H




