#ifndef ADDFEATURESDIALOG_H
#define ADDFEATURESDIALOG_H

#include <QDialog>

namespace Ui {
class addFeaturesDialog;
}

class addFeaturesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addFeaturesDialog(QWidget *parent = nullptr);
    ~addFeaturesDialog();

private:
    Ui::addFeaturesDialog *ui;
};

#endif // ADDFEATURESDIALOG_H
