#include "vcs_tool.h"
#include "ui_vcs_tool.h"
#include "dbInterface.h"
#include "addfeaturedialog.h"

#include "sectionsModel.h"
#include "recordModel.h"
//#include "insertDialog.h"
#include "blacklistValidator.h"

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
#include <QStringList>

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

    connect(openAct, &QAction::triggered, this, &vcsTool::onOpenAction);
    connect(newAct, &QAction::triggered, this, &vcsTool::onNewAction);


    //sections menu
    QMenu *sectionsMenu =menuBar()->addMenu("&Sections");
    QAction *addSectionAct = sectionsMenu->addAction("&Add Section");
    connect(addSectionAct, &QAction::triggered, this, &vcsTool::addSection);

    QMenu *featuresMenu =menuBar()->addMenu("&Features");

    QAction *addFeatAct = featuresMenu->addAction("&Add Feature");
    connect(addFeatAct, &QAction::triggered, this, &vcsTool::addFeature);

    QAction *dropSelectedAct = featuresMenu->addAction("&Drop Selected Features");
    connect(dropSelectedAct, &QAction::triggered, this, &vcsTool::dropSelectedFeatures);



    connect(ui->secBox, &QComboBox::currentTextChanged, afd, &addFeatureDialog::setSec);
    afd->setSec(ui->secBox->currentText());

    connect(this, &vcsTool::databaseSet, afd, &addFeatureDialog::setDatabase);


    addSectionDialog->setModal(true);

}


vcsTool::~vcsTool()
{
    delete ui;
}



void vcsTool::onOpenAction()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Sqlite Database"), QString(),"sqlite File (*.db)");

    if (not fileName.isEmpty() )
    {
        QSqlDatabase dataBase = QSqlDatabase::addDatabase("QSQLITE");
        dataBase.setDatabaseName(fileName);
        setDataBase(dataBase);
        connectSectModel();
        connectFeaturesModel();
    }
}




//void vcsTool::newDb()
void vcsTool::onNewAction()
    {
    QString fileName = QFileDialog::getSaveFileName(this,tr("Create new .db file"), QString(),"sqlite File (*.db)");
    if (not fileName.isEmpty() )
        {
          QSqlDatabase dataBase = QSqlDatabase::addDatabase("QSQLITE");
          dataBase.setDatabaseName(fileName);

          setDataBase(dataBase);//opens database

          setupDatabase(dataBase);
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

    if(addSectionDialog){addSectionDialog->setRecord(sectModel->record());}
  //  if(addSectionDialog){addSectionDialog->setModel(sectModel);}


   // ui->sectionsView->setItemDelegateForColumn(featuresModel->fieldIndex("lane"), laneDelegate);
    //blacklistValidator * v = new blacklistValidator(this,sectModel,sectModel->fieldIndex("label"));
  //  ui->blacklistTest->setValidator(v);
   // secDelegate->setIndex(sectModel.index(0,sectModel->fieldIndex("label")));
    ui->sectionsView->setItemDelegateForColumn(sectModel->fieldIndex("label"),secDelegate);
    ui->sectionsView->resizeColumnsToContents();

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
          addSectionDialog->show();
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


