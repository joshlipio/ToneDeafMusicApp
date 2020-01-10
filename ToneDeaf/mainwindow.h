#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QVBoxLayout>

#include <MIDITool/miditool.h>
#include "mycanvas.h"
#include "congratsdialog.h"
#include "expanddialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void addInstruments();

signals:
    void keyboardKeyPressed(int, bool);
    void keyboardKeyReleased(int, bool);
    void loadLesson(int);
    void clearStaff();

public slots:
    void getLessonEnd(int, int);

private slots:
    void on_playButton_clicked();

    void on_backButtonLessonPage_clicked();

    void on_introLessonButton_clicked();

    void on_backButtonIntroLessonPage_clicked();

    void on_expandPushButtonPracticePage_clicked();

    void on_testPageBackButton_clicked();

    void on_examBackButton_clicked();

    void on_continueToLessonPageButton_clicked();

    void on_nextButtonFromeTestPage_clicked();

    void on_backButtonLesson1Page_clicked();

    void on_nextButtonLesson1Page_clicked();

    void on_lesson1Button_clicked();

    void on_backButtonLesson2_clicked();

    void on_nextButtonLesson2_clicked();

    void on_lesson2Button_clicked();

    void on_twinkleButton_clicked();

    void playNote();

    void on_checkBox_stateChanged(int arg1);

    void on_a_F_pressed();

    void on_a_F_released();

    void on_a_Fsharp_pressed();

    void on_a_Fsharp_released();

    void on_a_G_pressed();

    void on_a_G_released();

    void on_a_Gsharp_pressed();

    void on_a_Gsharp_released();

    void on_b_A_pressed();

    void on_b_A_released();

    void on_b_Asharp_pressed();

    void on_b_Asharp_released();

    void on_b_B_pressed();

    void on_b_B_released();

    void on_b_C_pressed();

    void on_b_C_released();

    void on_b_Csharp_pressed();

    void on_b_Csharp_released();

    void on_b_D_pressed();

    void on_b_D_released();

    void on_b_Dsharp_pressed();

    void on_b_Dsharp_released();

    void on_b_E_pressed();

    void on_b_E_released();

    void on_b_F_pressed();

    void on_b_F_released();

    void on_b_Fsharp_pressed();

    void on_b_Fsharp_released();

    void on_b_G_pressed();

    void on_b_G_released();

    void on_b_Gsharp_pressed();

    void on_b_Gsharp_released();

    void on_c_A_pressed();

    void on_c_A_released();

    void on_c_Asharp_pressed();

    void on_c_Asharp_released();

    void on_c_B_pressed();

    void on_c_B_released();

    void on_c_C_pressed();

    void on_c_C_released();

    void on_c_Csharp_pressed();

    void on_c_Csharp_released();

    void on_c_D_pressed();

    void on_c_D_released();

    void on_c_Dsharp_pressed();

    void on_c_Dsharp_released();

    void on_c_E_pressed();

    void on_c_E_released();

    void on_c_F_pressed();

    void on_c_F_released();

    void on_c_Fsharp_pressed();

    void on_c_Fsharp_released();

    void on_c_G_pressed();

    void on_c_G_released();

    void on_c_Gsharp_pressed();

    void on_c_Gsharp_released();

    void on_d_A_pressed();

    void on_d_A_released();

    void on_d_Asharp_pressed();

    void on_d_Asharp_released();

    void on_d_B_pressed();

    void on_d_B_released();

    void on_d_C_pressed();

    void on_d_C_released();

    void on_lesson3Button_clicked();

    void on_lesson4Button_clicked();

    void on_lesson5Button_clicked();

    void on_lesson6Button_clicked();

    void on_checkBox_2_stateChanged(int arg1);

    void on_instrumentSelectButton_clicked();

    void on_backButtonInstrumentPage_clicked();

    void on_aPiano_clicked();

    void on_bOrgan_clicked();

    void on_cStrings_clicked();

    void on_dGuitar_clicked();

    void on_eFlute_clicked();

    void on_fFrenchHorn_clicked();

    void on_gVibraphone_clicked();

    void on_hHarp_clicked();

    void on_iSweepPad_clicked();

    void on_startExamButton_clicked();

    void on_expandButton_clicked();

private:
    Ui::MainWindow *ui;
    MidiTool midi_tool;
    int lessonSelected;
    void lessonPageConfig(int lesson);
    bool isPlayableWindow();
    void setLessonSlide();
};

#endif // MAINWINDOW_H
