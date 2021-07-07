#include "addfeaturesdialog.h"
#include "ui_addfeaturesdialog.h"
#include "vcs_tool.h"




addFeaturesDialog::addFeaturesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addFeaturesDialog)
{
    ui->setupUi(this);
}

addFeaturesDialog::~addFeaturesDialog()
{
    delete ui;
}
