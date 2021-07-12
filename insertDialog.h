#ifndef INSERTDIALOG_H
#define INSERTDIALOG_H



#include "recordModel.h"

#include <QDialog>
#include <QStandardItemModel>
#include <QAbstractItemDelegate>
#include <QSqlDatabase>
#include <QVariant>
#include<QTableView>
#include <QSqlTableModel>

/*
dialog to edit QSqlRecord. on clicking ok tries to insert record into model(if set) then emits fin signal containing record
 *
 *
*/

namespace Ui {
class insertDialog;
}

class insertDialog : public QDialog
{
    Q_OBJECT

public:
    insertDialog(QWidget *parent=nullptr,QSqlRecord record=QSqlRecord(),QSqlTableModel* model=nullptr);
    ~insertDialog();


public slots:
    void insert();//try to insert record
    void setRecord(QSqlRecord);
    void setModel(QSqlTableModel* model);

signals:
    void fin (QSqlRecord);

private:
    QTableView* view = new QTableView(this);
    QSqlTableModel* tableMod;
    recordModel* recMod;// = new recordModel(this);

};

#endif // INSERTDIALOG_H
