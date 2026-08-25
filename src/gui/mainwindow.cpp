#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"
#include <QFileDialog>
#include <QListWidget>
#include <QDebug>
#include <Qt>
#include "q3tod3_map.cpp"
#include <QMessageBox>

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
    if (ui->mapListWidget->count() > 0) {
        std::string infile = "";
        std::string outfile = "";
        int row = -1;
        int errors = 0;
        std::string bad_maps = "\n";

        for (row = 0; row < ui->mapListWidget->count(); row++){
            qDebug() << "row: " << row;
            infile = ui->mapListWidget->item(row)->text().toStdString();
            qDebug() << "converted: " << QString::fromStdString(infile);

            std::string map_file = std::filesystem::path(infile).filename().generic_string();
            qDebug() << "filename: " << QString::fromStdString(map_file);

            outfile = std::filesystem::path(infile).remove_filename().generic_string();
            outfile += "converted_" + map_file;
            qDebug() << "outfile: " << QString::fromStdString(outfile);
            try {
                convert_map(infile, outfile);
            }
            catch (const std::string msg) {
                bad_maps += infile + "\n";
                ui->mapListWidget->takeItem(row);
                QMessageBox::warning(
                    this,
                    tr("Error converting map"),
                    tr(msg.c_str()),
                    QMessageBox::Close
                );
                row--;
                errors++;
            }
        }
        QMessageBox msgBox(this);
        msgBox.setText("Conversion finished");
        msgBox.setWindowTitle("Done");
        msgBox.setDetailedText(
            "Successful: " + QString::number(ui->mapListWidget->count()) + "\n"
            + "Failures: " + QString::number(errors) + "\n"
            + "Bad Maps:" + QString::fromStdString(bad_maps));
        msgBox.exec();
        ui->mapListWidget->count();
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
