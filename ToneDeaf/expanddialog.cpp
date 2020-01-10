#include "expanddialog.h"
#include "ui_expanddialog.h"

ExpandDialog::ExpandDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExpandDialog)
{
    ui->setupUi(this);
}

ExpandDialog::~ExpandDialog()
{
    delete ui;
}

void ExpandDialog::setMap(QPixmap pdfMap)
{
    this->setGeometry(this->x(), this->y() + 100, pdfMap.width() + 50, this->height());
    ui->label->setPixmap(pdfMap);
}

void ExpandDialog::on_closeButton_clicked()
{
    this->close();
}
