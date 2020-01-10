#ifndef EXPANDDIALOG_H
#define EXPANDDIALOG_H

#include <QDialog>

namespace Ui {
class ExpandDialog;
}

class ExpandDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExpandDialog(QWidget *parent = 0);
    ~ExpandDialog();
    void setMap(QPixmap pdfMap);

private slots:
    void on_closeButton_clicked();

private:
    Ui::ExpandDialog *ui;
};

#endif // EXPANDDIALOG_H
