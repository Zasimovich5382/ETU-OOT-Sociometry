#ifndef PARTICIPANTS_H
#define PARTICIPANTS_H

#include <QWidget>
#include <QCloseEvent>
#include <QDebug>
#include <QListWidgetItem>
#include <participantitem.h>

namespace Ui {
class Participants;
}

class Participants : public QWidget
{
    Q_OBJECT

public:
    explicit Participants(QWidget *parent = 0);
    void closeEvent (QCloseEvent *event);
    // add method to send graph ftom mainwindow to participants
    ~Participants();

private slots:
    void on_addParticipantBtn_clicked();

    void on_saveChoicesBtn_clicked();

    void on_chooseParticipantBox_currentIndexChanged(const QString &name);

private:
    Ui::Participants *ui;
    // temporary ->  replace with erGraph *ergraph;
    QStringList testlist = {"Olya", "Ne Olya", "Masha", "Ne Masha"};
    QVector <ParticipantItem*> participants;
    void initParticipantsList();
};

#endif // PARTICIPANTS_H
