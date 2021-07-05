#ifndef VCSTOOL_H
#define VCSTOOL_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QString>



QT_BEGIN_NAMESPACE
namespace Ui { class vcsTool; }
QT_END_NAMESPACE

class vcsTool : public QMainWindow
{
    Q_OBJECT

    public:
        vcsTool(QWidget *parent = nullptr);
        ~vcsTool();
        QSqlTableModel * sectionsModel;
        QSqlTableModel * featuresModel;
     //   QSqlDatabase db;
        int testInt;

    public slots:
        void openDb();
        void newDb();
        bool connectToDb(QSqlDatabase db);
        void setSec(int index);


    private:
        Ui::vcsTool *ui;
};
#endif // VCSTOOL_H
