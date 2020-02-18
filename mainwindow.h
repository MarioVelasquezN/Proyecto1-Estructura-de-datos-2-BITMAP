#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <iostream>
#include <fstream>
#include <inttypes.h>
#include <QWidget>
#include <QApplication>
#include <QPainter>
#include <QImage>
#include <QTimer>
#include <vector>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

#pragma pack(push, 1)
struct BMP_HEADER {
    //header 0-13
    char BMP_TYPE[2];
    uint32_t SIZE;//4
    uint16_t RESERVED1;//2
    uint16_t RESERVED2;
    uint32_t OFFSET;
    //info header 14-39
    uint32_t size_ih;
    uint32_t with_ih;
    uint32_t heght_ih;
    uint16_t planes_ih;//2
    uint16_t bit_count_ih;//2
    uint32_t compression_ih;
    uint32_t imageSize_ih;
    uint32_t XpixelsPerM_ih;
    uint32_t YpixelsPerM_ih;
    uint32_t ColorUsed_ih;
    uint32_t ColorImportant_ih;

};
#pragma pack(pop)

#pragma pack(push,2)
struct RGB_Color{
    int red;
    int green;
    int blue;
    //int reserve;
};
#pragma pack(pop)

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    //int red;
    //int green;
    //int blue;
    RGB_Color colors;
    vector <RGB_Color> vectorRgb;
    MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    ~MainWindow();
    //RGB_Color colores;
    //info color

    //int reserved;
    void OpenBmp(const char * );
    void PrintHeader();

    //arreglos
    //int *redo=new int[reg_header.SIZE];
    //int *greendo=new int[reg_header.SIZE];
    //int *bluedo=new int[reg_header.SIZE];


private slots:
    void on_SalirPushButton_clicked();



private:
    QTimer *timer;
    Ui::MainWindow *ui;

    char *file_name;
    ifstream file_bmp;
    BMP_HEADER reg_header;
    void ReadHeader();
};

#endif // MAINWINDOW_H
