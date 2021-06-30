#include "vcs_tool.h"
#include "ui_vcs_tool.h"


vcsTool::vcsTool(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::vcsTool)
{
    ui->setupUi(this);
    QMenu *fileMenu =menuBar()->addMenu("&File");
    QAction *newAct = new QAction("&New", this);
    fileMenu->addAction(newAct);
}


vcsTool::~vcsTool()
{
    delete ui;
}

