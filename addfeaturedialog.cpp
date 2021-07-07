#include "addfeaturedialog.h"
#include "ui_addfeaturedialog.h"

addFeatureDialog::addFeatureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addFeatureDialog)
{
    ui->setupUi(this);
}

addFeatureDialog::~addFeatureDialog()
{
    delete ui;
}
