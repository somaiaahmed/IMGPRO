#include "mainwindow.h"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QMessageBox>
#include<QLabel>
#include<QImage>
#include<QGraphicsScene>
#include<QGraphicsPixmapItem>



#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
using namespace cv;
using namespace std;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->slider->setVisible(false);
    ui->brightnessSlider->setVisible(false);
    ui->contrastSlider->setVisible(false);
    ui->cropFrame->setVisible(true);
    ui->cropFrame->setGeometry(0, 0, 0, 0);
    ui->cropFrame->setMinimumSize(0, 0); // Set a minimum size of 0x0 (no minimum size)
  //  ui->cropFrame->stackAbove(ui->img2);


    //connect(ui->crop, &QPushButton::clicked, this, &MainWindow::cropImage);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString imagePath;
Mat img;

double currentAngle = 0.0;


//load an image
void MainWindow::on_load_clicked()
{
    imagePath = QFileDialog::getOpenFileName(nullptr, "Open Image", "", "Images (*.png *.jpg *.bmp *.jpeg)");

    if(imagePath.isEmpty())
        QMessageBox::information(this,"NULL"," No Image is selected");

    else {

        img = imread(imagePath.toStdString());
        if (!img.empty()) {
            QImage img_edited((const uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_BGR888);

            int labelw = ui->img1->width();
            int labelh = ui->img1->height();

            ui->img1->setPixmap(QPixmap::fromImage(img_edited).scaled(labelw, labelh));
        }
        else {
            QMessageBox::warning(this, "Error!", "Failed to load the image.");
        }
    }
}


//handel the blur button
void MainWindow::on_blur_clicked()
{


      if (!img.empty()) {

        ui->slider->setVisible(true);
        ui->brightnessSlider->setVisible(false);
        ui->contrastSlider->setVisible(false);


        QImage img_edited((const uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_BGR888);

        int labelw=ui->img2->width();
        int labelh=ui->img2->height();
        ui->img2->setPixmap(QPixmap::fromImage(img_edited).scaled(labelw,labelh));
        connect(ui->slider, &QSlider::valueChanged, this, &MainWindow::on_slider_valueChanged);

      } else {
    QMessageBox::warning(this,"Error!", "Failed to load the image.");
      }


}
//handel blur value
void MainWindow::on_slider_valueChanged(int value)
{
      // Get the current image from 'img'
      if (!img.empty()) {

    Mat blurredImg;
    // Apply Gaussian blur with a variable kernel size based on the slider's value
    int kernelSize = value * 2 + 1; // Ensure it's an odd number
    GaussianBlur(img, blurredImg, Size(kernelSize, kernelSize), 0);
    //img=blurredImg.clone();
    // Convert and display the blurred image in your QLabel
    QImage img_edited((const uchar*)blurredImg.data, blurredImg.cols, blurredImg.rows, blurredImg.step, QImage::Format_BGR888);

    int labelw = ui->img2->width();
    int labelh = ui->img2->height();
    ui->img2->setPixmap(QPixmap::fromImage(img_edited).scaled(labelw, labelh));
      }

}





//handel left rotate button
void MainWindow::on_rotate_clicked()
{
       // img =imread(imagePath.toStdString());
      if (!img.empty()) {
    ui->slider->setVisible(false);
    ui->brightnessSlider->setVisible(false);
    ui->contrastSlider->setVisible(false);


    // Increment the current angle by 90 degrees
    currentAngle += 90.0;

    // Reset the angle to 0 if it exceeds 360 degrees (full circle rotation)
    if (currentAngle >= 360.0) {
        currentAngle = 0.0;
    }

    Point2f center;
    center.x = static_cast<float>(img.cols) / 2.0f;
    center.y = static_cast<float>(img.rows) / 2.0f;

    Mat rotmatrix = getRotationMatrix2D(center, currentAngle, 1.0);
    Mat rotatedImg;
    warpAffine(img, rotatedImg, rotmatrix, img.size());
    //img =rotatedImg.clone();
    QImage img_edited((const uchar*)rotatedImg.data, rotatedImg.cols, rotatedImg.rows, rotatedImg.step, QImage::Format_BGR888);

    int labelw = ui->img2->width();
    int labelh = ui->img2->height();
    ui->img2->setPixmap(QPixmap::fromImage(img_edited).scaled(labelw, labelh));
    //img=rotatedImg;
      } else {
    QMessageBox::warning(this,"Error!", "Failed to load the image.");
      }
}

//handel gray button
void MainWindow::on_gray_clicked()
{
     //   img =imread(imagePath.toStdString());
      if (!img.empty()) {
    ui->slider->setVisible(false);
    ui->brightnessSlider->setVisible(false);
    ui->contrastSlider->setVisible(false);


    Mat grayImg;
    cvtColor(img, grayImg, COLOR_BGR2GRAY); // Convert to grayscale

    //img=grayImg.clone();

    QImage img_edited((const uchar*)grayImg.data, grayImg.cols, grayImg.rows, grayImg.step, QImage::Format_Grayscale8);

    int labelw = ui->img2->width();
    int labelh = ui->img2->height();
    ui->img2->setPixmap(QPixmap::fromImage(img_edited).scaled(labelw, labelh));
    //img=grayImg;

      } else {
    QMessageBox::warning(this, "Error!", "No image loaded or image processing failed.");
      }
}


//handel right rotate button
void MainWindow::on_rightRotate_clicked()
{
    // img =imread(imagePath.toStdString());
      if (!img.empty()) {
    ui->slider->setVisible(false);
    ui->brightnessSlider->setVisible(false);
    ui->contrastSlider->setVisible(false);


    // Increment the current angle by 90 degrees
    currentAngle -= 90.0;

    // Reset the angle to 0 if it exceeds 360 degrees (full circle rotation)
    if (currentAngle >= 360.0) {
        currentAngle = 0.0;
    }

    Point2f center;
    center.x = static_cast<float>(img.cols) / 2.0f;
    center.y = static_cast<float>(img.rows) / 2.0f;

    Mat rotmatrix = getRotationMatrix2D(center, currentAngle, 1.0);
    Mat rotatedImg;
    warpAffine(img, rotatedImg, rotmatrix, img.size());

    //img=rotatedImg.clone();
    QImage img_edited((const uchar*)rotatedImg.data, rotatedImg.cols, rotatedImg.rows, rotatedImg.step, QImage::Format_BGR888);

    int labelw = ui->img2->width();
    int labelh = ui->img2->height();
    ui->img2->setPixmap(QPixmap::fromImage(img_edited).scaled(labelw, labelh));
    //img=rotatedImg;
      } else {
    QMessageBox::warning(this,"Error!", "Failed to load the image.");
      }
}

int n=0;

//handel resize button
void MainWindow::on_resize_clicked()
{
      n++;
      if (!img.empty()) {
    ui->slider->setVisible(false);
    ui->brightnessSlider->setVisible(false);
    ui->contrastSlider->setVisible(false);


    // Resize the original image
    Mat resizedImage;
    cv::resize(img, resizedImage, cv::Size(), 0.75, 0.75);

    //img=resizedImage.clone();
    // Display the resized image
    QImage img_edited((const uchar*)resizedImage.data, resizedImage.cols, resizedImage.rows, resizedImage.step, QImage::Format_BGR888);

    int labelw = ui->img2->width();
    int labelh = ui->img2->height();

    ui->img2->setPixmap(QPixmap::fromImage(img_edited).scaled(labelw * 3 /( 4*n), labelh * 3 / (4*n)));

    // Update the original image with the resized image
   img = resizedImage;
      }
      else {
    QMessageBox::warning(this, "Error!", "Failed to load the image.");
      }
}


//handel clear button
void MainWindow::on_clear_clicked()
{
      n=0;
      ui->slider->setVisible(false);
      ui->brightnessSlider->setVisible(false);
      ui->contrastSlider->setVisible(false);


      currentAngle = 0.0;
      img = imread(imagePath.toStdString());
      if (!img.empty()) {

    QImage img_edited((const uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_BGR888   );


    int labelw2 = ui->img2->width();
    int labelh2 = ui->img2->height();

    ui->img2->setPixmap(QPixmap::fromImage(img_edited).scaled(labelw2, labelh2));
      }
}



//handel sharp button
void MainWindow::on_sharp_clicked()
{
     //Mat img = imread(imagePath.toStdString());

      if (!img.empty()) {
  ui->slider->setVisible(false);
    ui->brightnessSlider->setVisible(false);
  ui->contrastSlider->setVisible(false);




      // Create a kernel for sharpening
      Mat kernel = (Mat_<float>(3,3) <<
                         0, -1,  0,
                        -1,  5, -1,
                        0, -1,  0);

      // Apply the kernel to sharpen the image
      Mat sharpenedImg;
      filter2D(img, sharpenedImg, -1, kernel);



      //img=sharpenedImg.clone();
      QImage img_edited((const uchar*)sharpenedImg.data, sharpenedImg.cols, sharpenedImg.rows, sharpenedImg.step, QImage::Format_BGR888);

      int labelw = ui->img2->width();
      int labelh = ui->img2->height();

      ui->img2->setPixmap(QPixmap::fromImage(img_edited).scaled(labelw , labelh));


     // img = sharpenedImg;
      }
      else {
      QMessageBox::warning(this, "Error!", "Failed to load the image.");
      }
}


//handel flip button
void MainWindow::on_flip_clicked()
{
      if (!img.empty()) {
      ui->slider->setVisible(false);
      ui->brightnessSlider->setVisible(false);
      ui->contrastSlider->setVisible(false);


      Mat flipImg;
      cv::flip(img,flipImg,1);
      //imshow(" ",flipImg);

     // img=flipImg.clone();
      QImage img_edited((const uchar*)flipImg.data, flipImg.cols, flipImg.rows, flipImg.step, QImage::Format_BGR888);

      int labelw = ui->img2->width();
      int labelh = ui->img2->height();
      ui->img2->setPixmap(QPixmap::fromImage(img_edited).scaled(labelw, labelh));
      //img=flipImg;

      } else {
      QMessageBox::warning(this, "Error!", "No image loaded or image processing failed.");
      }
}


//handel enlarge button
void MainWindow::on_enlarge_clicked()
{

      if (!img.empty()) {
      ui->slider->setVisible(false);
      ui->brightnessSlider->setVisible(false);
      ui->contrastSlider->setVisible(false);


      n=0;
      // Resize the original image
      Mat resizedImage;
      cv::resize(img, resizedImage, cv::Size(), 1.25, 1.25);

    //  img=resizedImage.clone();
      // Display the resized image
      QImage img_edited((const uchar*)resizedImage.data, resizedImage.cols, resizedImage.rows, resizedImage.step, QImage::Format_BGR888);

      int labelw = ui->img2->width();
      int labelh = ui->img2->height();

 ui->img2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
      ui->img2->setPixmap(QPixmap::fromImage(img_edited).scaled(labelw *( 4)/3, labelh* (4)/3,Qt::KeepAspectRatio));

      // Update the original image with the resized image
      img = resizedImage;
      }
      else {
      QMessageBox::warning(this, "Error!", "Failed to load the image.");
      }
}





//handel brightness button
void MainWindow::on_brightness_clicked()
{
      if (!img.empty()) {
      ui->slider->setVisible(false);
      ui->brightnessSlider->setVisible(true);
      ui->contrastSlider->setVisible(false);


      QImage img_edited((const uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_BGR888);

      int labelw=ui->img2->width();
      int labelh=ui->img2->height();
      ui->img2->setPixmap(QPixmap::fromImage(img_edited).scaled(labelw,labelh));

      connect(ui->brightnessSlider, &QSlider::valueChanged, this, &MainWindow::on_brightnessSlider_valueChanged);
      } else {
      QMessageBox::warning(this,"Error!", "Failed to load the image.");
      }
}

void adjustBrightness(cv::Mat& img, int brightnessOffset) {
      // Iterate through all the pixels in the image
      for (int y = 0; y < img.rows; y++) {
      for (int x = 0; x < img.cols; x++) {
        // Get the pixel value at (x, y)
        cv::Vec3b& pixel = img.at<cv::Vec3b>(y, x);

        // Adjust the brightness by adding the offset to each channel
        pixel[0] = cv::saturate_cast<uchar>(pixel[0] + brightnessOffset); // Blue channel
        pixel[1] = cv::saturate_cast<uchar>(pixel[1] + brightnessOffset); // Green channel
        pixel[2] = cv::saturate_cast<uchar>(pixel[2] + brightnessOffset); // Red channel
      }
      }
}

void MainWindow::on_brightnessSlider_valueChanged(int value)
{
      if (!img.empty()) {
      // Make a copy of the original image to apply brightness adjustments
     Mat adjustedImg = img.clone();
      adjustBrightness(adjustedImg, value);

  //   img =adjustedImg.clone();
      // Convert and display the adjusted image in your QLabel
      QImage img_edited((const uchar*)adjustedImg.data, adjustedImg.cols, adjustedImg.rows, adjustedImg.step, QImage::Format_BGR888);

      int labelw = ui->img2->width();
      int labelh = ui->img2->height();
      ui->img2->setPixmap(QPixmap::fromImage(img_edited).scaled(labelw, labelh));
      }
}

void adjustContrast(cv::Mat& img, double contrastFactor) {
      // Iterate through all the pixels in the image
      for (int y = 0; y < img.rows; y++) {
      for (int x = 0; x < img.cols; x++) {
        // Get the pixel value at (x, y)
        cv::Vec3b& pixel = img.at<cv::Vec3b>(y, x);

        // Adjust the contrast by scaling each channel value
        for (int c = 0; c < 3; c++) { // 3 channels (BGR)
            pixel[c] = cv::saturate_cast<uchar>(pixel[c] * contrastFactor);
        }
      }
      }
}



void MainWindow::on_contrastSlider_valueChanged(int value)
{

      if (!img.empty()) {
      // Make a copy of the original image to apply brightness adjustments
      Mat adjustedImg = img.clone();
      adjustContrast(adjustedImg, value);

      //img=adjustedImg.clone();
      // Convert and display the adjusted image in your QLabel
      QImage img_edited((const uchar*)adjustedImg.data, adjustedImg.cols, adjustedImg.rows, adjustedImg.step, QImage::Format_BGR888);

      int labelw = ui->img2->width();
      int labelh = ui->img2->height();
      ui->img2->setPixmap(QPixmap::fromImage(img_edited).scaled(labelw, labelh));
      }
}


//handel contrast button
void MainWindow::on_contrast_clicked()
{
      if (!img.empty()) {
      ui->slider->setVisible(false);
      ui->brightnessSlider->setVisible(false);
        ui->contrastSlider->setVisible(true);

      QImage img_edited((const uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_BGR888);

      int labelw=ui->img2->width();
      int labelh=ui->img2->height();
      ui->img2->setPixmap(QPixmap::fromImage(img_edited).scaled(labelw,labelh));
      connect(ui->contrastSlider, &QSlider::valueChanged, this, &MainWindow::on_contrastSlider_valueChanged);
      } else {
      QMessageBox::warning(this,"Error!", "Failed to load the image.");
      }
}

//handel white balance button
void MainWindow::on_color_clicked()
{
      if (!img.empty()) {
      ui->slider->setVisible(false);
      ui->brightnessSlider->setVisible(false);
      ui->contrastSlider->setVisible(false);

      cv::Scalar avgColor = cv::mean(img);

      // Calculate the scaling factors for each channel to balance white
      double scaleFactorB = avgColor[0] / 255.0;
      double scaleFactorG = avgColor[1] / 255.0;
      double scaleFactorR = avgColor[2] / 255.0;

      // Apply the scaling factors to each channel
      Mat balancedImage;
      multiply(img, Scalar(scaleFactorB, scaleFactorG, scaleFactorR), balancedImage);

      // Ensure that pixel values are within the valid range [0, 255]
      normalize(balancedImage, balancedImage, 0, 255, NORM_MINMAX);

      // Convert the balanced image to 8-bit format
      balancedImage.convertTo(balancedImage, CV_8U);



     // img=balancedImage.clone();
      QImage img_edited((const uchar*)balancedImage.data, balancedImage.cols, balancedImage.rows, balancedImage.step, QImage::Format_BGR888);

      int labelw = ui->img2->width();
      int labelh = ui->img2->height();
    ui->img2->setPixmap(QPixmap::fromImage(img_edited).scaled(labelw, labelh));

       } else {
      QMessageBox::warning(this,"Error!", "Failed to load the image.");
      }
}


//handel save button
void MainWindow::on_save_clicked()
{
      // Check if img1 label contains an image
      if (!ui->img2->pixmap()) {
      QMessageBox::warning(this, "Error", "No image to save.");
      return;
      }

      QString savePath = QFileDialog::getSaveFileName(this, "Save Image", "", "Images (*.png *.jpg *.bmp *.jpeg)");

      if (!savePath.isEmpty()) {
      // Convert the QImage from img1 to a QPixmap for saving
      QPixmap savePixmap = ui->img2->pixmap();

      // Save the QPixmap to the selected file path
      if (savePixmap.save(savePath)) {
        QMessageBox::information(this, "Success", "Image saved successfully.");
      } else {
        QMessageBox::warning(this, "Error", "Failed to save the image.");
      }
      }
}


//handel crop button
void MainWindow::on_crop_clicked() {

      if (!img.empty()) {
        ui->slider->setVisible(false);
        ui->brightnessSlider->setVisible(false);
        ui->contrastSlider->setVisible(false);
      // Show the cropping frame and set isCropping to true


      ui->cropFrame->setVisible(true);
      isCropping = true;
     // QPixmap pixmap = ui->img2->pixmap();  // Get the QPixmap from ui->img2
      //QImage img_edited = pixmap.toImage(); // Convert the QPixmap to a QImage
          QImage img_edited ((const uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_BGR888);

      int labelw = ui->img2->width();
      int labelh = ui->img2->height();
      ui->img2->setPixmap(QPixmap::fromImage(img_edited).scaled(labelw, labelh));
      // Assuming you have QPushButton pointers for both buttons.
      ui->cropFrame->setGeometry(0, 0, 0, 0);
      } else {
      QMessageBox::warning(this,"Error!", "Failed to load the image.");
      }
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
      if (isCropping)
      {
      if (event->button() == Qt::LeftButton)
      {
            lastMousePos = event->pos();
            isMoving = true;
            ui->cropFrame->setFixedSize(0, 0);
         //   ui->cropFrame->setGeometry(event->pos().x(), event->pos().y(), 0, 0);
              ui->cropFrame->move(event->pos());
      }
      }
}


void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
      if (isMoving)
      {
      int width = event->pos().x() - lastMousePos.x();
      int height = event->pos().y() - lastMousePos.y();
    ui->cropFrame->setFixedSize(event->pos().x() - lastMousePos.x(), event->pos().y() - lastMousePos.y());

     ui-> cropFrame->setGeometry(lastMousePos.x(), lastMousePos.y(), width, height);
      qDebug()<<event->pos().x()<<" "<<lastMousePos.x();
      }
}


void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
      if (isCropping && isMoving)
      {
      // Create a QImage named img_edited using your img data (assuming img is valid)
      QImage img_edited((const uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_BGR888);

      isMoving = false;

      // QRect rect;
      float xratio = static_cast<float>(img_edited.width()) / static_cast<float>(ui->img1->pixmap().width());
      float yratio = static_cast<float>(img_edited.height()) / static_cast<float>(ui->img1->pixmap().height());
      float xp = (ui->img2->width() - ui->img2->pixmap().width()) / 2;
      float yp = (ui->img2->height() - ui->img2->pixmap().height()) / 2;

     /* QRect rect(
          static_cast<int>((ui->cropFrame->x() -50)*xratio ),
          static_cast<int>((ui->cropFrame->y() -180)*yratio ),
          static_cast<int>(ui->cropFrame->width() *4),
          static_cast<int>(ui->cropFrame->height() *2)
          );*/
      QRect rect(
          static_cast<int>((ui->cropFrame->x() ) ),
          static_cast<int>((ui->cropFrame->y() -20) ),
          static_cast<int>(ui->cropFrame->width() * xratio),
          static_cast<int>(ui->cropFrame->height() *yratio)
          );

      qDebug() << "xratio: " << xratio << ", yratio: " << yratio;
      qDebug() << "xp: " << xp << ", yp: " << yp;
      qDebug() << "CropFrame x: " << ui->cropFrame->x() << ", y: " << ui->cropFrame->y();
      qDebug() << "CropFrame width: " << ui->cropFrame->width() << ", height: " << ui->cropFrame->height();
      qDebug() << "Cropped Rect: " << rect;



      img_edited = img_edited.copy(rect);


      // Display the cropped image
      ui->img2->setPixmap(QPixmap::fromImage(img_edited));


      // Hide the cropping frame
       ui->cropFrame->setGeometry(0, 0, 0, 0);
      ui->cropFrame->setVisible(false);

      // Reset isCropping
      isCropping = false;
      }
}
