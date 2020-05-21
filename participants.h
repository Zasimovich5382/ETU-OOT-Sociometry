#ifndef PARTICIPANTS_H
#define PARTICIPANTS_H

#include <QWidget>
#include <QCloseEvent>
#include <QDebug>
#include <QListWidgetItem>

#include "participantitem.h"
#include "ercontainer.h"

namespace Ui {
class Participants;
}

class Participants : public QWidget
{
    Q_OBJECT

public:
    explicit Participants(QWidget *parent = 0);
    void closeEvent (QCloseEvent *event);
    void setGraph(ERContainer<std::string> *graph);
    void initParticipantsList();
    ~Participants();

private slots:
    void on_addParticipantBtn_clicked();

    void on_saveChoicesBtn_clicked();

    void on_chooseParticipantBox_currentIndexChanged(const QString &name);

signals:
    void updateGraph();


private:
    Ui::Participants *ui;
    ERContainer<std::string> *graph;

    void participantFormAddParticipant(QString& name);
    void participantFormSetRelations(SocialEntity<std::string>& entity);

};

#endif // PARTICIPANTS_H
