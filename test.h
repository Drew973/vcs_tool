#ifndef TEST_H
#define TEST_H

#include <QMainWindow>
#include <QObject>

class test : public QMainWindow
{
    Q_OBJECT
public:
    explicit test(QWidget *parent = nullptr);

signals:

};

#endif // TEST_H
