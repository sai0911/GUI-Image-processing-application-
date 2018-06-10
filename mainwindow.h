#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<iostream>
#include <QMainWindow>
#include<QFileDialog>

//defining Mat class member variable to be able to process and display image.

#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
namespace Ui


{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();










    void on_verticalSlider_valueChanged(int value);

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();



    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;
    // defining Mat type image
Mat image;
Mat result,edge1,lpf1,noise;





};

#endif // MAINWINDOW_H
