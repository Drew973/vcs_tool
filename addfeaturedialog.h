#ifndef ADDFEATUREDIALOG_H
#define ADDFEATUREDIALOG_H

#include <QDialog>

namespace Ui {
class addFeatureDialog;
}

class addFeatureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addFeatureDialog(QWidget *parent = nullptr);
    ~addFeatureDialog();

private:
    Ui::addFeatureDialog *ui;
};

#endif // ADDFEATUREDIALOG_H
