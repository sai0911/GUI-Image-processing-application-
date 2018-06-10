#include "mainwindow.h"
#include "ui_mainwindow.h"
double thres=127;
 int lowThreshold = 20;
  int n=100;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName= QFileDialog::getOpenFileName(this,tr("Open Image"),".",tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));
    image=imread(fileName.toStdString().data());


    if(image.data)
    {
        ui->pushButton_2->setEnabled(true);
        ui->verticalSlider->setEnabled(true);
    }
    if (image.channels()==3)
    {
   cv::cvtColor(image,result,CV_BGR2RGB);
    QImage img=QImage((const unsigned char*)(result.data),result.cols,result.rows,QImage::Format_RGB888);


    //display label
    ui->label->setPixmap(QPixmap::fromImage(img));
    //resize the label to fit the image
    ui->label->resize(ui->label->pixmap()->size());
}
    else if (image.channels()==1)
    {
        QImage img=QImage((const unsigned char*)(image.data),image.cols,image.rows,QImage::Format_Grayscale8);
        //display label
        ui->label->setPixmap(QPixmap::fromImage(img));
        //resize the label to fit the image
        ui->label->resize(ui->label->pixmap()->size());
    }
}

void MainWindow::on_pushButton_2_clicked()
{



    cv::cvtColor(image,result,CV_BGR2GRAY);


QImage img=QImage((const unsigned char*)(result.data),result.cols,result.rows,QImage::Format_Grayscale8);

//display label
ui->label->setPixmap(QPixmap::fromImage(img));
//resize the label to fit the image
ui->label->resize(ui->label->pixmap()->size());

}

void MainWindow::on_pushButton_4_clicked()
{
    QApplication::exit();
}








void MainWindow::on_verticalSlider_valueChanged(int value)
{
    thres=value;
     lowThreshold = value;
     n=value;


}

void MainWindow::on_pushButton_3_clicked()
{
     cv::cvtColor(image,result,CV_BGR2GRAY);

    cv::adaptiveThreshold(result,result,255.0,cv::ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY,3,5);
    QImage img=QImage((const unsigned char*)(result.data),result.cols,result.rows,QImage::Format_Grayscale8);
    //display label
    ui->label->setPixmap(QPixmap::fromImage(img));
    //resize the label to fit the image
    ui->label->resize(ui->label->pixmap()->size());




}

void MainWindow::on_pushButton_5_clicked()
{




    const int ratio = 3;
    const int kernel_size = 3;

    cv::cvtColor(image,edge1,CV_BGR2GRAY);
     blur( edge1,edge1, Size(3,3) );
     Canny( edge1, edge1, lowThreshold, lowThreshold*ratio, kernel_size );

     QImage img=QImage((const unsigned char*)(edge1.data),edge1.cols,edge1.rows,QImage::Format_Grayscale8);
     //display label
     ui->label->setPixmap(QPixmap::fromImage(img));
     //resize the label to fit the image
     ui->label->resize(ui->label->pixmap()->size());


}










void MainWindow::on_pushButton_6_clicked()
{
    image.copyTo(noise);
    //number of pixels affected by noise

    for (int k=0;k<n*10;k++)
    {
        int i=rand()%noise.cols;
        int j=rand()%noise.rows;

        if(noise.channels()==1)
        {
            noise.at<uchar>(j,i)=255;
        }
        else if(noise.channels()==3)
        {
            noise.at<Vec3b>(j,i)[0]=255;
            noise.at<Vec3b>(j,i)[1]=255;
            noise.at<Vec3b>(j,i)[2]=255;
        }
    }
QImage img2;
   if(noise.channels()==1)  { img2=QImage((const unsigned char*)(noise.data),noise.cols,noise.rows,QImage::Format_Grayscale8);}

    else if(noise.channels()==3) {  cv::cvtColor(noise,noise,CV_BGR2RGB);
       img2=QImage((const unsigned char*)(noise.data),noise.cols,noise.rows,QImage::Format_RGB888); }

    //display label
    ui->label->setPixmap(QPixmap::fromImage(img2));
    //resize the label to fit the image
    ui->label->resize(ui->label->pixmap()->size());
      cv::cvtColor(noise,noise,CV_RGB2BGR);
}













void MainWindow::on_pushButton_7_clicked()
{

    medianBlur(noise,lpf1,3);
    QImage img3;
       if(noise.channels()==1)  { img3=QImage((const unsigned char*)(lpf1.data),lpf1.cols,lpf1.rows,QImage::Format_Grayscale8);}

        else if(noise.channels()==3) {  cv::cvtColor(lpf1,lpf1,CV_BGR2RGB);
           img3=QImage((const unsigned char*)(lpf1.data),lpf1.cols,lpf1.rows,QImage::Format_RGB888); }

        //display label
        ui->label->setPixmap(QPixmap::fromImage(img3));
        //resize the label to fit the image
        ui->label->resize(ui->label->pixmap()->size());



}


void MainWindow::on_pushButton_8_clicked()
{
    cv::cvtColor(image,result,CV_BGR2GRAY);
cv::threshold(result,result,thres,255.0,0);


QImage img=QImage((const unsigned char*)(result.data),result.cols,result.rows,QImage::Format_Grayscale8);
//display label
ui->label->setPixmap(QPixmap::fromImage(img));
//resize the label to fit the image
ui->label->resize(ui->label->pixmap()->size());
}
