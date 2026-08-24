#include "about.h"
#include "ui_about.h"

about::about(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::about)
{
    ui->setupUi(this);
}

about::~about()
{
    delete ui;
}

void about::on_closeBtn_clicked()
{
    this->close();
}

