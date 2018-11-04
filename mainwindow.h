#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void myfunction();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QLabel *label;
};

#endif // MAINWINDOW_H
