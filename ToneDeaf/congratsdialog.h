#ifndef CONGRATSDIALOG_H
#define CONGRATSDIALOG_H

#include <QDialog>

namespace Ui {
class CongratsDialog;
}

class CongratsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CongratsDialog(QWidget *parent = 0,
                            QString imgPath = "",
                            int lesson = 0,
                            double percentCorrect = 0.0,
                            bool passed = true);
    ~CongratsDialog();

private slots:
    void on_continueButton_clicked();

private:
    Ui::CongratsDialog *ui;
};

#endif // CONGRATSDIALOG_H
