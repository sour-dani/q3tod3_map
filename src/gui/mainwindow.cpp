#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"
#include <QFileDialog>
#include <QListWidget>
#include <QDebug>
#include <Qt>
#include "q3tod3_map.cpp"
#include <QMessageBox>
#include <QProgressDialog>

// TODO: Add options area
//    - Option to prevent popups
//    - Option to prevent removal of bad maps
//    = Option to set the remove button to remove all maps
//    = Option to remove all maps after conversion
//    = Potentially Q3toD3 GUI ported options

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
    ui->convertBtn->setEnabled(false);
    ui->addMapsBtn->setEnabled(false);
    ui->removeMapBtn->setEnabled(false);

    if (ui->mapListWidget->count() > 0) {
        std::string infile = "";
        std::string outfile = "";
        std::string bad_maps = "\n";
        int row = 0;
        int errors = 0;
        int numFiles = ui->mapListWidget->count();

        QProgressDialog progress("Converting files...", "Cancel", 0, numFiles, this);
        progress.setWindowTitle("Progress");
        progress.setWindowModality(Qt::WindowModal);
        QApplication::processEvents();
        progress.show();

        qDebug() << "number of files: " << numFiles;

        for (int p = 0; p < numFiles; p++){

            if (progress.wasCanceled()) break;

            progress.setValue(p);
            qDebug() << "progress: " << p + 1 << "/" << numFiles;
            qDebug() << "row: " << row;

            infile = ui->mapListWidget->item(row)->text().toStdString();
            qDebug() << "converted: " << QString::fromStdString(infile);
            progress.setLabelText(QString::fromStdString(infile));
            QApplication::processEvents();

            std::string map_file = std::filesystem::path(infile).filename().generic_string();
            qDebug() << "filename: " << QString::fromStdString(map_file);

            outfile = std::filesystem::path(infile).remove_filename().generic_string();
            outfile += "converted_" + map_file;
            qDebug() << "outfile: " << QString::fromStdString(outfile);

            try {
                convert_map(infile, outfile);
                row++;
            }
            catch (const std::string msg) {
                bad_maps += infile + "\n";
                ui->mapListWidget->takeItem(row);
                qDebug() << "failed: " << QString::fromStdString(infile);
                QMessageBox::warning(
                    this,
                    tr("Error converting map"),
                    tr(msg.c_str()),
                    QMessageBox::Close
                );
                errors++;
                ui->fileCountNumberLabel->setText(QString::number(ui->mapListWidget->count()));
                QApplication::processEvents();
            }
        }
        qDebug() << "set value to the max";
        progress.setValue(numFiles);
        progress.close();
        qDebug() << "done box";

        QMessageBox msgBox(this);
        msgBox.setText("Conversion finished");
        msgBox.setWindowTitle("Done");
        msgBox.setDetailedText(
            "Successful: " + QString::number(numFiles - errors) + "\n"
            + "Failures: " + QString::number(errors) + "\n"
            + "Bad Maps:" + QString::fromStdString(bad_maps));
        msgBox.exec();
    }
    qDebug() << "enabling buttons";
    ui->convertBtn->setEnabled(true);
    ui->addMapsBtn->setEnabled(true);
    ui->removeMapBtn->setEnabled(true);
}

void MainWindow::on_actionAbout_triggered()
{
    aboutDialog = new about();
    aboutDialog->show();
}

void MainWindow::closeEvent([[maybe_unused]] QCloseEvent *event)
{
    QCoreApplication::exit();
}

void MainWindow::on_addMapsBtn_clicked()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Map"), "", tr("Quake Map Files (*.map *.MAP)"));
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
        ui->fileCountNumberLabel->setText(QString::number(ui->mapListWidget->count()));
    }
}

void MainWindow::on_removeMapBtn_clicked()
{
    for (QListWidgetItem *i : ui->mapListWidget->selectedItems()){
        qDebug() << "removed: " << i->text();
        ui->mapListWidget->takeItem(ui->mapListWidget->row(i));
        ui->mapListWidget->update();
    }
    if (ui->mapListWidget->count() > 0) {
        ui->convertBtn->setEnabled(true);
        ui->removeMapBtn->setEnabled(true);
    } else {
        ui->convertBtn->setEnabled(false);
        ui->removeMapBtn->setEnabled(false);
        ui->fileCountNumberLabel->setText(QString::number(ui->mapListWidget->count()));
    }
}
