#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow){
   // ui->setupUi(this);
    setGeometry(0,0,1100,1000);
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(repaint()));
    timer->start();
}

//img[3*(x+y*info->width)+comp]

void MainWindow::paintEvent(QPaintEvent *){
    //int total=vectorRgb.size();
    int cont=0;
    QImage background(size(),QImage::Format_ARGB32);

    for(int i=reg_header.heght_ih; i>0;i--){
        for(int z=0;z<reg_header.with_ih;z++){
            QRgb rgb= qRgb(vectorRgb[cont].blue,vectorRgb[cont].green,vectorRgb[cont].red);
            background.setPixel(z,i,rgb);
            cont++;
        }

    }
    QPainter paint(this);
    paint.drawImage(0,0,background);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReadHeader(){
    file_bmp.seekg(0,ios_base::beg);
    file_bmp.read((char *)&reg_header,sizeof (reg_header));
}

void MainWindow::OpenBmp(const char * filename) {
    file_name = (char *)filename;
    file_bmp.open(filename, ifstream::in | ifstream::binary);
    ReadHeader();
}

void MainWindow::PrintHeader() {
    char type[3];

    type[0] = reg_header.BMP_TYPE[0];
    type[1] = reg_header.BMP_TYPE[1];
    type[2] = '\0';//son null terminated en c++, que si tiene hola en char * realmente lo que se tiene es "hola\0"
     //memcpy(type, &reg_header.BMP_TYPE, 2);

    cout << "*********************Header***********************" << endl;
    cout << "Tipo: " << type << endl;
    cout << "Size: " << reg_header.SIZE << endl;
    cout << "Reservado 1: " << reg_header.RESERVED1 << endl;
    cout << "Reservado 2: " << reg_header.RESERVED2 << endl;
    cout << "Offset: " << reg_header.OFFSET << endl;
    cout << "*****************Info Header************************" << endl;
    cout << "Size: " << reg_header.size_ih << endl;
    cout << "Width: " << reg_header.with_ih << endl;
    cout << "heght: " << reg_header.heght_ih << endl;
    cout << "Plane: " << reg_header.planes_ih << endl;
    cout << "Bit count: " << reg_header.bit_count_ih << endl;
    cout << "Compression: " << reg_header.compression_ih << endl;
    cout << "Imagen Size: " << reg_header.imageSize_ih << endl;
    cout << "XpixelsPerM: " << reg_header.XpixelsPerM_ih << endl;
    cout << "YPixelsPerM: " << reg_header.YpixelsPerM_ih << endl;
    cout << "ColorUsed: " << reg_header.ColorUsed_ih << endl;
    cout << "ColorImportant: " << reg_header.ColorImportant_ih << endl;
    cout << "******************Color Table**************************" << endl;
        file_bmp.seekg(reg_header.OFFSET);
       // static const int umbral=90;
        //static const int reduccionX=6,reduccionY=4;
        //static unsigned char colores[9]=" bgfrRGB";
        //unsigned char* imgn;
        //if(reg_header.with_ih%4==0){
        for (uint32_t i =0; i<reg_header.with_ih; i++)
        {
            for (uint32_t j = 0; j < reg_header.with_ih; j++)
            {
                file_bmp.read((char*)&colors.red,sizeof(char));
                file_bmp.read((char*)&colors.green,sizeof (char));
                file_bmp.read((char*)&colors.blue,sizeof(char));
                //file_bmp.read((char*)&colors.reserve,sizeof (char));
                vectorRgb.push_back(colors);

               // cout <<" Red Green Blue : "<<colors.red<<" "<<colors.green<<" "<<colors.blue<<endl;
            }
        }
        //}
}


void MainWindow::on_SalirPushButton_clicked()
{
    close();
}





