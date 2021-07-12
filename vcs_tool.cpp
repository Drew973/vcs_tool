#include "vcs_tool.h"
#include "ui_vcs_tool.h"
#include "dbInterface.h"
#include "addfeaturedialog.h"

#include "sectionsModel.h"
#include "recordModel.h"
//#include "insertDialog.h"


#include <QFileDialog>
#include <QString>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDebug>
#include <QStringList>
#include <algorithm>
#include <QObject>
#include <QAction>
#include <QMainWindow>


#include <QStyledItemDelegate>


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

    QAction *addFeatAct = featuresMenu->addAction("&Add Feature");
    connect(addFeatAct, &QAction::triggered, this, &vcsTool::addFeature);

    QAction *dropSelectedAct = featuresMenu->addAction("&Drop Selected Features");
    connect(dropSelectedAct, &QAction::triggered, this, &vcsTool::dropSelectedFeatures);

    QMenu *sectionsMenu =menuBar()->addMenu("&Sections");
    QAction *addSectionAct = sectionsMenu->addAction("&Add Section");
    //connect(dropSelectedAct, &QAction::triggered, this, &vcsTool::dropSelectedFeatures);

    connect(ui->secBox, &QComboBox::currentTextChanged, afd, &addFeatureDialog::setSec);
    afd->setSec(ui->secBox->currentText());

    connect(this, &vcsTool::databaseSet, afd, &addFeatureDialog::setDatabase);

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
        connectSectModel();
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

          connectSectModel();
          connectFeaturesModel();

        }
    }


//called on secBox.currentIndexChanged
    void vcsTool::setSec(int index)
    {
        if (featuresModel and sectModel)
        {
            int labelField=sectModel->fieldIndex("label");
            QString filt = QString("section_label='%1'").arg(sectModel->index(index,labelField).data(Qt::DisplayRole).toString());
            featuresModel->setFilter(filt);
        }
    }



void vcsTool::connectSectModel()//warning if table doesn't exist
{
    //sections
    sectModel = new sectionsModel(this,db);
    sectModel->setTable("sections");
    ui->sectionsView->setModel(sectModel);

    ui->secBox->setModel(sectModel);
    ui->secBox->setModelColumn(sectModel->fieldIndex("label"));

    sectModel->select();


    recordModel* r =new recordModel(this,sectModel->record());
    ui->insertSectionView->setModel(r);

}



void vcsTool::connectFeaturesModel()//warning if table doesn't exist
{
    featuresModel = new QSqlTableModel(this,db);
    featuresModel->setTable("features");//
    connect(afd,&QDialog::accepted,featuresModel,&QSqlTableModel::select);
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
        emit databaseSet(dataBase);

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
           afd->show();
       }

       else
       {
           QMessageBox msgBox;
           msgBox.setText("not connected to database.");
           msgBox.exec();
       }
    }



    void vcsTool::addSection()
    {
       qDebug() << "Add Section";
       if (db.isOpen())
       {
          // addFeatureDialog->show();
       }

       else
       {
           QMessageBox msgBox;
           msgBox.setText("not connected to database.");
           msgBox.exec();
       }
    }



void vcsTool::dropSelectedFeatures()
    {
        QItemSelectionModel *m = ui->featuresView->selectionModel();

        if (m and featuresModel)
        {
            QModelIndexList indices = m->selectedRows();
            for (int i=indices.count()-1; i>=0; --i)
            {
                QModelIndex index = indices.at(i);
                featuresModel->removeRow(index.row());
            }

         featuresModel->select();
         }

    }


