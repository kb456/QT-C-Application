#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()),this,SLOT(myfunction()));
    timer->start();




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myfunction()
{
    qDebug() << "update..";
}
