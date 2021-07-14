#include "blacklistValidator.h"


blacklistValidator::blacklistValidator(QObject *parent,QStringList blacklist) : QValidator(parent)
{
    setBlacklist(blacklist);
}




QValidator::State blacklistValidator::validate(QString &input, int &pos) const
{
    if (list.contains(input)){return QValidator::Intermediate;}
    return QValidator::QValidator::Acceptable;

}



void blacklistValidator::setBlacklist(QStringList blacklist)
{
    list=blacklist;
}



QStringList blacklistValidator::blacklist()
{
return list;
}
