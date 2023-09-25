#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStack>
#include <opencv2/opencv.hpp>
#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include <QMouseEvent>

using namespace cv;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
  //  void on_crop_clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;



private slots:


    void on_load_clicked();


    void on_blur_clicked();

    void on_rotate_clicked();


    void on_gray_clicked();

    void on_rightRotate_clicked();

    void on_resize_clicked();

    void on_crop_clicked();

    void on_clear_clicked();


    void on_slider_valueChanged(int value);

    void on_sharp_clicked();

    void on_flip_clicked();

    void on_enlarge_clicked();

    void on_brightness_clicked();

    void on_brightnessSlider_valueChanged(int value);

    void on_contrastSlider_valueChanged(int value);

    void on_contrast_clicked();

    void on_color_clicked();

    void on_save_clicked();
//void cropImage();


private:
    Ui::MainWindow *ui;
    QPoint lastMousePos;
      bool sliderVisible = false;
    bool isCropping=0,isMoving=0;


};
#endif // MAINWINDOW_H
