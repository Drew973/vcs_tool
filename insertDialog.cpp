#include "insertDialog.h"

//#include "vcs_tool.h"
//#include "dbInterface.h"
#include "recordModel.h"


#include <QAbstractItemDelegate>
#include <QList>
#include <QStandardItem>

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlTableModel>


//if model and record given set them. if model given and record empty sets record to model.record()
insertDialog::insertDialog(QWidget *parent,QSqlRecord record,QSqlTableModel * model)
{
    setModel(model);
    if (record.isEmpty() and model){setRecord(model->record());}
}


insertDialog::~insertDialog()
{
}


//void insertDialog::setDelegate(int column,QAbstractItemDelegate * delegate)
//{
    //ui->view->setItemDelegateForColumn(column,delegate);
//}

void insertDialog::setModel(QSqlTableModel * model)
{
    tableMod = model;
}



void insertDialog::insert()//try to insert record
{
//    if(tableMod){tableMod->insertRecord(-1,recMod->record());}
   // emit fin(recMod->record());
}


void insertDialog::setRecord(QSqlRecord record)
{
    recMod->setRecord(record);
}
