#include "mainwindow.h"
#include <SFML/Graphics.hpp>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication App(argc, argv);

    MainWindow w;
    w.setWindowTitle("Tone Deaf");
    w.setWindowIcon(QIcon(":/resources/icon.png"));
    w.show();

    return App.exec();
}
