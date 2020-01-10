#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QBoxLayout>
#include <QPushButton>
#include <QShortcut>
#include <QKeyEvent>
#include <QDesktopWidget>
#include <QApplication>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(1);
    ui->noteKeysFrame->hide();
    ui->noteKeysFrame_2->hide();

    ui->noteKeysFrame->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui->noteLabelFrame->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    connect(this, &MainWindow::keyboardKeyPressed, ui->practiceCanvas, &MyCanvas::getKeyPressed);
    connect(this, &MainWindow::keyboardKeyReleased, ui->practiceCanvas, &MyCanvas::getKeyReleased);
    connect(this, &MainWindow::clearStaff, ui->practiceCanvas, &MyCanvas::clear);

    connect(this, &MainWindow::keyboardKeyPressed, ui->examCanvas, &MyCanvas::getKeyPressed);
    connect(this, &MainWindow::keyboardKeyReleased, ui->examCanvas, &MyCanvas::getKeyReleased);
    connect(this, &MainWindow::clearStaff, ui->examCanvas, &MyCanvas::clear);
    connect(this, &MainWindow::loadLesson, ui->examCanvas, &MyCanvas::queueLessonLoad);
    connect(ui->examCanvas, &MyCanvas::sendLessonEnd, this, &MainWindow::getLessonEnd);

    QWidget::showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::lessonPageConfig(int lesson)
{
    lessonSelected = lesson;
}

void MainWindow::on_playButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_instrumentSelectButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_backButtonInstrumentPage_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_backButtonLessonPage_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::on_introLessonButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    lessonPageConfig(2);
}

void MainWindow::on_backButtonIntroLessonPage_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_expandPushButtonPracticePage_clicked()
{
    // TODO: Needs a specefic signal to know what lesson to go to
    ui->stackedWidget->setCurrentIndex(3);
    lessonPageConfig(lessonSelected);
}

void MainWindow::on_testPageBackButton_clicked()
{
    // TODO: Needs a specefic signal to know what lesson to go to
    ui->stackedWidget->setCurrentIndex(3);
    lessonPageConfig(lessonSelected);
}

