#ifndef FILEWIDGET_H
#define FILEWIDGET_H

#include <QString>

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>


class fileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit fileWidget(QWidget *parent = nullptr);
    QString currentFile();

public slots:
        void setFilter(QString);
        void browse();
        void setTextEditable(bool editable);//sets if text can be edited through text edit. If not currentFile will be "" or an existing file

signals:

private:
    QPushButton * browseButton;
    QLineEdit * edit;
    QString filt;

};

#endif // FILEWIDGET_H
