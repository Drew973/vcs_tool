#include "addfeaturedialog.h"
#include "ui_addfeaturedialog.h"
#include "vcs_tool.h"
#include "dbInterface.h"


#include <QAbstractItemDelegate>
#include <QList>
#include <QStandardItem>

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>



addFeatureDialog::addFeatureDialog(QWidget *parent,QSqlDatabase db,QAbstractItemDelegate * laneDelegate,QAbstractItemDelegate * featureDelegate,QAbstractItemDelegate * locationDelegate,QAbstractItemDelegate * photoDelegate) :
    QDialog(parent),
    ui(new Ui::addFeatureDialog)
{
    ui->setupUi(this);
    setDatabase(db);

    if(laneDelegate){setDelegate(0,laneDelegate);}
    if(featureDelegate){setDelegate(4,featureDelegate);}
    if(locationDelegate){setDelegate(5,locationDelegate);}
    if(locationDelegate){setDelegate(6,photoDelegate);}

   // model.appendRow(QStandardItem("CL1"))
    model->setHorizontalHeaderLabels({"Lane","s_ch","e_ch","width","feature","location","photo"});

    ui->view->setModel(model);
}


addFeatureDialog::~addFeatureDialog()
{
    delete ui;
}



void addFeatureDialog::setDelegate(int column,QAbstractItemDelegate * delegate)
{
    ui->view->setItemDelegateForColumn(column,delegate);
}

void addFeatureDialog::setSec(QString label)
{
    sec=label;
}

void addFeatureDialog::setDatabase(QSqlDatabase database)
{
    db=database;
}


void addFeatureDialog::add()
{
    //r bool=addFeature()
    addFeature(db,QVariant(sec),d(0),d(1),d(2),d(3),d(4),d(5),d(6));

    accept();
}

//gets data at column i
QVariant addFeatureDialog::d(int i)
{
    QStandardItem * item=model->item(0,i);
    if(item)
    {
        return item->data(Qt::DisplayRole);
    }
    else
    {
        return QVariant();
    }
}