void MainWindow::on_examBackButton_clicked()
{
    emit clearStaff();
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_continueToLessonPageButton_clicked()
{
    emit clearStaff();
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_nextButtonFromeTestPage_clicked()
{
    emit clearStaff();
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_backButtonLesson1Page_clicked()
{
    emit clearStaff();
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_nextButtonLesson1Page_clicked()
{
    emit clearStaff();
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_lesson1Button_clicked()
{
    emit clearStaff();
    ui->stackedWidget->setCurrentIndex(5);
    lessonPageConfig(1);
    setLessonSlide();
}

void MainWindow::on_backButtonLesson2_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_nextButtonLesson2_clicked()
{
    emit clearStaff();
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_lesson2Button_clicked()
{
    emit clearStaff();
    ui->stackedWidget->setCurrentIndex(5);
    lessonPageConfig(2);
    setLessonSlide();
}

void MainWindow::on_twinkleButton_clicked()
{
    if (!midi_tool.openFile("../midFiles/twinkle.mid"))
    {
        return;
    }

    playNote();

}

void MainWindow::playNote()
{
    midi_tool.getNextNote();
    if (midi_tool.EOFPassed())
    {
        return;
    }
    double length = midi_tool.getNoteLength() * 1000;
    midi_tool.playCurrentNote();
    QTimer::singleShot((int) length + 10, this, &MainWindow::playNote);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (arg1 == 0)
    {
        ui->noteKeysFrame->hide();
        ui->noteLabelFrame->show();
        ui->noteKeysFrame_2->hide();
        ui->noteLabelFrame_2->show();
        ui->checkBox_2->setChecked(0);
    }
    else
    {
        ui->noteKeysFrame->show();
        ui->noteLabelFrame->hide();
        ui->noteKeysFrame_2->show();
        ui->noteLabelFrame_2->hide();
        ui->checkBox_2->setChecked(1);
    }
}


void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if (arg1 == 0)
    {
        ui->noteKeysFrame->hide();
        ui->noteLabelFrame->show();
        ui->noteKeysFrame_2->hide();
        ui->noteLabelFrame_2->show();
        ui->checkBox->setChecked(0);
    }
    else
    {
        ui->noteKeysFrame->show();
        ui->noteLabelFrame->hide();
        ui->noteKeysFrame_2->show();
        ui->noteLabelFrame_2->hide();
        ui->checkBox->setChecked(1);
    }
}

bool MainWindow::isPlayableWindow()
{
    return !(ui->stackedWidget->currentIndex() == 5 || ui->stackedWidget->currentIndex() == 6);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    grabKeyboard();
    if (event->isAutoRepeat())
    {
        event->ignore();
    }
    else
    {
        switch(event->key())
        {
            case Qt::Key_Q : on_a_F_pressed();          break;
            case Qt::Key_2 : on_a_Fsharp_pressed();     break;
            case Qt::Key_W : on_a_G_pressed();          break;
            case Qt::Key_3 : on_a_Gsharp_pressed();     break;
            case Qt::Key_E : on_b_A_pressed();          break;
            case Qt::Key_4 : on_b_Asharp_pressed();     break;
            case Qt::Key_R : on_b_B_pressed();          break;
            case Qt::Key_T : on_b_C_pressed();          break;
            case Qt::Key_6 : on_b_Csharp_pressed();     break;
            case Qt::Key_Y : on_b_D_pressed();          break;
            case Qt::Key_7 : on_b_Dsharp_pressed();     break;
            case Qt::Key_U : on_b_E_pressed();          break;
            case Qt::Key_I : on_b_F_pressed();          break;
            case Qt::Key_9 : on_b_Fsharp_pressed();     break;
            case Qt::Key_O : on_b_G_pressed();          break;
            case Qt::Key_0 : on_b_Gsharp_pressed();     break;
            case Qt::Key_P : on_c_A_pressed();          break;
            case Qt::Key_Minus : on_c_Asharp_pressed(); break;
            case Qt::Key_BracketLeft : on_c_B_pressed();break;
            case Qt::Key_Z : on_c_C_pressed();          break;
            case Qt::Key_S : on_c_Csharp_pressed();     break;
            case Qt::Key_X : on_c_D_pressed();          break;
            case Qt::Key_D : on_c_Dsharp_pressed();     break;
            case Qt::Key_C : on_c_E_pressed();          break;
            case Qt::Key_V : on_c_F_pressed();          break;
            case Qt::Key_G : on_c_Fsharp_pressed();     break;
            case Qt::Key_B : on_c_G_pressed();          break;
            case Qt::Key_H : on_c_Gsharp_pressed();     break;
            case Qt::Key_N : on_d_A_pressed();          break;
            case Qt::Key_J : on_d_Asharp_pressed();     break;
            case Qt::Key_M : on_d_B_pressed();          break;
            case Qt::Key_Comma : on_d_C_pressed();      break;
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
    {
        event->ignore();
    }
    else
    {
        switch(event->key())
        {
            case Qt::Key_Q : on_a_F_released();          break;
            case Qt::Key_2 : on_a_Fsharp_released();     break;
            case Qt::Key_W : on_a_G_released();          break;
            case Qt::Key_3 : on_a_Gsharp_released();     break;
            case Qt::Key_E : on_b_A_released();          break;
            case Qt::Key_4 : on_b_Asharp_released();     break;
            case Qt::Key_R : on_b_B_released();          break;
            case Qt::Key_T : on_b_C_released();          break;
            case Qt::Key_6 : on_b_Csharp_released();     break;
            case Qt::Key_Y : on_b_D_released();          break;
            case Qt::Key_7 : on_b_Dsharp_released();     break;
            case Qt::Key_U : on_b_E_released();          break;
            case Qt::Key_I : on_b_F_released();          break;
            case Qt::Key_9 : on_b_Fsharp_released();     break;
            case Qt::Key_O : on_b_G_released();          break;
            case Qt::Key_0 : on_b_Gsharp_released();     break;
            case Qt::Key_P : on_c_A_released();          break;
            case Qt::Key_Minus : on_c_Asharp_released(); break;
            case Qt::Key_BracketLeft : on_c_B_released();break;
            case Qt::Key_Z : on_c_C_released();          break;
            case Qt::Key_S : on_c_Csharp_released();     break;
            case Qt::Key_X : on_c_D_released();          break;
            case Qt::Key_D : on_c_Dsharp_released();     break;
            case Qt::Key_C : on_c_E_released();          break;
            case Qt::Key_V : on_c_F_released();          break;
            case Qt::Key_G : on_c_Fsharp_released();     break;
            case Qt::Key_B : on_c_G_released();          break;
            case Qt::Key_H : on_c_Gsharp_released();     break;
            case Qt::Key_N : on_d_A_released();          break;
            case Qt::Key_J : on_d_Asharp_released();     break;
            case Qt::Key_M : on_d_B_released();          break;
            case Qt::Key_Comma : on_d_C_released();      break;
        }
    }
}

void MainWindow::on_aPiano_clicked()
{
    midi_tool.changeInstrument(1);
}

void MainWindow::on_bOrgan_clicked()
{
    midi_tool.changeInstrument(17);
}

void MainWindow::on_cStrings_clicked()
{
    midi_tool.changeInstrument(49);
}

void MainWindow::on_dGuitar_clicked()
{
    midi_tool.changeInstrument(26);
}

void MainWindow::on_eFlute_clicked()
{
    midi_tool.changeInstrument(75);
}

void MainWindow::on_fFrenchHorn_clicked()
{
    midi_tool.changeInstrument(61);
}

void MainWindow::on_gVibraphone_clicked()
{
    midi_tool.changeInstrument(12);
}

void MainWindow::on_hHarp_clicked()
{
    midi_tool.changeInstrument(46);
}

void MainWindow::on_iSweepPad_clicked()
{
    midi_tool.changeInstrument(96);
}

void MainWindow::on_a_F_pressed()
{
    ui->a_F->setDown(1);
    ui->a_F_2->setDown(1);
    midi_tool.noteStart(53);
    int note = 53;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_a_F_released()
{
    ui->a_F->setDown(0);
    ui->a_F_2->setDown(0);
    midi_tool.noteStop(53);
    int note = 53;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_a_Fsharp_pressed()
{
    ui->a_Fsharp->setDown(1);
    ui->a_Fsharp_2->setDown(1);
    midi_tool.noteStart(54);
    int note = 54;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_a_Fsharp_released()
{
    ui->a_Fsharp->setDown(0);
    ui->a_Fsharp_2->setDown(0);
    midi_tool.noteStop(54);
    int note = 54;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_a_G_pressed()
{
    ui->a_G->setDown(1);
    ui->a_G_2->setDown(1);
    midi_tool.noteStart(55);
    int note = 55;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_a_G_released()
{
    ui->a_G->setDown(0);
    ui->a_G_2->setDown(0);
    midi_tool.noteStop(55);
    int note = 55;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_a_Gsharp_pressed()
{
    ui->a_Gsharp->setDown(1);
    ui->a_Gsharp_2->setDown(1);
    midi_tool.noteStart(56);
    int note = 56;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_a_Gsharp_released()
{
    ui->a_Gsharp->setDown(0);
    ui->a_Gsharp_2->setDown(0);
    midi_tool.noteStop(56);
    int note = 56;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_b_A_pressed()
{
    ui->b_A->setDown(1);
    ui->b_A_2->setDown(1);
    midi_tool.noteStart(57);
    int note = 57;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_b_A_released()
{
    ui->b_A->setDown(0);
    ui->b_A_2->setDown(0);
    midi_tool.noteStop(57);
    int note = 57;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_b_Asharp_pressed()
{
    ui->b_Asharp->setDown(1);
    ui->b_Asharp_2->setDown(1);
    midi_tool.noteStart(58);
    int note = 58;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_b_Asharp_released()
{
    ui->b_Asharp->setDown(0);
    ui->b_Asharp_2->setDown(0);
    midi_tool.noteStop(58);
    int note = 58;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_b_B_pressed()
{
    ui->b_B->setDown(1);
    ui->b_B_2->setDown(1);
    midi_tool.noteStart(59);
    int note = 59;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_b_B_released()
{
    ui->b_B->setDown(0);
    ui->b_B_2->setDown(0);
    midi_tool.noteStop(59);
    int note = 59;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_b_C_pressed()
{
    ui->b_C->setDown(1);
    ui->b_C_2->setDown(1);
    midi_tool.noteStart(60);
    int note = 60;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_b_C_released()
{
    ui->b_C->setDown(0);
    ui->b_C_2->setDown(0);
    midi_tool.noteStop(60);
    int note = 60;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_b_Csharp_pressed()
{
    ui->b_Csharp->setDown(1);
    ui->b_Csharp_2->setDown(1);
    midi_tool.noteStart(61);
    int note = 61;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_b_Csharp_released()
{
    ui->b_Csharp->setDown(0);
    ui->b_Csharp_2->setDown(0);
    midi_tool.noteStop(61);
    int note = 61;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_b_D_pressed()
{
    ui->b_D->setDown(1);
    ui->b_D_2->setDown(1);
    midi_tool.noteStart(62);
    int note = 62;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_b_D_released()
{
    ui->b_D->setDown(0);
    ui->b_D_2->setDown(0);
    midi_tool.noteStop(62);
    int note = 62;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_b_Dsharp_pressed()
{
    ui->b_Dsharp->setDown(1);
    ui->b_Dsharp_2->setDown(1);
    midi_tool.noteStart(63);
    int note = 63;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_b_Dsharp_released()
{
    ui->b_Dsharp->setDown(0);
    ui->b_Dsharp_2->setDown(0);
    midi_tool.noteStop(63);
    int note = 63;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_b_E_pressed()
{
    ui->b_E->setDown(1);
    ui->b_E_2->setDown(1);
    midi_tool.noteStart(64);
    int note = 64;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_b_E_released()
{
    ui->b_E->setDown(0);
    ui->b_E_2->setDown(0);
    midi_tool.noteStop(64);
    int note = 64;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_b_F_pressed()
{
    ui->b_F->setDown(1);
    ui->b_F_2->setDown(1);
    midi_tool.noteStart(65);
    int note = 65;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_b_F_released()
{
    ui->b_F->setDown(0);
    ui->b_F_2->setDown(0);
    midi_tool.noteStop(65);
    int note = 65;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_b_Fsharp_pressed()
{
    ui->b_Fsharp->setDown(1);
    ui->b_Fsharp_2->setDown(1);
    midi_tool.noteStart(66);
    int note = 66;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_b_Fsharp_released()
{
    ui->b_Fsharp->setDown(0);
    ui->b_Fsharp_2->setDown(0);
    midi_tool.noteStop(66);
    int note = 66;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_b_G_pressed()
{
    ui->b_G->setDown(1);
    ui->b_G_2->setDown(1);
    midi_tool.noteStart(67);
    int note = 67;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_b_G_released()
{
    ui->b_G->setDown(0);
    ui->b_G_2->setDown(0);
    midi_tool.noteStop(67);
    int note = 67;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_b_Gsharp_pressed()
{
    ui->b_Gsharp->setDown(1);
    ui->b_Gsharp_2->setDown(1);
    midi_tool.noteStart(68);
    int note = 68;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_b_Gsharp_released()
{
    ui->b_Gsharp->setDown(0);
    ui->b_Gsharp_2->setDown(0);
    midi_tool.noteStop(68);
    int note = 68;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_c_A_pressed()
{
    ui->c_A->setDown(1);
    ui->c_A_2->setDown(1);
    midi_tool.noteStart(69);
    int note = 69;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_c_A_released()
{
    ui->c_A->setDown(0);
    ui->c_A_2->setDown(0);
    midi_tool.noteStop(69);
    int note = 69;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_c_Asharp_pressed()
{
    ui->c_Asharp->setDown(1);
    ui->c_Asharp_2->setDown(1);
    midi_tool.noteStart(70);
    int note = 70;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_c_Asharp_released()
{
    ui->c_Asharp->setDown(0);
    ui->c_Asharp_2->setDown(0);
    midi_tool.noteStop(70);
    int note = 70;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_c_B_pressed()
{
    ui->c_B->setDown(1);
    ui->c_B_2->setDown(1);
    midi_tool.noteStart(71);
    int note = 71;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_c_B_released()
{
    ui->c_B->setDown(0);
    ui->c_B_2->setDown(0);
    midi_tool.noteStop(71);
    int note = 71;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_c_C_pressed()
{
    ui->c_C->setDown(1);
    ui->c_C_2->setDown(1);
    midi_tool.noteStart(72);
    int note = 72;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_c_C_released()
{
    ui->c_C->setDown(0);
    ui->c_C_2->setDown(0);
    midi_tool.noteStop(72);
    int note = 72;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_c_Csharp_pressed()
{
    ui->c_Csharp->setDown(1);
    ui->c_Csharp_2->setDown(1);
    midi_tool.noteStart(73);
    int note = 73;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_c_Csharp_released()
{
    ui->c_Csharp->setDown(0);
    ui->c_Csharp_2->setDown(0);
    midi_tool.noteStop(73);
    int note = 73;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_c_D_pressed()
{
    ui->c_D->setDown(1);
    ui->c_D_2->setDown(1);
    midi_tool.noteStart(74);
    int note = 74;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_c_D_released()
{
    ui->c_D->setDown(0);
    ui->c_D_2->setDown(0);
    midi_tool.noteStop(74);
    int note = 74;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_c_Dsharp_pressed()
{
    ui->c_Dsharp->setDown(1);
    ui->c_Dsharp_2->setDown(1);
    midi_tool.noteStart(75);
    int note = 75;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_c_Dsharp_released()
{
    ui->c_Dsharp->setDown(0);
    ui->c_Dsharp_2->setDown(0);
    midi_tool.noteStop(75);
    int note = 75;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_c_E_pressed()
{
    ui->c_E->setDown(1);
    ui->c_E_2->setDown(1);
    midi_tool.noteStart(76);
    int note = 76;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_c_E_released()
{
    ui->c_E->setDown(0);
    ui->c_E_2->setDown(0);
    midi_tool.noteStop(76);
    int note = 76;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_c_F_pressed()
{
    ui->c_F->setDown(1);
    ui->c_F_2->setDown(1);
    midi_tool.noteStart(77);
    int note = 77;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_c_F_released()
{
    ui->c_F->setDown(0);
    ui->c_F_2->setDown(0);
    midi_tool.noteStop(77);
    int note = 77;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_c_Fsharp_pressed()
{
    ui->c_Fsharp->setDown(1);
    ui->c_Fsharp_2->setDown(1);
    midi_tool.noteStart(78);
    int note = 78;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_c_Fsharp_released()
{
    ui->c_Fsharp->setDown(0);
    ui->c_Fsharp_2->setDown(0);
    midi_tool.noteStop(78);
    int note = 78;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_c_G_pressed()
{
    ui->c_G->setDown(1);
    ui->c_G_2->setDown(1);
    midi_tool.noteStart(79);
    int note = 79;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_c_G_released()
{
    ui->c_G->setDown(0);
    ui->c_G_2->setDown(0);
    midi_tool.noteStop(79);
    int note = 79;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_c_Gsharp_pressed()
{
    ui->c_Gsharp->setDown(1);
    ui->c_Gsharp_2->setDown(1);
    midi_tool.noteStart(80);
    int note = 80;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_c_Gsharp_released()
{
    ui->c_Gsharp->setDown(0);
    ui->c_Gsharp_2->setDown(0);
    midi_tool.noteStop(80);
    int note = 80;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_d_A_pressed()
{
    ui->d_A->setDown(1);
    ui->d_A_2->setDown(1);
    midi_tool.noteStart(81);
    int note = 81;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_d_A_released()
{
    ui->d_A->setDown(0);
    ui->d_A_2->setDown(0);
    midi_tool.noteStop(81);
    int note = 81;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_d_Asharp_pressed()
{
    ui->d_Asharp->setDown(1);
    ui->d_Asharp_2->setDown(1);
    midi_tool.noteStart(82);
    int note = 82;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_d_Asharp_released()
{
    ui->d_Asharp->setDown(0);
    ui->d_Asharp_2->setDown(0);
    midi_tool.noteStop(82);
    int note = 82;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_d_B_pressed()
{
    ui->d_B->setDown(1);
    ui->d_B_2->setDown(1);
    midi_tool.noteStart(83);
    int note = 83;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_d_B_released()
{
    ui->d_B->setDown(0);
    ui->d_B_2->setDown(0);
    midi_tool.noteStop(83);
    int note = 83;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_d_C_pressed()
{
    ui->d_C->setDown(1);
    ui->d_C_2->setDown(1);
    midi_tool.noteStart(84);
    int note = 84;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyPressed(note, testPage);
}

void MainWindow::on_d_C_released()
{
    ui->d_C->setDown(0);
    ui->d_C_2->setDown(0);
    midi_tool.noteStop(84);
    int note = 84;
    bool testPage = ui->stackedWidget->currentIndex() == 5;
    emit keyboardKeyReleased(note, testPage);
}

void MainWindow::on_lesson3Button_clicked()
{
    emit clearStaff();
    ui->stackedWidget->setCurrentIndex(5);
    lessonPageConfig(3);
    setLessonSlide();
}

void MainWindow::on_lesson4Button_clicked()
{
    emit clearStaff();
    ui->stackedWidget->setCurrentIndex(5);
    lessonPageConfig(4);
    setLessonSlide();
}

void MainWindow::on_lesson5Button_clicked()
{
    emit clearStaff();
    ui->stackedWidget->setCurrentIndex(5);
    lessonPageConfig(5);
    setLessonSlide();
}

void MainWindow::on_lesson6Button_clicked()
{
    emit clearStaff();
    ui->stackedWidget->setCurrentIndex(5);
    lessonPageConfig(6);
    setLessonSlide();
}

void MainWindow::on_startExamButton_clicked()
{
    emit clearStaff();
    emit loadLesson(lessonSelected);
    ui->examBackButton->setEnabled(false);
    ui->continueToLessonPageButton->setEnabled(false);
    ui->startExamButton->setEnabled(false);
}

void MainWindow::getLessonEnd(int totalNotes, int correctNotes)
{
    ui->examBackButton->setEnabled(true);
    ui->continueToLessonPageButton->setEnabled(true);
    ui->startExamButton->setEnabled(true);
    double percentCorrect = (double) correctNotes / (double) totalNotes;

    CongratsDialog* cd;
    if (percentCorrect > 0.5)
    {
        cd = new CongratsDialog(this, "../resources/congrats.png", lessonSelected, percentCorrect, true);
    }
    else
    {
        cd = new CongratsDialog(this, "../resources/fail.png", lessonSelected, percentCorrect, false);
    }

    int x = (this->width() - cd->width()) / 2;
    int y = (this->height() - cd->height()) / 4;
    cd->show();
    cd->move(x, y);
    cd->setGeometry(cd->geometry().x(), cd->geometry().y(),
                    this->width() / 3, this->height() / 2);

    cd->show();
}

void MainWindow::setLessonSlide()
{
    QString lessonPath = "../lessonPDF/Lesson " + QString::number(lessonSelected) + "_scaled.png";

    QPixmap map(lessonPath);
    ui->lessonPDF->setPixmap(map);
    ui->lessonPDF->setScaledContents(true);
    ui->lessonPDF->adjustSize();
    ui->lessonPDF->show();
}

void MainWindow::on_expandButton_clicked()
{
    ExpandDialog* ed = new ExpandDialog(this);
    ed->setMap(ui->lessonPDF->pixmap()->copy(0, 0, ui->lessonPDF->pixmap()->width(),
                                                   ui->lessonPDF->pixmap()->height()));
    ed->setModal(false);
    ed->showNormal();
}
