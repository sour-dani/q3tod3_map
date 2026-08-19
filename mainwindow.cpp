#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_convertBtn_clicked()
{

}

void MainWindow::on_actionAbout_triggered()
{
    aboutDialog = new about();
    aboutDialog->show();
}

void MainWindow::closeEvent(QCloseEvent *_)
{
    QCoreApplication::exit();
}
