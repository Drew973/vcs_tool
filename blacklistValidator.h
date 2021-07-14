#ifndef BLACKLISTVALIDATOR_H
#define BLACKLISTVALIDATOR_H



#include <QStringList>

#include <QValidator>

class blacklistValidator : public QValidator
{
public:
    explicit blacklistValidator(QObject *parent = nullptr,QStringList blacklist=QStringList());

    QValidator::State validate(QString &input, int &pos) const;
    void setBlacklist(QStringList blacklist);
    QStringList blacklist();


private:
    QStringList list;

};

#endif // BLACKLISTVALIDATOR_H
