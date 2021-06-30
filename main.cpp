#include "vcs_tool.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    vcsTool w;
    w.show();
    return a.exec();
}
