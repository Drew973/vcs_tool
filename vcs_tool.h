#ifndef VCSTOOL_H
#define VCSTOOL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class vcsTool; }
QT_END_NAMESPACE

class vcsTool : public QMainWindow
{
    Q_OBJECT

public:
    vcsTool(QWidget *parent = nullptr);
    ~vcsTool();

private:
    Ui::vcsTool *ui;
};
#endif // VCSTOOL_H
