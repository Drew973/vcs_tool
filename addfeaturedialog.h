#ifndef ADDFEATUREDIALOG_H
#define ADDFEATUREDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <QAbstractItemDelegate>
#include <QSqlDatabase>
#include <QVariant>



namespace Ui {
class addFeatureDialog;
}

class addFeatureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addFeatureDialog(QWidget *parent=nullptr,QSqlDatabase db=QSqlDatabase(),QAbstractItemDelegate * laneDelegate=nullptr,QAbstractItemDelegate * featureDelegate=nullptr,
                              QAbstractItemDelegate * locationDelegate=nullptr,QAbstractItemDelegate * photoDelegate=nullptr);
    ~addFeatureDialog();


    QStandardItemModel * model = new QStandardItemModel(1,7,parent());

    void setDelegate(int column,QAbstractItemDelegate* delegate);

    public slots:
        void setSec(QString label);
        void setDatabase(QSqlDatabase database);
        void add();



private:
    Ui::addFeatureDialog *ui;
    QString sec;
    QSqlDatabase db;
    QVariant d(int i);

};

#endif // ADDFEATUREDIALOG_H
