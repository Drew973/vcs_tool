#include "addfeaturedialog.h"
#include "ui_addfeaturedialog.h"
#include "vcs_tool.h"

#include <QAbstractItemDelegate>
#include <QList>
#include <QStandardItem>



addFeatureDialog::addFeatureDialog(QWidget *parent,QAbstractItemDelegate * laneDelegate,QAbstractItemDelegate * featureDelegate,QAbstractItemDelegate * locationDelegate,QAbstractItemDelegate * photoDelegate) :
    QDialog(parent),
    ui(new Ui::addFeatureDialog)
{
    ui->setupUi(this);
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
