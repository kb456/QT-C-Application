#include "widget.h"
#include "ui_widget.h"
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QFileDialog>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    mCamera = new QCamera(this);
    mCameraImageCapture = new QCameraImageCapture(mCamera,this);
    mCameraViewfinder = new QCameraViewfinder(this);
    mLayout = new QVBoxLayout;
    mOptionsMenu = new QMenu("Options",this);
    mSenderAction = new QAction("Sender",this);
    mReceiverAction = new QAction("Receiver",this);
    mCaptureAction = new QAction("Capture",this);

    mOptionsMenu->addActions({ mSenderAction, mReceiverAction,
                               mCaptureAction });
    ui->optionspushButton->setMenu(mOptionsMenu);
    mCamera->setViewfinder(mCameraViewfinder);
    mLayout->addWidget(mCameraViewfinder);
    mLayout->setMargin(0);
    ui->scrollArea->setLayout(mLayout);

connect(mSenderAction, &QAction::triggered, [&] (){
    mCamera->start();

 });

connect(mReceiverAction, &QAction::triggered, [&] () {
    mCamera->stop();

});

connect(mCaptureAction, &QAction::triggered, [&]() {
   auto filename = QFileDialog::getSaveFileName(this,"capture","/",
                                 "Imagen (*.jpg;*.jpeg)");
   if(filename.isEmpty()) {
       return;
   }
    mCameraImageCapture->setCaptureDestination(
                QCameraImageCapture::CaptureToFile);
    QImageEncoderSettings imageEncoderSettings;
    imageEncoderSettings.setCodec("image/jpeg");
    imageEncoderSettings.setResolution(1600,1200);
    mCameraImageCapture->setEncodingSettings(imageEncoderSettings);
    mCamera->setCaptureMode(QCamera::CaptureStillImage);
    mCamera->start();
    mCamera->searchAndLock();
    mCameraImageCapture->capture(filename);
    mCamera->unlock();
});

}
Widget::~Widget()
{
    delete ui;
}
