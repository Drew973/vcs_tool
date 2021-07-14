#include "blacklistValidator.h"



blacklistValidator::blacklistValidator(QObject *parent,QModelIndex index) : QValidator(parent)
{
    setIndex(index);
}



//search col of mod for input. returns QValidator::Intermediate if found
QValidator::State blacklistValidator::validate(QString &input, int &pos) const
{

    if (ind.isValid())
    {
        for (int i=0;i<ind.model()->rowCount();i++)
        {
            if (input==ind.sibling(i,ind.column()).data().toString())
            {
                return QValidator::Intermediate;
            }
        }

    }

    return QValidator::QValidator::Acceptable;
}


void blacklistValidator::setIndex(QModelIndex index)
{
    ind = index;
}

