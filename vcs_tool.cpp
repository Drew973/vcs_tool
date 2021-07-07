#include "vcs_tool.h"
#include "ui_vcs_tool.h"
#include "dbInterface.h"
#include "comboboxdelegate.h"

#include <QFileDialog>
#include <QString>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDebug>


vcsTool::vcsTool(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::vcsTool)
{
    ui->setupUi(this);
    //qt creator doesn't seem to have way to do this in ui

    //fileMenu
    QMenu *fileMenu =menuBar()->addMenu("&File");
    QAction *newAct = new QAction("&New", this);
    fileMenu->addAction(newAct);
    QAction * openAct = new QAction("&Open", this);
    fileMenu->addAction(openAct);

    connect(openAct, &QAction::triggered, this, &vcsTool::openDb);
    connect(newAct, &QAction::triggered, this, &vcsTool::newDb);

    QMenu *featuresMenu =menuBar()->addMenu("&Features");
    QAction *addFeatAct = new QAction("&Add Feature", this);
    featuresMenu->addAction(addFeatAct);
    connect(addFeatAct, &QAction::triggered, this, &vcsTool::addFeature);


}


vcsTool::~vcsTool()
{
    delete ui;
}



void vcsTool::openDb()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open .db file"), QString(),"sqlite Files (*.db)");
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);
    connectToDb(db);
}


bool vcsTool::connectToDb(QSqlDatabase db)
    {
    this->setWindowTitle("not connected - VCS tool");

    if (not db.isOpen())
        {
         if (not db.open())
            {
             qDebug() << "database failed to open:";
             return false;
            }
        }



        //features
        featuresModel = new QSqlTableModel(this,db);
        featuresModel->setTable("features");//
        featuresModel->select();
        ui->featuresView->setModel(featuresModel);
        ui->featuresView->setColumnHidden(featuresModel->fieldIndex("section_label"),true);
        ui->featuresView->setColumnHidden(featuresModel->fieldIndex("pk"),true);

        //setting up delegates for features view
        comboboxDelegate * laneDelegate = new comboboxDelegate(ui->featuresView);
        laneDelegate->setItems({ "CL1", "CL2", "CL3", "CL1&CL2","CL2&CL3", "CL1&CL2&CL3"});
        ui->featuresView->setItemDelegateForColumn(featuresModel->fieldIndex("lane"), laneDelegate);


        comboboxDelegate * defectDelegate = new comboboxDelegate(ui->featuresView);
        defectDelegate->setItems({ "HRA", "TSSC", "HFSC", "I(G)","I(MH)", "J","Trench Failure","FT","SD(1)","SD(2)","PF","CZ(1)","CZ(2)","POT","LJ(O)","MJ","PJ","LOOPS","PA","CR(1)","CR(2)","TC(1)","TC(2)"});
        ui->featuresView->setItemDelegateForColumn(featuresModel->fieldIndex("feature"), defectDelegate);


        //sections
        sectionsModel = new QSqlTableModel(this,db);
        sectionsModel->setTable("sections");
        ui->sectionsView->setModel(sectionsModel);

        ui->secBox->setModel(sectionsModel);
        ui->secBox->setModelColumn(sectionsModel->fieldIndex("label"));

        sectionsModel->select();//this will trigger setSec? before featuresModel set?


        this->setWindowTitle(db.databaseName()+" - VCS tool");
        return true;
    }




void vcsTool::newDb()
    {
    QString fileName = QFileDialog::getSaveFileName(this,tr("Create new .db file"), QString(),"sqlite Files (*.db)");
    if (not fileName.isEmpty() )
        {
          QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
          db.setDatabaseName(fileName);

          bool r = createNewDb(db);

          if (r)
              {
                this->connectToDb(db);
              }
          else
              {
                  QMessageBox msgBox;
                  msgBox.setText("Error Creating database.");
                  msgBox.exec();
                 // QMessageBox.Warning
              }
        }
    }


//called on secBox.currentIndexChanged
    void vcsTool::setSec(int index)
    {
        QString filt = QString("section_label='%1'").arg(sectionsModel->index(index,7).data(Qt::DisplayRole).toString());
        //qDebug() << "filt:" << filt;
        this->featuresModel->setFilter(filt);
    }



    bool vcsTool::addFeature()
    {
       qDebug() << "Add Feature";
       return true;
    }



