#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

#include "loginform.h"
#include "participants.h"
#include "ercontainer.h"
#include "conclusionform.h"
#include "graphwidget.h"
#include "exceptions.h"

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

    void on_actionLog_out_triggered();

private:
    void saveToJson(const QString& filename);
    void loadFromJson(const QString& filename);

    Ui::MainWindow *ui;
    LoginForm *loginForm;
    Participants *participantsForm;
    ConclusionForm *conclusionForm;
    GraphWidget *graphWidget;
    QString conclusion;

    ERContainer<std::string> *graph;
};

#endif // MAINWINDOW_H
