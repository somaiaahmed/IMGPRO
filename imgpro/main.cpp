#include "mainwindow.h"
#include <opencv2/opencv.hpp>
#include<iostream>
#include <QApplication>
using namespace cv;
using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;



    w.show();
    return a.exec();
}
