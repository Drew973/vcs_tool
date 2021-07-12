#ifndef RECORDMODEL_H
#define RECORDMODEL_H


#include <QAbstractTableModel>
#include <QSqlRecord>


class recordModel : public QAbstractTableModel
{
    Q_OBJECT
    public:


    recordModel(QObject *parent = nullptr,QSqlRecord record=QSqlRecord());

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    QSqlRecord record();

    Qt::ItemFlags flags(const QModelIndex &index) const;//Qt::ItemIsEditable


   public slots:
        void setRecord(QSqlRecord record);


   private:
        QSqlRecord rec = QSqlRecord();

};

#endif // RECORDMODEL_H
