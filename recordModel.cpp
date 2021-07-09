#include "recordModel.h"
#include <QSqlField>
#include <QDebug>

//QString QSqlRecord::fieldName(int index) const



recordModel::recordModel(QObject *parent,QSqlRecord record) : QAbstractTableModel(parent)
{
    setRecord(record);
  //  QDebug<<"created recordmodel"<<columnCount();
}


void recordModel::setRecord(QSqlRecord record)
{
    rec=record;
}


int recordModel::rowCount(const QModelIndex &parent) const
{return 1;}


int recordModel::columnCount(const QModelIndex &parent) const
{
    return rec.count();
}


Qt::ItemFlags recordModel::flags(const QModelIndex &index) const//Qt::ItemIsEditable
{
    return Qt::ItemIsEditable|Qt::ItemIsEnabled;
}


bool recordModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role==Qt::EditRole)
    {
        rec.setValue(index.column(),value);
        return true;
    }
    return false;
}


QVariant recordModel::data(const QModelIndex &index, int role) const
{
    if (role==Qt::DisplayRole or role==Qt::EditRole)
    {
        qDebug() << rec.value(index.column());
        return rec.value(index.column());

    }
    return QVariant();
}


QVariant recordModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role==Qt::DisplayRole and orientation==Qt::Horizontal )
    {
        return rec.fieldName(section);
    }

    return QVariant();
}

QSqlRecord recordModel::record()
{
    return rec;
}
