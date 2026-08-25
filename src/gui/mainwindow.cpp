#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"
#include <QFileDialog>
#include <QListWidget>
#include <QDebug>
#include <Qt>

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
    for (int i = 0; i < ui->mapListWidget->count(); i++){
        qDebug() << "converted: " << ui->mapListWidget->item(i)->text();
    }
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

void MainWindow::on_addMapsBtn_clicked()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Map"), "", tr("Quake Map Files (*.map)"));
    qDebug() << "empty? " << fileNames.isEmpty();
    if (!fileNames.isEmpty()) {
        // logic for removing duplicate items
        if (ui->mapListWidget->count() == 0) {
                ui->mapListWidget->addItems(fileNames);
                qDebug() << "added: " << fileNames;
        } else {
            for (QString file : fileNames) {
                if (ui->mapListWidget->findItems(file, Qt::MatchExactly).isEmpty()) {
                    ui->mapListWidget->addItem(file);
                    qDebug() << "added: " << file;
                } else qDebug() << "duplicate rejected: " << file;
            }
        }
        ui->removeMapBtn->setEnabled(true);
        ui->convertBtn->setEnabled(true);
    }
}


void MainWindow::on_removeMapBtn_clicked()
{
    for (QListWidgetItem *i : ui->mapListWidget->selectedItems()){
        qDebug() << "removed: " << i->text();
        ui->mapListWidget->takeItem(ui->mapListWidget->row(i));
        ui->mapListWidget->update();
    }
    qDebug() << "file count: " << ui->mapListWidget->count();
    if (ui->mapListWidget->count() > 0) {
        ui->convertBtn->setEnabled(true);
        ui->removeMapBtn->setEnabled(true);
    } else {
        ui->convertBtn->setEnabled(false);
        ui->removeMapBtn->setEnabled(false);
    }
}
