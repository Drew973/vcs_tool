#include "filewidget.h"

#include <QString>
#include <QPushButton>
#include <QLineEdit>
#include<QHBoxLayout>
#include <QFileDialog>


fileWidget::fileWidget(QWidget *parent) : QWidget(parent)
{
    setLayout(new QHBoxLayout(this));

    edit = new QLineEdit(this);
    layout()->addWidget(edit);

    browseButton = new QPushButton("&...",this);
    browseButton->setToolTip("Browse...");
    layout()->addWidget(browseButton);

    connect(browseButton, &QPushButton::pressed, this,&fileWidget::browse);

  //  setTextEditable(false);
   // setFilter("Images (*.png *.bmp *.jpg)");
}



QString fileWidget::currentFile()
{
    return edit->text();
}


void fileWidget::setTextEditable(bool editable)
{
    edit->setReadOnly(not editable);
}



void fileWidget::setFilter(QString filter)
    {
    filt = filter;
    }


void fileWidget::browse()
    {
        QString f = QFileDialog::getOpenFileName(this,tr("Select File"), QString(), filt);
        if (not f.isEmpty())
        {
            edit->setText(f);
        }
    }


void fileWidget::setText(QString text)
{
    edit->setText(text);
}


