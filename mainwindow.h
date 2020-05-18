#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "loginform.h"
#include "participants.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_setRole(enum ROLE);

    void on_updateParticipantsBtn_clicked();

private:
    Ui::MainWindow *ui;
    LoginForm *loginForm;
    Participants *participantsForm;
};

#endif // MAINWINDOW_H
