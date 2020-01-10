#include "congratsdialog.h"
#include "ui_congratsdialog.h"

CongratsDialog::CongratsDialog(QWidget *parent, QString imgPath, int lesson, double percentCorrect, bool passed) :
    QDialog(parent),
    ui(new Ui::CongratsDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    QPixmap map(imgPath);

    QString lbl;
    if (passed)
    {
        lbl = "You PASSED lesson " + QString::number(lesson) + "!";
    }
    else
    {
        lbl = "You FAILED lesson " + QString::number(lesson) + "!";
    }

    QString percLbl = "With " + QString::number(percentCorrect * 100) + "% correct notes.";

    ui->pfLabel->setText(lbl);
    ui->correctLabel->setText(percLbl);
    ui->imageLabel->setScaledContents(true);
    ui->imageLabel->setPixmap(map);
}

CongratsDialog::~CongratsDialog()
{
    delete ui;
}

void CongratsDialog::on_continueButton_clicked()
{
    this->close();
}
