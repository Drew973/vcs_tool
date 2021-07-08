#include "vcs_tool.h"
#include "ui_vcs_tool.h"
#include "dbInterface.h"
#include "addfeaturedialog.h"

#include <QFileDialog>
#include <QString>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDebug>
#include <QStringList>


#include "addfeaturedialog.h"


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
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open .db file"), QString(),"sqlite File (*.db)");

    if (not fileName.isEmpty() )
    {
        QSqlDatabase dataBase = QSqlDatabase::addDatabase("QSQLITE");
        dataBase.setDatabaseName(fileName);
        setDataBase(dataBase);
        connectSectionsModel();
        connectFeaturesModel();
    }
}




void vcsTool::newDb()
    {
    QString fileName = QFileDialog::getSaveFileName(this,tr("Create new .db file"), QString(),"sqlite File (*.db)");
    if (not fileName.isEmpty() )
        {
          QSqlDatabase dataBase = QSqlDatabase::addDatabase("QSQLITE");
          dataBase.setDatabaseName(fileName);

          setDataBase(dataBase);

          bool r = createNewDb(db);

          if(not r)
              {
                  QMessageBox msgBox;
                  msgBox.setText("Error Creating database.");
                  msgBox.exec();
                 // QMessageBox.Warning
              }

          connectSectionsModel();
          connectFeaturesModel();

        }
    }


//called on secBox.currentIndexChanged
    void vcsTool::setSec(int index)
    {
        if (featuresModel and sectionsModel)
        {
            int labelField=sectionsModel->fieldIndex("label");
            QString filt = QString("section_label='%1'").arg(sectionsModel->index(index,labelField).data(Qt::DisplayRole).toString());
            featuresModel->setFilter(filt);
        }
    }



void vcsTool::connectSectionsModel()//warning if table doesn't exist
{
    //sections
    sectionsModel = new QSqlTableModel(this,db);
    sectionsModel->setTable("sections");
    ui->sectionsView->setModel(sectionsModel);

    ui->secBox->setModel(sectionsModel);
    ui->secBox->setModelColumn(sectionsModel->fieldIndex("label"));

    sectionsModel->select();//this will trigger setSec? before featuresModel set?
}



void vcsTool::connectFeaturesModel()//warning if table doesn't exist
{
    featuresModel = new QSqlTableModel(this,db);
    featuresModel->setTable("features");//
    featuresModel->select();
    ui->featuresView->setModel(featuresModel);

    //hidden columns
    ui->featuresView->setColumnHidden(featuresModel->fieldIndex("section_label"),true);
    ui->featuresView->setColumnHidden(featuresModel->fieldIndex("pk"),true);

    //delegates
    ui->featuresView->setItemDelegateForColumn(featuresModel->fieldIndex("lane"), laneDelegate);
    ui->featuresView->setItemDelegateForColumn(featuresModel->fieldIndex("feature"), defectDelegate);
    ui->featuresView->setItemDelegateForColumn(featuresModel->fieldIndex("location"), locationDelegate);
    ui->featuresView->setItemDelegateForColumn(featuresModel->fieldIndex("photo"), photoDelegate);
}


void vcsTool::setDataBase(QSqlDatabase dataBase)//open dataBase. set db to this.
    {
        db = dataBase;

        if(not db.isOpen()){db.open();}
        if (db.isOpen())
        {
            this->setWindowTitle(db.databaseName()+" - VCS tool");
        }
        else
        {
            this->setWindowTitle("not connected - VCS tool");
        }
    }

    void vcsTool::addFeature()
    {
       qDebug() << "Add Feature";
       if (db.isOpen())
       {
           addFeatureDialog * afd =new addFeatureDialog(this,db,laneDelegate,defectDelegate,locationDelegate,photoDelegate);
           connect(ui->secBox, &QComboBox::currentTextChanged, afd, &addFeatureDialog::setSec);

           afd->show();
           if (featuresModel){featuresModel->select();}
       }
       else
       {
           QMessageBox msgBox;
           msgBox.setText("not connected to database.");
           msgBox.exec();
       }

    }



