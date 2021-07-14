#ifndef BLACKLISTVALIDATOR_H
#define BLACKLISTVALIDATOR_H
#include <QAbstractItemModel>
#include <QModelIndex>

/*validator to search column of model for input and return QValidator::intermediate if found
 *
 */

#include <QValidator>

class blacklistValidator : public QValidator
{
    Q_OBJECT


    public:
        explicit blacklistValidator(QObject *parent = nullptr,QModelIndex index=QModelIndex());
        QValidator::State validate(QString &input, int &pos) const;
        void setIndex(QModelIndex index);

    private:
        QModelIndex ind=QModelIndex();
};

#endif // BLACKLISTVALIDATOR_H
