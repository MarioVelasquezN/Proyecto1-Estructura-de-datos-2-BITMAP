#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //cout<<"BMP File: "<<flush;
    w.OpenBmp("\\rolan\\Documents\\QTProjects\\BMP_Project\\arboles.bmp");
    w.PrintHeader();
    return a.exec();
}
