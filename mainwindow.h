#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>

#include "loginform.h"
#include "participants.h"
#include "ercontainer.h"
#include "drawing_entity.h"
#include "drawing_relation.h"

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

    void on_loadPreviousStateBtn_clicked();

    void on_saveCurrentStateBtn_clicked();

    void on_showResearchResultBtn_clicked();

    void on_writeConclusionBtn_clicked();

private:
    Ui::MainWindow *ui;
    LoginForm *loginForm;
    Participants *participantsForm;
    QGraphicsScene  *scene;
    ERContainer<std::string> *graph;

};

#endif // MAINWINDOW_H
